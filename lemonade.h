/*#ifdef LEMONADE_H
    #define EXTERN
#else
    #define EXTERN extern
#endif*/

#include <iostream>
#include <string>

using std::string;

extern string
    exec_dir;

extern double
    p_x, p_y,
    v0_x, v0_y,
    p_m_mantissa, p_q_mantissa,

    k_mantissa;

extern int
    p_m_exponent, p_q_exponent, k_exponent,
    //distance_scale_exponent,
    resulting_exponent,

    animFrames,
    animFrame_duration;

void debug_output_available_data();
