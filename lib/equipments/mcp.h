#ifndef mcp_ctrl_h
#define mcp_ctrl_h

#include "../signal/signal.h"
#include <PID_v1.h>

class Mcp_ctrl_signals {
public:
/*SIMULADOR SERVER - INTERFACE COM MODELO				
Coils			        Holding registers	
Address	Name		        Address	Name
0	MCP_PARTIR		    0	MCP_ROTACAOATUAL
1	MCP_PARAR		    1	MCP_POSATUADOR
2	MCP_FUNCIONADO			
*/ 
    Digital_input* status;
    Digital_output* start_command;
    Digital_output* stop_command;
    
    Analog_input* rotation;    
    Analog_output* actuator_position;

    Hmi_signal<bool>* start_command_hmi;
    Hmi_signal<bool>* stop_command_hmi;
    Hmi_signal<bool>* status_hmi;
    
    Hmi_signal<int>* demand_hmi;
    Hmi_signal<int>* rotation_hmi;
    Hmi_signal<double>* actuator_position_hmi;
    Hmi_signal<double>* kp_hmi;
    Hmi_signal<double>* ki_hmi;
    Hmi_signal<double>* kd_hmi;
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