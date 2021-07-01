#include "../subsystems/propulsion.h"

// TAG Signals -> SUBSYSTEM(P=Propulsion) / EQ(01=MCP_BE) / TYPE (D=DIGITAL/A=ANALOG/H=HMI) / SEQ(xxx)

Propulsion::Propulsion(/* args */) {

    Mcp_ctrl_signals* mcp_be_signals = new Mcp_ctrl_signals();
    
    mcp_be_signals->start_command = new Digital_output(MODEL_DO_START_COMMAND, "P01D001");       //#define IC_DG_MCP_PARTIR 0 
    mcp_be_signals->stop_command = new Digital_output(MODEL_DO_STOP_COMMAND, "P01D002");        //#define IC_DG_MCP_PARAR 1
    mcp_be_signals->status = new Digital_input(MODEL_DI_STATUS, "P01D003");               //#define CI_DG_MCP_FUNCIONANDO 2

    mcp_be_signals->rotation = new Analog_input(MODEL_AI_ROTATION, "P01A001");              //#define SC_AN_MCP_ROTACAO 0 
    mcp_be_signals->actuator_position = new Analog_output(MODEL_AO_POSITION, "P01A003");    //#define CS_AN_MCP_POSATUADOR 1
    mcp_be_signals->status->set_value(false);   //bool statusMCPBE_init=0;

    mcp_be_signals->start_command->set_value(false);
    mcp_be_signals->stop_command->set_value(true);

/////////////////HMI SIGNALS //////////////////////////////////////
    mcp_be_signals->start_command_hmi = new Hmi_signal<bool>(START_COMMAND_HMI, "P01H001");
    mcp_be_signals->stop_command_hmi = new Hmi_signal<bool>(STOP_COMMAND_HMI, "P01H002");
    mcp_be_signals->status_hmi = new Hmi_signal<bool>(STATUS_HMI, "P01H003");

    mcp_be_signals->demand_hmi = new Hmi_signal<int>(DEMAND_HMI, "P01H004");
    mcp_be_signals->rotation_hmi = new Hmi_signal<int>(ROTATION_HMI, "P01H008");

    mcp_be_signals->kp_hmi = new Hmi_signal<double>(KP_HMI, "P01H005");
    mcp_be_signals->ki_hmi = new Hmi_signal<double>(KI_HMI, "P01H006");
    mcp_be_signals->kd_hmi = new Hmi_signal<double>(KD_HMI, "P01H007");
    mcp_be_signals->actuator_position_hmi = new Hmi_signal<double>(ACTUATOR_POSITION_HMI, "P01H009");

    mcp_be_signals->status_hmi->set_value(false);
    mcp_be_signals->start_command_hmi->set_value(false);
    mcp_be_signals->stop_command_hmi->set_value(false);

    mcp_be_signals->demand_hmi->set_value(0);
    mcp_be_signals->rotation_hmi->set_value(0);

    // Setting PID intial values
    mcp_be_signals->kp_hmi->set_value(0.009);   //double PID_P_init=0.009;
    mcp_be_signals->ki_hmi->set_value(0.26);    //double PID_I_init=0.26;
    mcp_be_signals->kd_hmi->set_value(0);       //double PID_D_init=0;*/

    mcp_be = new Mcp_ctrl(mcp_be_signals);
}

Propulsion::~Propulsion() {
}

void Propulsion::control_propulsion() {
    
    propulsion_control_mcp(mcp_be);

}

void Propulsion::propulsion_control_mcp(Mcp_ctrl* mcp) {

    if( (mcp->get_mcp_signals()->start_command_hmi->get_value() == true) &&
        (mcp->get_mcp_signals()->start_command->get_value() == false) 
    ) {
        mcp->get_mcp_signals()->stop_command_hmi->set_value(false);
        mcp->start();
    }
    
    if( (mcp ->get_mcp_signals()->stop_command_hmi->get_value() == true) &&
        (mcp->get_mcp_signals()->stop_command->get_value() == false) 
    ) {
        mcp->get_mcp_signals()->start_command_hmi->set_value(false);
        mcp->stop();
    }
    
    mcp->process_pid();

    // Verifica o estado do MCP
    if(mcp->get_mcp_signals()->rotation->get_value() > 500){
        mcp->get_mcp_signals()->status_hmi->set_value(true);
    }
    else if(mcp->get_mcp_signals()->rotation->get_value() < 300){
        mcp->get_mcp_signals()->status_hmi->set_value(false);
    }
    //-------------------------
}