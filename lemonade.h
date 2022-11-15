#ifdef LEMONADE_H
    #define EXTERN
#else
    #define EXTERN extern
#endif

#include <iostream>
#include <string>
using std::string;

EXTERN string
    exec_dir;

EXTERN double
    p_x, p_y,
    v_x, v_y,
    p_m_mantissa, p_q_mantissa,

    d1, l,
    p_V0_x, p_V0_y,
    k,

    F;

EXTERN int
    p_m_exponent, p_q_exponent, k_exponent,
    resulting_exponent;

void debug_output_available_data();
