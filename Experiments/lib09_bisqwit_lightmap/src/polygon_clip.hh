#ifndef bqtPolygonClipHH
#define bqtPolygonClipHH

#include "math.hh"
#include <ranges>

void ClipPolygon(const Plane& p, auto& points) requires std::ranges::forward_range<decltype(points)>
{
    bool keepfirst = true;

    // Process each edge of the polygon (line segment between two successive points)
    for(auto current = points.begin(); current != points.end(); )
    {
        auto next = std::next(current);
        if(next == points.end()) { next = points.begin(); }

        auto outside     = p.DistanceTo(*current);
        auto outsidenext = p.DistanceTo(*next);

        // If this corner is not inside the plane, keep it
        bool keep = outside >= 0;
        if(current == points.begin()) { keepfirst=keep; keep=true; }

        // If this edge of the polygon _crosses_ the plane, generate an intersection point
        if((outside < 0 && outsidenext > 0)
        || (outside > 0 && outsidenext < 0))
        {
            auto factor = outside / (outside - outsidenext);

            // Create a new point b between *current and *next like this: current + (next-current) * factor
            auto b = *current + ((*next - *current) * factor);

            if(keep) { current = std::next(points.insert(std::next(current), std::move(b))); }
            else     { *current = std::move(b); ++current; }
        }
        else
        {
            // Keep or delete the original vertex
            if(keep) ++current; else current = points.erase(current);
        }
    }
    if(!keepfirst) points.erase(points.begin());
}

#endif

