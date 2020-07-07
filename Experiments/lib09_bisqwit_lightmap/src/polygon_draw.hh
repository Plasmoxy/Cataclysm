#include "rasterize.hh"
#include "slope.hh"

template<std::size_t Xindex=0, std::size_t Yindex=1, bool PerspectiveCorrected=true, std::size_t Zindex=2, int AssumedWinding=0>
void DrawPolygon(auto&& points, auto&& Plot) requires std::ranges::input_range<decltype(points)>
{
    constexpr std::size_t Size = std::tuple_size_v<std::ranges::range_value_t<decltype(points)>>;
    static_assert(Xindex < Size && Yindex < Size && (Zindex < Size || !PerspectiveCorrected));

    RasterizePolygon<AssumedWinding>(points,
        // GetXY: Retrieve two-element tuple from a PointType. X can be float, but Y must be integer.
        [&](const auto& p) { return std::tuple{ std::get<Xindex>(p), int(std::get<Yindex>(p)) }; },
        // Slope generator
        [&](const auto& from, const auto& to, int num_steps)
        {
            // Generate a slope for all props except Y.
            // Special cases: X slope will not be perspective-corrected (or none if PerspectiveCorrected==false)
            //                Z slope values are inverted
            //                All other values are divided by Z
            return [&]<std::size_t...p>(std::index_sequence<p...>, auto&& GetSlope)
            {
                return std::array{ GetSlope( std::index_sequence<p>{} ) ... };
            }(std::make_index_sequence<Size-1>{}, [&]<std::size_t p>(std::index_sequence<p>)
            {
                constexpr std::size_t i = p + (p >= Yindex);
                // Number of steps = number of scanlines
                auto a = std::get<i>(*from), b = std::get<i>(*to);
                if constexpr(i == Xindex || !PerspectiveCorrected) return Slope(a,     b, num_steps);
                else if constexpr(i == Zindex)                     return Slope(1/a, 1/b, num_steps);
                else return Slope(a / std::get<Zindex>(*from), b / std::get<Zindex>(*to), num_steps);
            });
        },
        // Scanline function
        [&](int y, auto& left, auto& right)
        {
            constexpr std::size_t Xprop = Xindex - (Xindex>=Yindex); // Index of X within left[] and right[]
            auto leftx = (int)left[Xprop].get();
            auto endx = (int)right[Xprop].get();
            auto num_steps = endx - leftx;
            auto rounding_error = 0;//int(leftx)-leftx;

            // For each prop except X coordinate, create slopes between left and right edge
            auto props = [&]<std::size_t...p>(std::index_sequence<p...>, auto&& GetSlope)
            {
                return std::array{ GetSlope( std::index_sequence<p>{} ) ... };
            }(std::make_index_sequence<Size-2>{}, [&]<std::size_t p>(std::index_sequence<p>)
            {
                constexpr std::size_t i = p + (p >= Xprop);
                return Slope( std::get<i>(left).get(), std::get<i>(right).get(), num_steps, rounding_error );
            });
            // Using those slopes, render each pixel. After each pixel, update the slopes by their step-sizes.
            for(int x = leftx, e = endx; x < e; ++x)
            {
                [&]<std::size_t...p>(std::index_sequence<p...>, auto&& GetValue)
                {
                    Plot( GetValue( std::index_sequence<p>{} ) ... );
                }(std::make_index_sequence<Size>{}, [&]<std::size_t p>(std::index_sequence<p>)
                {
                    // Retrieve parameter for Plot() corresponding to the index "p".
                    // Parameters may come from x, y, or props[], and they may be perspective-corrected.
                    constexpr std::size_t i = p      - (p      >= Xindex) - (p      >= Yindex);
                    constexpr std::size_t z = Zindex - (Zindex >= Xindex) - (Zindex >= Yindex);
                    /**/ if constexpr(p == Xindex) return x;
                    else if constexpr(p == Yindex) return y;
                    else if constexpr(!PerspectiveCorrected) return std::get<i>(props).get();
                    else if constexpr(p == Zindex) return     1.f / std::get<z>(props).get();
                    else          return std::get<i>(props).get() / std::get<z>(props).get();
                });
                for(auto& prop: props) prop.advance();
            }

            // After the scanline is drawn, update the X coordinate and props on both sides
            for(auto& slope: left) slope.advance();
            for(auto& slope: right) slope.advance();
        });
}

