#ifndef bqtRasterizeHH
#define bqtRasterizeHH

#include <type_traits>
#include <utility>
#include <tuple>
#include <algorithm>

#include "math.hh"

template<typename P>
void RasterizeTriangle
    (const P* p0, const P* p1, const P* p2, // The three corner vertices, of some type P.
     auto&& GetXY,        // A functor that retrieves integer x and y coordinates from a ref to P.
     auto&& MakeSlope,    // A functor that creates a slope between two points, with a number of iterations.
     auto&& DrawScanline) // A functor that plots N pixels using the slopes on left and right side.
    requires std::invocable<decltype(GetXY), const P&>
         and std::invocable<decltype(MakeSlope), const P*, const P*, int>
         and IsTuple<decltype(GetXY(*p0)),2,2>
         and requires { { +std::get<0>(GetXY(*p0)) } -> std::convertible_to<int>; }
         and requires { { +std::get<1>(GetXY(*p0)) } -> std::integral; }
         and requires(decltype(MakeSlope(p0,p1,1)) a) { DrawScanline(1, a,a); }
{
    // Do the rasterization from top to bottom.
    auto [x0,y0, x1,y1, x2,y2] = std::tuple_cat(GetXY(*p0), GetXY(*p1), GetXY(*p2));

    // Sort the points in order of Y coordinate, so first point is the top one.
    // In case of equal Y coordinates, sort according to X coordinates.
    // Using a 3-input sorting network.
    if(std::tie(y1,x1) < std::tie(y0,x0)) { std::swap(x0,x1); std::swap(y0,y1); std::swap(p0,p1); }
    if(std::tie(y2,x2) < std::tie(y0,x0)) { std::swap(x0,x2); std::swap(y0,y2); std::swap(p0,p2); }
    if(std::tie(y2,x2) < std::tie(y1,x1)) { std::swap(x1,x2); std::swap(y1,y2); std::swap(p1,p2); }

    // Refuse to draw arealess triangles.
    if(int(y0) == int(y2)) return;

    // Determine whether the short side is on the left or on the right.
    bool shortside = (y1 - y0) * (x2 - x0) < (x1 - x0) * (y2 - y0); // false=left side, true=right side

    // Create two slopes: p0-p1 (short) and p0-p2 (long).
    // One of these is on the left side and one is on the right side.
    // At y = y1, the p0-p1 slope will be replaced with p1-p2 slope.
    // The type of these variables is whatever MakeSlope() returns.
    std::invoke_result_t<decltype(MakeSlope), P*,P*,int> sides[2];

    // At this point, y2-y0 cannot be zero.
    sides[!shortside] = MakeSlope(p0,p2, y2 - y0); // Slope for long side

    // The main rasterization loop.
    /*
    if(int(y0) < int(y1))
    {
        // Calculate the first slope for short side. The number of lines cannot be zero.
        sides[shortside] = MakeSlope(p0,p1, y1-y0);
        for(int y = y0; y < int(y1); ++y)
        {
            // On a single scanline, we go from the left X coordinate to the right X coordinate.
            DrawScanline(y, sides[0], sides[1]);
        }
    }
    if(int(y1) < int(y2))
    {
        // Calculate the second slope for short side. The number of lines cannot be zero.
        sides[shortside] = MakeSlope(p1,p2, y2-y1);
        for(int y = y1; y < int(y2); ++y)
        {
            // On a single scanline, we go from the left X coordinate to the right X coordinate.
            DrawScanline(y, sides[0], sides[1]);
        }
    }
    */
    // The main rasterizing loop. Note that this is intentionally designed such that
    // there's only one place where DrawScanline() is invoked. This will minimize the
    // chances that the compiler fails to inline the functor.
    for(auto y = y0, endy = y0; ; ++y)
    {
        if(y >= endy)
        {
            // If y of p2 is reached, the triangle is complete.
            if(y >= y2) break;
            // Recalculate slope for short side. The number of lines cannot be zero.
            sides[shortside] = std::apply(MakeSlope, (y<y1) ? std::tuple(p0,p1, (endy=y1) - y0)
                                                            : std::tuple(p1,p2, (endy=y2) - y1) );
        }
        // On a single scanline, we go from the left X coordinate to the right X coordinate.
        DrawScanline(y, sides[0], sides[1]);
    }
}

/* Rasterize any convex polygon. If AssumedWinding != 0, then >0 = supports only cw and <0 = supports only ccw */
template<int AssumedWinding = 0>
void RasterizePolygon
    (auto&& points,       // A bidirectional range of corner vertices, of some type.
     auto&& GetXY,        // A functor that retrieves integer x and y coordinates from a ref to a vertex.
     auto&& MakeSlope,    // A functor that creates a slope between two points, with a number of iterations.
     auto&& DrawScanline) // A functor that plots N pixels using the slopes on left and right side.
    requires std::ranges::bidirectional_range<decltype(points)>
         and std::invocable<decltype(GetXY), decltype(*std::begin(points))>
         and std::invocable<decltype(MakeSlope), decltype(std::begin(points)), decltype(std::begin(points)), int>
         and IsTuple<decltype(GetXY(*std::begin(points))), 2,2>
         and requires { { +std::get<0>(GetXY(*std::begin(points))) } -> std::convertible_to<int>; }
         and requires { { +std::get<1>(GetXY(*std::begin(points))) } -> std::integral; }
         and requires(decltype(MakeSlope(std::begin(points),std::begin(points),1)) a) { DrawScanline(1, a,a); }
{
    auto begin = std::begin(points), end = std::end(points);

    int forwards;
    if constexpr(AssumedWinding == 0)
    {
        // Figure out the winding direction. Clockwise or counterforwards?
        // decltype(Sum()) does the same as std::common_type_t between elements, but in much shorter code.
        decltype(Sum(GetXY(*begin))) x0,y0, x1,y1, x2,y2, confidence{}, threshold=1;
        // Because of rounding artifacts in clipping, it is possible that we may get
        // contradictory results from (a,b,c) and (b,c,d) for a four-corner polygon.
        // We choose the bend that has the strongest indication of directionality.
        if(auto tag = begin; tag != end) { std::tie(x0,y0) = GetXY(*tag);
        if(                ++tag != end) { std::tie(x1,y1) = GetXY(*tag);
        while(             ++tag != end)
        {
            std::tie(x2,y2) = GetXY(*tag);
            auto direction = (y1 - y0) * (x2 - x0) - (x1 - x0) * (y2 - y0);
            if(std::abs(direction) > std::abs(confidence))
                confidence = direction;
            std::tie(x0,y0) = std::tie(x1,y1);
            std::tie(x1,y1) = std::tie(x2,y2);
        }}}
        // If all vertices were parallel, or they were fewer than three, we cannot render.
        if(std::abs(confidence) < threshold) return;
        forwards = confidence < 0;
    }
    else
    {
        // User explicitly requested support for one kind of windings only. Skip testing.
        forwards = AssumedWinding > 0;
        // We don’t need to render anything that has less than three points,
        // but the algorithm in this function will produce correct results even without the check.
        // If the user supplied iterators to e.g. std::list<>, using std::distance() would not be cheap here.
        // We do have to test for an empty range, because we explicitly try to dereference at least one iterator.
        if(begin == end) { return; }
    }

    // Find the point that is topleft-most. Begin both slopes (left & right) from there.
    // Also find the bottomright-most vertex; that’s where the rendering ends.
    auto compare = [&](const auto& elem, const auto& prev)
    {
        auto [px,py, cx,cy] = std::tuple_cat(GetXY(prev), GetXY(elem));
        return std::tie(cy,cx) < std::tie(py,px);
    };
    auto [first, last] = std::minmax_element(points.begin(), points.end(), compare);

    std::array cur { first, first };
    auto y = [&](int side) -> int { return std::get<1>(GetXY(*cur[side])); };

    // The main rasterizing loop. Note that this is intentionally designed such that
    // there's only one place where DrawScanline() or MakeSlope() is invoked.
    // This will minimize the chances that the compiler fails to inline the functors.
    // The loop is terminated when the last vertex is reached on either side.
    decltype(MakeSlope(first,last,1)) sides[2] {};
    for(int side = 0, cury = y(side), next[2] = {cury,cury}; cur[side] != last; )
    {
        // We have reached a bend on either side (or both). "side" indicates which side the next bend is.
        // In the beginning of the loop, both sides have a bend (top-left corner of the polygon).
        // In that situation, we first process the left side, then without rendering anything, process the right side.
        // Now check whether to go forwards or backwards in the circular chain of points.
        auto prev = std::move(cur[side]);

        if(side == forwards) cur[side] = (std::next(prev) == end) ? begin : std::next(prev);
        else                 cur[side] = std::prev(prev == begin ? end : prev);

        next[side]  = y(side);
        sides[side] = MakeSlope(prev, cur[side], next[side] - cury);

        // Identify which side the next bend is going to be, by choosing the smaller Y coordinate.
        side = (next[0] <= next[1]) ? 0 : 1;
        // Process scanlines until the next bend.
        for(int limit = next[side]; cury != limit; ++cury)
            DrawScanline(cury, sides[0], sides[1]);
    }
}

#endif


#if 0 /* This code is what I used to record video for my demonstrations */

#include <SDL.h>
/**/
#include <cstdio>
#include <string>
auto SDL_UpdateTexture_Orig = SDL_UpdateTexture;
static void SaveFrame(SDL_Texture* texture, const unsigned* pixels, unsigned width)
{
    //unsigned asp[2] = {16,9};
    constexpr unsigned asp[2] = {1,1};
    unsigned pixwidth = width/4, pixheight = (pixwidth*asp[1]/asp[0]+7)&~7;

    auto SafeWrite = [](const void* buffer, std::size_t elemsize, std::size_t nelems, std::FILE* fp)
    {
        const char* source = static_cast<const char*>(buffer);;
        std::size_t p = 0, limit = elemsize * nelems;
        while(p < limit)
        {
            int r = std::fwrite(source+p, 1, limit-p, fp);
            if(r > 0) p += r;
            if(r <= 0) break;
        }
    };

    if(0)
    {
    static std::FILE* fp1 = std::fopen("s.dat", "wb");
    std::fwrite(pixels, width, pixheight, fp1);
    std::fflush(fp1);
    }

    //static unsigned counter=0;
    //if(++counter >= 30)
    if(1)
    {
        //std::fprintf(stderr, "pixwidth=%u pixheight=%u\n", pixwidth,pixheight);
        std::string encoder = " -c:v h264_nvenc -profile high444p -pixel_format yuv444p -preset losslesshp";
        std::string fnbuf   = "/home/bisqwit/frame.mkv";
        double fps = 60;
        std::string cmd = "ffmpeg -y -f rawvideo -pix_fmt bgra"
            " -s:v "+std::to_string(pixwidth)+"x"+std::to_string(pixheight)+
            " -r "+std::to_string(fps)+
            " -i -"
            " -aspect 16/9"
            " -loglevel error"
            + encoder
            + " " + fnbuf;
        fprintf(stderr, "%s\n", cmd.c_str());
        static std::FILE* fp = popen(cmd.c_str(), "w");
        SafeWrite(pixels, 4, pixwidth*pixheight, fp);
    }

    SDL_UpdateTexture(texture,nullptr,pixels,width);
// ffmpeg -f rawvideo -pix_fmt bgra -s 424x240 -r 60 -i s.dat -sws_flags neighbor -vf scale=3840:2160 -c:v h264 -preset slower 1.mkv
// ffmpeg -f rawvideo -pix_fmt bgra -s 3840x2160 -r 5 -i s.dat -c:v h264 -preset slower -g 5 fullscreen.mkv
}

#define SDL_UpdateTexture(a,b, pixels, width) SaveFrame(a,pixels,width)
/**/

#endif

#if 0 /* This code is what I used to verify that my requires-clauses are correct */

void test()
{
    int a;
    typedef int K;
    std::tuple<K,K> test;
    //char*test;
    RasterizeTriangle(&a,&a,&a,
        [&](const int&a){return std::tuple<K,K>{}; },
        [](const int*, const int*,int){return 0; },
        [](int,int&,int&){}
    );
}
#endif
