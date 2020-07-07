#ifndef bqtPolygonTesselateHH
#define bqtPolygonTesselateHH

#include "rasterize.hh"
#include <ranges>

void TesselateAndDraw(auto&& points, auto&& GetXY, auto&&...args) requires std::ranges::random_access_range<decltype(points)>
{
    constexpr unsigned limit = 16;
    bool too_many_corners = points.size() >= limit;

    // prev[] and next[] form a double-directional linked list
    unsigned char next[limit], prev[limit];
    for(unsigned n=0; n<points.size() && n<limit; ++n)
    {
        next[n] = (n+1)==points.size() ? 0 : (n+1);
        prev[n] = n==0 ? points.size()-1 : (n-1);
    }
    for(unsigned cur = 0, remain = points.size(); remain >= 3; --remain)
    {
        unsigned p1 = next[cur], p2 = next[p1];
        unsigned a = cur, b = p1, c = p2, era = cur;
        if(remain > 3 && !too_many_corners)
        {
            unsigned m1 = prev[cur], m2 = prev[m1];
            auto [curx,cury, p1x,p1y, p2x,p2y, m1x,m1y, m2x,m2y] = std::tuple_cat(
                GetXY(points[cur]), GetXY(points[p1]), GetXY(points[p2]), GetXY(points[m1]), GetXY(points[m2]));
            // Three possible tesselations:
            //     prev2-prev1-this (score3)
            //     prev1-this-next1 (score1)
            //     this-next1-next2 (score2)
            // Score indicates how long horizontal lines there are in this triangle
            auto score1 = (std::abs(curx-p1x) + std::abs(p1x-m1x) + std::abs(m1x-curx))
                        - (std::abs(cury-p1y) + std::abs(p1y-m1y) + std::abs(m1y-cury));
            auto score2 = (std::abs(curx-p1x) + std::abs(p1x-p2x) + std::abs(p2x-curx))
                        - (std::abs(cury-p1y) + std::abs(p1y-p2y) + std::abs(p2y-cury));
            auto score3 = (std::abs(curx-m2x) + std::abs(m2x-m1x) + std::abs(m1x-curx))
                        - (std::abs(cury-m2y) + std::abs(m2y-m1y) + std::abs(m1y-cury));
            if(score1 >= score2 && score1 >= score3)      { b = p1; c = m1; /* era = cur; */ }
            else if(score2 >= score1 && score2 >= score3) { /*b = p1; c = p2;*/ era = p1; }
            else                                          { b = m2; c = m1; era = m1; }
        }
    rest:
        RasterizeTriangle(&points[a],&points[b],&points[c], GetXY, args...);
        if(too_many_corners)
        {
            b = c++;
            if(c >= remain) return;
            goto rest;
        }
        auto p = prev[era], n = next[era];
        next[p] = n;
        prev[n] = p;
        cur = n;
    }
}

#endif

