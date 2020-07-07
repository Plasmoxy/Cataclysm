#ifndef bqtViewHH
#define bqtViewHH

#include "math.hh"
#include <array>
#include <vector>
#include <numbers>
#include <limits>
#include <cmath>

template<typename PixType = unsigned>
class View
{
    unsigned W, H;
    std::array<float,2> center, size, aspect, scale;
    std::vector<PixType> pixels;
    std::vector<float>   zbuffer;

public:
    View(unsigned Ww, unsigned Hh, float fov) :
        W(Ww), H(Hh),
        center{ W*.5f, H*.5f }, size{ center}, aspect{ 1.f, W*1.f/H },
        scale{ size * aspect * (1.f / std::tan(fov/2.f*std::numbers::pi_v<float>/180.f)) },
        pixels(W*H),
        zbuffer(W*H)
    {
    }

    void InitFrame()
    {
        for(auto& p: pixels)  p = {};
        for(auto& z: zbuffer) z = std::numeric_limits<float>::max();
    }
    const std::vector<unsigned> GetRGBpixels() const
    {
        auto ToRGB = [](auto pix)
        {
            // γ should be 1.8—2.0. I use slightly smaller number, so that the base-2
            const float γ = 1.7777777f; // representation of invγ has very few 1-bits
            float invγ = 1 / γ, brightness = 2.f, sat = 1.f;
            pix[0] = std::pow(pix[0] * brightness, invγ);
            pix[1] = std::pow(pix[1] * brightness, invγ);
            pix[2] = std::pow(pix[2] * brightness, invγ);
            float luma = Dot(pix, AsArray(.299f,.587f,.114f));
            for(unsigned n=0; n<3; ++n)
                if(pix[n] > 1.f)      sat = std::min(sat, (luma-1.f) / (luma-pix[n]));
                else if(pix[n] < 0.f) sat = std::min(sat, luma       / (luma-pix[n]));
            sat = std::clamp(sat, 0.f, 1.f);
            for(unsigned n=0; n<3; ++n)
                pix[n] = std::clamp((pix[n] - luma) * sat + luma, 0.f, 1.f);
            return Dot(AsArray<unsigned>(pix * (256-1e-5f)), AsArray(65536u,256u,1u));
        };
        std::vector<unsigned> rgb(W*H);
        for(unsigned y=0; y<H; ++y)
            for(unsigned x=0; x<W; ++x)
                rgb[y*W+x] = ToRGB( pixels[y*W+x] );
        return rgb;
    }
    const std::vector<PixType>& GetPixels() const
    {
        return pixels;
    }

    auto Draw(auto&& func) // This function returns a functor, that calls the supplied functor.
    {
        return [&](unsigned x,unsigned y,float z, auto&&... rest)
        {
            if(/* x <= W && y <= H && */ z < zbuffer[y*W+x])
            {
                pixels[y*W+x]  = func(x,y,z, std::forward<decltype(rest)>(rest)...);
                zbuffer[y*W+x] = z;
            }
        };
    }

    // Converting 3D x,y,z into 2D X & Y follows this formula (rectilinear projection):
    //    X = xcenter + x * hscale / z
    //    Y = ycenter + y * vscale / z
    auto PerspectiveProject(const auto& point) const
    {
        return scale * point * (1 / std::get<2>(point)) + center;
    }
    // Doing the same in reverse, getting 3D x,y,z from 2D X & Y,
    // can be done as follows, but requires that we already know z:
    //    x = (X - xcenter) * z / hscale
    //    y = (Y - ycenter) * z / vscale
    auto PerspectiveUnproject(const auto& point, float z) const
    {
        return std::tuple_cat((point - center) * z / scale, std::tuple{z});
    }

    auto MakeFrustum(const auto& corners) const requires std::ranges::forward_range<decltype(corners)>
    {
        // znear = near clipping plane distance, zany = arbitrary z value
        constexpr float znear = 0.1, zany = 1;
        std::vector<Plane> result{ std::array<std::array<float,3>,3>{{ {0,0,znear}, {1,0,znear}, {0,1,znear}}} };
        // Iterate through all successive pairs of corner points (including last->first)
        for(auto begin = corners.begin(), end = corners.end(), current = begin; current != end; ++current)
        {
            auto next = std::next(current); if(next == end) next = begin;
            result.push_back(std::tuple{ PerspectiveUnproject(*current,zany), PerspectiveUnproject(*next,zany), std::tuple{0,0,0}} );
        }
        return result;
    }
    auto MakeFrustum() const
    {
        return MakeFrustum(std::initializer_list{ std::pair{0,0}, {W-1,0}, {W-1,H-1}, {0,H-1} });
    }
};

#endif






































