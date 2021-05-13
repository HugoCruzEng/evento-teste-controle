

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
    myPID = new PID(&myRealimentacao, &myPosAtuador, &mySetpoint,Kp,Ki,Kd, DIRECT);

    //turn the PID on
    myPID->SetMode(AUTOMATIC);
}

bool mcp::getStatusMCP(){
    return myStatusMCP; 
}

unsigned int mcp::getRotacaoMCP(){
    return myRotacao;
}

void mcp:: partirMCP(){
    myStatusMCP=1;
}

void mcp::pararMCP(){
    myStatusMCP=0;
    }

void mcp::demandaRotacao(double demandRotacao){
    switch(myStatusMCP){
        case 0:
            mySetpoint=0;
            break;   
        case 1:
            mySetpoint=demandRotacao;
            break;
        }
}

double mcp::getPosAtuador(){
    return myPosAtuador;
}

double mcp::getSetPoint(){
    return mySetpoint;
}

double mcp::getRealimentacao(){
    return myRealimentacao;
}

void mcp::setSetPoint(double setpoints){
    mySetpoint=setpoints;
}

void mcp::setRealimentacao(double realimentacao){
    myRealimentacao=realimentacao;
}

void mcp::setKp(double Kp){
    myKp=Kp;
    myPID->SetTunings(myKp,myKi,myKd);
}

void mcp::setKi(double Ki){
    myKi=Ki;
    myPID->SetTunings(myKp,myKi,myKd);
}

void mcp::setKd(double Kd){
    myKd=Kd;
    myPID->SetTunings(myKp,myKi,myKd);
}

double mcp::processaPID(double inputs, double setPoint){
  //if( (REG_OUT_SIMU[0] != Input) || ( REG_IN_SIMU[SC_AN_MCP_ROTACAO] =! Setpoint)){
setRealimentacao(inputs);

  if(myStatusMCP){
    setSetPoint(setPoint);
  }
  else {
    setSetPoint(0); 
  }
    myPID->Compute();
    return getPosAtuador();
}
