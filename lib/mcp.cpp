

#include <mcp.h>
#include <PID_v1.h>
//teste

mcp::mcp(bool mcp_Status, double mcp_RPM, double mcp_PosAtuador, double STpoint, double Kp, double Ki, double Kd){
    myStatusMCP=mcp_Status;
    myRotacao=mcp_RPM;
    Realimentacao=myRotacao;
    myPosAtuador=mcp_PosAtuador;
    Setpoint=STpoint;
    myKp=Kp;
    myKi=Ki;
    myKd=Kd;

    //Specify the links and initial tuning parameters
    //double Kp=0.009, Ki=0.26, Kd=0; //valores iniciais de controle
    myPID = new PID(&Realimentacao, &myPosAtuador, &Setpoint,Kp,Ki,Kd, DIRECT);
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
            Setpoint=0;
            break;   
        case 1:
            Setpoint=demandRotacao;
            break;
        }
}

double mcp::getPosAtuador(){
    return myPosAtuador;
}

double mcp::getSetPoint(){
    return Setpoint;
}

double mcp::getRealimentacao(){
    return Realimentacao;
}

void mcp::setSetPoint(double setpoints){
    Setpoint=setpoints;
}

void mcp::setRealimentacao(double realimentacao){
    Realimentacao=realimentacao;
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
    return getRotacaoMCP();
}
