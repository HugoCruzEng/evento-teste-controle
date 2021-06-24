#ifndef mcp_ctrl_h
#define mcp_ctrl_h

#include "../signal/signal.h"
#include <PID_v1.h>

class Mcp_ctrl_signals {
public:    
    Digital_output* start_command;
    Digital_output* stop_command;
    Digital_input* status;

    Analog_input* rotation;
    Analog_input* set_point;
    Analog_output* actuator_position;

    /*Hmi_signal<double>* demand;
    Hmi_signal<double>* kp;
    Hmi_signal<double>* ki;
    Hmi_signal<double>* kd;*/
};

class Mcp_ctrl {
private:
    Mcp_ctrl_signals* mcp_signals;
    PID* pid;

    double my_rotation = 0;             //double mcpBE_RPM_init=0;
    double my_setpoint = 0;             //double mcpBE_setpoint_init=0;
    double my_actuator_position = 0;    //double mcpBE_PosAtuador_init=0;

public:
    Mcp_ctrl(Mcp_ctrl_signals* mcp_signals);
    ~Mcp_ctrl();

    void start();
    void stop();
    //void rotation_demand();
    //void demand_rotation();
    //void set_setpoint();
    void process_pid();

    Mcp_ctrl_signals* get_mcp_signals();   
};

#endif