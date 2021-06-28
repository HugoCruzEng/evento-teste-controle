#include "../subsystems/propulsion.h"

// TAG Signals -> SUBSYSTEM(P=Propulsion) / EQ(01=MCP_BE) / TYPE (D=DIGITAL/A=ANALOG/H=HMI) / SEQ(xxx)

Propulsion::Propulsion(/* args */)
{
    Mcp_ctrl_signals* mcp_be_signals = new Mcp_ctrl_signals();
    
    mcp_be_signals->status = new Digital_input(MODEL_DI_STATUS, "P01D003");               //#define CI_DG_MCP_FUNCIONANDO 2
    digital_input_list.push_back(mcp_be_signals->status);

    mcp_be_signals->start_command = new Digital_output(MODEL_DO_START_COMMAND, "P01D001");       //#define IC_DG_MCP_PARTIR 0
    digital_output_list.push_back(mcp_be_signals->start_command);
    
    mcp_be_signals->stop_command = new Digital_output(MODEL_DO_STOP_COMMAND, "P01D002");        //#define IC_DG_MCP_PARAR 1
    digital_output_list.push_back(mcp_be_signals->stop_command);
    
    mcp_be_signals->rotation = new Analog_input(MODEL_AI_ROTATION, "P01A001");              //#define SC_AN_MCP_ROTACAO 0 
    analog_input_list.push_back(mcp_be_signals->rotation);

    mcp_be_signals->actuator_position = new Analog_output(MODEL_AO_POSITION, "P01A003");    //#define CS_AN_MCP_POSATUADOR 1
    analog_output_list.push_back(mcp_be_signals->actuator_position);
    
/////////////////HMI SIGNAL //////////////////////////////////////
    mcp_be_signals->start_command_hmi = new Hmi_signal<bool>(START_COMMAND_HMI, "P01H001");
    hmi_bool_signal_list.push_back(mcp_be_signals->start_command_hmi);
    
    mcp_be_signals->stop_command_hmi = new Hmi_signal<bool>(STOP_COMMAND_HMI, "P01H002");
    hmi_bool_signal_list.push_back(mcp_be_signals->stop_command_hmi);

    mcp_be_signals->status_hmi = new Hmi_signal<bool>(STATUS_HMI, "P01H003");
    hmi_bool_signal_list.push_back(mcp_be_signals->status_hmi);

    mcp_be_signals->demand_hmi = new Hmi_signal<int>(DEMAND_HMI, "P01H004");
    hmi_int_signal_list.push_back(mcp_be_signals->demand_hmi);

    mcp_be_signals->rotation_hmi = new Hmi_signal<int>(ROTATION_HMI, "P01H008");
    hmi_int_signal_list.push_back(mcp_be_signals->rotation_hmi);

    mcp_be_signals->kp_hmi = new Hmi_signal<double>(KP_HMI, "P01H005");
    hmi_double_signal_list.push_back(mcp_be_signals->kp_hmi);

    mcp_be_signals->ki_hmi = new Hmi_signal<double>(KI_HMI, "P01H006");
    hmi_double_signal_list.push_back(mcp_be_signals->ki_hmi);

    mcp_be_signals->kd_hmi = new Hmi_signal<double>(KD_HMI, "P01H007");
    hmi_double_signal_list.push_back(mcp_be_signals->kd_hmi);

    mcp_be_signals->actuator_position_hmi = new Hmi_signal<double>(ACTUATOR_POSITION_HMI, "P01H009");
    hmi_double_signal_list.push_back(mcp_be_signals->actuator_position_hmi);
    
    mcp_be_signals->status->set_value(0);   //bool statusMCPBE_init=0;
    // Setting PID intial values
    mcp_be_signals->kp_hmi->set_value(0.009);   //double PID_P_init=0.009;
    mcp_be_signals->ki_hmi->set_value(0.26);    //double PID_I_init=0.26;
    mcp_be_signals->kd_hmi->set_value(0);       //double PID_D_init=0;*/

    mcp_be = new Mcp_ctrl(mcp_be_signals);

}

Propulsion::~Propulsion()
{
}

void Propulsion::control_propulsion()
{
    if(mcp_be->get_mcp_signals()->status->get_value() == true){
        mcp_be->start();
    }
    else {
        mcp_be->stop();
    }

    mcp_be->get_mcp_signals()->actuator_position->set_value( mcp_be->get_mcp_signals()->rotation->get_value() * 10 );
}


