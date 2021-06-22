#include "../subsystems/propulsion.h"

// TAG Signals -> SUBSYSTEM(P=Propulsion) / EQ(01=MCP_BE) / TYPE (D=DIGITAL/A=ANALOG/H=HMI) / SEQ(xxx)

Propulsion::Propulsion(/* args */)
{
    Mcp_ctrl_signals* mcp_be_signals = new Mcp_ctrl_signals();
    
    mcp_be_signals->start_command = new Digital_output(0, "P01D001");       //#define IC_DG_MCP_PARTIR 0
    mcp_be_signals->stop_command = new Digital_output(1, "P01D002");        //#define IC_DG_MCP_PARAR 1
    mcp_be_signals->status = new Digital_input(2, "P01D003");               //#define CI_DG_MCP_FUNCIONANDO 2
    
    mcp_be_signals->rotation = new Analog_input(0, "P01A001");              //#define SC_AN_MCP_ROTACAO 0 
    mcp_be_signals->set_point = new Analog_input(1, "P01A002");
    mcp_be_signals->actuator_position = new Analog_output(2, "P01A003");    //#define CS_AN_MCP_POSATUADOR 1

    mcp_be_signals->demand = new Hmi_signal<double>(0, "P01H001");          //#define IC_AN_MCP_ROTACAO 0
    mcp_be_signals->kp = new Hmi_signal<double>(1, "P01H002");              //#define IC_AN_MCP_PIDP 1
    mcp_be_signals->ki = new Hmi_signal<double>(2, "P01H003");              //#define IC_AN_MCP_PIDI 2
    mcp_be_signals->kd = new Hmi_signal<double>(3, "P01H004");              //#define IC_AN_MCP_PIDD 3

    mcp_be_signals->status->set_value(0);   //bool statusMCPBE_init=0;
    // Setting PID intial values
    mcp_be_signals->kp->set_value(0.009);   //double PID_P_init=0.009;
    mcp_be_signals->ki->set_value(0.26);    //double PID_I_init=0.26;
    mcp_be_signals->kd->set_value(0);       //double PID_D_init=0;

    mcp_be = new Mcp_ctrl(mcp_be_signals);
}

Propulsion::~Propulsion()
{
}