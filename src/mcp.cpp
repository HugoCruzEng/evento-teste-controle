#include <mcp.h>
#include <PID_v1.h>
//teste

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
    setRealimentacao(inputs);
    setSetPoint(setPoint);

    myPID->Compute();
    return myPosAtuador;
}
