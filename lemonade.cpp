#include "lemonade.h"
#include "debugtools.h"
/*! Defaults (by default, particle is electron). Planet is only Earth*/
std::string
    exec_dir="/";

double
//allows "hand-input" - input from ui, now stores default values
    p_x=0, p_y=0,
    v_x=100,v_y=100,
    p_m_mantissa=9.1093837015, p_q_mantissa=-1.602176634,

//not hand-inputed yet
    d1, l,
    p_V0_x=1, p_V0_y=0, //p_V0_z=0,

//consts (idk why, but they don't want to be initialized as actually consts)
    k=8.987551787368176, //exponent defined directly in formula (idk why i didn't put THIS var there...)
    g=9.8067,

//semi-nonsts (defined almost on very start of programm)
    kqCU_2m;

int
    p_m_exponent=-31, p_q_exponent=-19,
    resulting_exponent=0;

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
    Debugger.strMsgInline("v_x=");Debugger.doubMsg(v_x);
    Debugger.strMsgInline("v_y=");Debugger.doubMsg(v_y);
    Debugger.strMsg("");
}
