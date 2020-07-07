#ifndef bqtSlopeHH
#define bqtSlopeHH

class Slope
{
    float cur, step;
public:
    Slope() : cur{}, step{} {}
    Slope(float begin, float end, float num_steps, float advance=0)
    {
        float inv_step = 1.f / num_steps;
        step = (end - begin) * inv_step;  // Stepsize = (end-begin) / num_steps
        cur  = begin + step*advance;      // Begin here
    }
    float get() const     { return cur; }
    void advance()        { cur += step; }
    void advance(float n) { cur += step*n; }
};

#endif

