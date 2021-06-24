#include "../equipments/mcp.h"

Mcp_ctrl::Mcp_ctrl(Mcp_ctrl_signals* mcp_signals) : mcp_signals(mcp_signals)
{
    pid = new PID( 
        &my_rotation, 
        &my_actuator_position, 
        &my_setpoint,
        0.1, //mcp_signals->kp->get_value(),
        0.1, //mcp_signals->ki->get_value(),
        0, //mcp_signals->kd->get_value(), 
        DIRECT
    );
}

Mcp_ctrl::~Mcp_ctrl()
{
}

void Mcp_ctrl::process_pid(){
    my_rotation = mcp_signals->rotation->get_value();
    my_setpoint = mcp_signals->set_point->get_value();

    pid->Compute();

    mcp_signals->actuator_position->set_value(my_actuator_position);
}

void Mcp_ctrl::start(){
    mcp_signals->start_command->set_value(true);
    mcp_signals->stop_command->set_value(false);   
}   

void Mcp_ctrl::stop(){
    mcp_signals->start_command->set_value(false);
    mcp_signals->stop_command->set_value(true);   
} 

Mcp_ctrl_signals* Mcp_ctrl::get_mcp_signals(){
    return mcp_signals;
}