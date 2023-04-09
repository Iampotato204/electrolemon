#include "lemonade.h"
#include "debugtools.h"
std::string
    exec_dir="/";

double
    p_x=0, p_y=0,
    v0_x=20,v0_y=10,
    //v0_x=-3,v0_y=15,
    //p_m_mantissa=9.1093837015, p_q_mantissa=-1.602176634,
    p_m_mantissa=910938.37015, p_q_mantissa=-160217.6634,

    k_mantissa=8.987551787368176,
    g=9.8067;

int
    //p_m_exponent=-31, p_q_exponent=-19,
    p_m_exponent=-38, p_q_exponent=-24,
    //distance_scale_exponent=2,
    k_exponent=9,

    animFrame_duration=100,
    animFrames=60;

void debug_output_available_data(){
    DebugTools Debugger;

    Debugger.strMsg("");
    Debugger.strMsg("onClickDataProcessing:");
    Debugger.strMsgInline("p_x0=");Debugger.doubMsg(p_x);
    Debugger.strMsgInline("p_y0=");Debugger.doubMsg(p_y);
    Debugger.strMsgInline("p_m_mantissa=");Debugger.doubMsg(p_m_mantissa);
    Debugger.strMsgInline("p_m_exponent=");Debugger.doubMsg(p_m_exponent);
    Debugger.strMsgInline("p_q_mantissa=");Debugger.doubMsg(p_q_mantissa);
    Debugger.strMsgInline("p_q_exponent=");Debugger.doubMsg(p_q_exponent);
    Debugger.strMsgInline("v0_x=");Debugger.doubMsg(v0_x);
    Debugger.strMsgInline("v0_y=");Debugger.doubMsg(v0_y);
    Debugger.strMsg("");
}
