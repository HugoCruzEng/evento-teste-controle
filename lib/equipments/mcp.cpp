#include "../equipments/mcp.h"

Mcp_ctrl::Mcp_ctrl(Mcp_ctrl_signals* mcp_signals) : mcp_signals(mcp_signals)
{
    pid = new PID( 
        &my_rotation, 
        &my_actuator_position, 
        &my_setpoint,
        mcp_signals->kp_hmi->get_value(),
        mcp_signals->ki_hmi->get_value(),
        mcp_signals->kd_hmi->get_value(), 
        DIRECT
    );
}

Mcp_ctrl::~Mcp_ctrl()
{
}

void Mcp_ctrl::process_pid(){
    my_rotation = mcp_signals->rotation->get_value();
    my_setpoint = mcp_signals->demand_hmi->get_value(); //TODO: Falta método para relacionar demanda com set point

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

/*
mcp::mcp(bool mcp_Status, double mcp_RPM, double mcp_PosAtuador, double STpoint, double Kp, double Ki, double Kd){
    myStatusMCP=mcp_Status;
    myRotacao=mcp_RPM;
    myRealimentacao=myRotacao;
    myPosAtuador=mcp_PosAtuador;
    mySetpoint=STpoint;
    myKp=Kp;
    myKi=Ki;
    myKd=Kd;

    //Specify the links and initial tuning parameters
    //double Kp=0.009, Ki=0.26, Kd=0; //valores iniciais de controle
    myPID = new PID(&myRealimentacao, &myPosAtuador, &mySetpoint,Kp,Ki,Kd,DIRECT);

    //turn the PID on
    myPID->SetMode(AUTOMATIC);

    //itf.start_signal_interfaces();
    //Interface_modbus interface1;
    Signal sg1(100, "Sinal1");
    Signal sg2(101, "Sinal2");
    Signal sg3(102, "Sinal3");
}

bool mcp::getStatusMCP(){
    return myStatusMCP; 
}

unsigned short int mcp::getRotacaoMCP(){
    return myRotacao;
}

void mcp:: partirMCP(){
    myStatusMCP=1;
}

void mcp::pararMCP(){
    myStatusMCP=0;
}

void mcp::demandaRotacao(unsigned short int demandRotacao){
    switch(myStatusMCP){
        case 0:
            mySetpoint=0;
            break;   
        case 1:
            mySetpoint=demandRotacao;
            break;
        }
}

unsigned short int mcp::getPosAtuador(){
    return myPosAtuador;
}

unsigned short int mcp::getSetPoint(){
    return mySetpoint;
}

unsigned short int mcp::getRealimentacao(){
    return myRealimentacao;
}

void mcp::setSetPoint(unsigned short int setpoints){
    mySetpoint=setpoints;
}

void mcp::setRealimentacao(unsigned short int realimentacao){
    myRealimentacao=realimentacao;
}

void mcp::setKp(unsigned short int Kp){
    myKp=Kp;
    myPID->SetTunings(myKp,myKi,myKd);
}

void mcp::setKi(unsigned short int Ki){
    myKi=Ki;
    myPID->SetTunings(myKp,myKi,myKd);
}

void mcp::setKd(unsigned short int Kd){
    myKd=Kd;
    myPID->SetTunings(myKp,myKi,myKd);
}

double mcp::processaPID(unsigned short int inputs, unsigned short int setPoint){
  //if( (REG_OUT_SIMU[0] != Input) || ( REG_IN_SIMU[SC_AN_MCP_ROTACAO] =! Setpoint)){
    mySetpoint=inputs; //setRealimentacao(inputs);
    setSetPoint(setPoint);

    myPID->Compute();
    return myPosAtuador;
}
*/