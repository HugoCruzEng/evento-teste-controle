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
    void process_pid();

    Mcp_ctrl_signals* get_mcp_signals();   
};

/*
#include <PID_v1.h>
#include "../signal/signal.h"

class mcp {
    public:
    //estados do MCP
       // #define mcpParado 0
       // #define mcpFuncionando 1
   
    //construtor
        mcp(bool, double, double, double, double, double, double);

        void partirMCP();
        void pararMCP();
        void demandaRotacao(unsigned short int);
        void setSetPoint(unsigned short int);
        void setRealimentacao(unsigned short int);
        void setKp(unsigned short int);
        void setKi(unsigned short int);
        void setKd(unsigned short int);
        bool getStatusMCP();
        unsigned short int getRotacaoMCP();
        unsigned short int getPosAtuador();
        unsigned short int getSetPoint();
        unsigned short int getRealimentacao();
        
        double processaPID(unsigned short int, unsigned short int);

    private:
        bool myStatusMCP;
        unsigned short myRotacao;
        // Variáveis PID
        double mySetpoint, myRealimentacao, myPosAtuador;
        double myKp, myKi, myKd;        
        PID *myPID;
        //PID myPID;

};
*/
#endif