/*
  Modbus-Arduino Example - Modbus IP Client (ESP8266/ESP32)
  Write multiple coils to Slave device

  (c)2019 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/

#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else
 #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>

#include <PID_v1.h>

// Variáveis PID
//Define Variables we'll be connecting to
double Setpoint, Input, Output;
//Specify the links and initial tuning parameters
double Kp=0.009, Ki=0.26, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

//Variaveis de interface com a SIMULACAO
//ENTRADAS
#define SC_AN_MCP_ROTACAO 0
const int OFFSET_REG_IN_SIMU=0; 
const int NUM_IN_SIMU=1; //quatidade de defines de entrada SIMULACAO
uint16 REG_IN_SIMU[NUM_IN_SIMU]={0};
//SAIDAS
#define CS_AN_MCP_POSATUADOR 0
const int OFFSET_REG_OUT_SIMU=NUM_IN_SIMU; //OFFSET SAIDA=QUANTIDADE DE ENTRADAS 
const int NUM_OUT_SIMU=1; //qtde de defines de saida SIMULACAO
uint16 REG_OUT_SIMU[NUM_OUT_SIMU]={0}; 

//Variaveis de interface com a IHM
//ENTRADAS REG
#define IC_AN_MCP_ROTACAO 0
#define IC_AN_MCP_PIDP 1
#define IC_AN_MCP_PIDI 2
#define IC_AN_MCP_PIDD 3
const int OFFSET_REG_IN_IHM=0; 
const int NUM_IN_IHM=4;       //quatidade de defines de entrada SIMULACAO
unsigned int REG_IN_IHM [NUM_IN_IHM]={0};
//SAIDAS REG
#define CI_AN_MCP_ROTACAO 0
const int OFFSET_REG_OUT_IHM=NUM_IN_IHM; //OFFSET SAIDA=QUANTIDADE DE ENTRADAS 
const int NUM_OUT_IHM=1;              //qtde de defines de saida SIMULACAO
unsigned int REG_OUT_IHM[NUM_OUT_IHM]={0}; 

//ENTRADA COIL
#define IC_DG_MCP_PARTIR 0
#define IC_DG_MCP_PARAR 1
const int OFFSET_COIL_IN_IHM=0; 
const int NUM_IN_COIL=2; 
bool REG_COIL_IN_IHM [NUM_IN_COIL]={false};
//SAIDA COIL
#define CI_DG_MCP_FUNCIONANDO 0
const int OFFSET_COIL_OUT_IHM=NUM_IN_COIL;
const int NUM_OUT_COIL=1;
bool REG_COIL_OUT_IHM [NUM_OUT_COIL]={false};


int TOTAL_REG_IHM=NUM_OUT_IHM+NUM_IN_IHM;
int TOTAL_COIL_IHM=NUM_IN_COIL+NUM_OUT_COIL;

const int REG = 0;                   // Modbus Coils Offse
const int COUNT = 5;                 // Count of Coils
IPAddress remote(192, 168, 0, 5);    // Address of Modbus Slave device

ModbusIP mb,mbIHM;  // ModbusIP object

bool statusMCP=false;

long ts;

uint16_t writeROTACAO_MCP(TRegister* reg, uint16_t val) {
    REG_IN_IHM[IC_AN_MCP_ROTACAO] = val;
    Setpoint=REG_IN_IHM[IC_AN_MCP_ROTACAO];
    Input=REG_IN_SIMU[SC_AN_MCP_ROTACAO];
    //refreshVisor = HIGH;
  return val;
}

uint16_t partirMCP(TRegister* reg, uint16_t val) {
     if(val){
      statusMCP=true;
      Setpoint = REG_IN_IHM[IC_AN_MCP_ROTACAO];
      Input = REG_IN_SIMU [SC_AN_MCP_ROTACAO];
     
      //turn the PID on
      myPID.SetMode(AUTOMATIC);

      //REG_OUT_SIMU[CS_AN_MCP_POSATUADOR] = (uint16) Output;
      REG_OUT_SIMU[CS_AN_MCP_POSATUADOR]=Output;

      Serial.println(Setpoint);
      Serial.println(Input );
      Serial.println(Output );
     }
     
         //refreshVisor = HIGH;
  return val;
}

uint16_t pararMCP(TRegister* reg, uint16_t val) {
  if( val != 0 ){
       //turn the PID off
        Setpoint = 0;
        statusMCP=false;
  }
  return val;
}

uint16_t writePID_P(TRegister* reg, uint16_t val) {
  Kp=val;
  myPID.SetTunings(Kp,Ki,Kd);
  return val;
}

uint16_t writePID_I(TRegister* reg, uint16_t val) {
  Ki=val;
  myPID.SetTunings(Kp,Ki,Kd);
  return val;
}

uint16_t writePID_D(TRegister* reg, uint16_t val) {
  Kd=val;
  myPID.SetTunings(Kp,Ki,Kd);
  return val;
}

bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Modbus Transaction callback
  if (event != Modbus::EX_SUCCESS)                  // If transaction got an error
    Serial.printf("Modbus result: %02X\n", event);  // Display Modbus error code
  if (event == Modbus::EX_TIMEOUT) {    // If Transaction timeout took place
    mb.disconnect(remote);              // Close connection to slave and
    mb.dropTransactions();              // Cancel all waiting transactions
  }
  return true;
}

void processaPID(){
  //if( (REG_OUT_SIMU[0] != Input) || ( REG_IN_SIMU[SC_AN_MCP_ROTACAO] =! Setpoint)){
  Input = REG_IN_SIMU [SC_AN_MCP_ROTACAO];

  if(statusMCP){
    Setpoint=REG_IN_IHM[IC_AN_MCP_ROTACAO];
  }
  else {
    Setpoint=0;
  }
  
  myPID.Compute();

  REG_OUT_SIMU[CS_AN_MCP_POSATUADOR] = Output;
    
  //}
}


void setup() {
  Serial.begin(115200);
 
  WiFi.begin("pontes","12345678");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mb.client();
  mbIHM.server();
  //ADICIONA REGISTRADORES DO SERVIDOR
  mbIHM.addHreg(OFFSET_REG_IN_IHM+IC_AN_MCP_ROTACAO,REG_IN_IHM[IC_AN_MCP_ROTACAO],1);
  mbIHM.addHreg(OFFSET_REG_IN_IHM+IC_AN_MCP_PIDP,REG_IN_IHM[IC_AN_MCP_PIDP],1);
  mbIHM.addHreg(OFFSET_REG_IN_IHM+IC_AN_MCP_PIDI,REG_IN_IHM[IC_AN_MCP_PIDI],1);
  mbIHM.addHreg(OFFSET_REG_IN_IHM+IC_AN_MCP_PIDD,REG_IN_IHM[IC_AN_MCP_PIDD],1);
  mbIHM.addHreg(OFFSET_REG_OUT_IHM+CI_AN_MCP_ROTACAO,REG_OUT_IHM[CI_AN_MCP_ROTACAO],1);
  //ADICIONA COIL DA IHM
  mbIHM.addCoil(OFFSET_COIL_IN_IHM+IC_DG_MCP_PARTIR,REG_COIL_IN_IHM[IC_DG_MCP_PARTIR]);
  mbIHM.addCoil(OFFSET_COIL_IN_IHM+IC_DG_MCP_PARAR,REG_COIL_IN_IHM[IC_DG_MCP_PARAR]);
  mbIHM.addCoil(OFFSET_COIL_OUT_IHM+CI_DG_MCP_FUNCIONANDO,REG_COIL_OUT_IHM[CI_DG_MCP_FUNCIONANDO]);
  
  //DECLARA FUNÇÕES ASSOCIADAS A ALTERAÇÃO DA LEITURA DOS REGISTERS
  mbIHM.onSetHreg(OFFSET_REG_IN_IHM+IC_AN_MCP_ROTACAO, writeROTACAO_MCP);
  mbIHM.onSetHreg(OFFSET_REG_IN_IHM+IC_AN_MCP_PIDP, writePID_P);
  mbIHM.onSetHreg(OFFSET_REG_IN_IHM+IC_AN_MCP_PIDI, writePID_I);
  mbIHM.onSetHreg(OFFSET_REG_IN_IHM+IC_AN_MCP_PIDD, writePID_D);
  //DECLARA FUNÇÕES ASSOCIADAS A ALTERAÇÃO DA LEITURA DOS coils
  mbIHM.onSetCoil(OFFSET_COIL_IN_IHM+IC_DG_MCP_PARTIR,partirMCP);
  mbIHM.onSetCoil(OFFSET_COIL_IN_IHM+IC_DG_MCP_PARAR,pararMCP);
 
}

uint16 resInputSimu1=0;
uint16 resInputSimu2=0;
uint16 resInputSimu[1]={0};

uint8_t show = 100;

void loop() {
    if (!mb.isConnected(remote)) {   // Check if connection to Modbus Slave is established
        mb.connect(remote);           // Try to connect if no connection
        Serial.print(".");
    }
    mb.readHreg(remote,0,REG_IN_SIMU,1,cb,1);
    mb.task(); // Modbus task
    mbIHM.task();

if (!show--) { 
    //Função PID 0
    processaPID();

    Serial.print(REG_IN_SIMU[SC_AN_MCP_ROTACAO]);
    Serial.print(" ");
    Serial.print(REG_IN_IHM[IC_AN_MCP_ROTACAO]);
    Serial.print(" ");
    Serial.println(REG_OUT_SIMU[CS_AN_MCP_POSATUADOR]);

    //STATUS FUNCIONANDO PARA A IHM
    if(REG_IN_SIMU[SC_AN_MCP_ROTACAO]>500){
      REG_OUT_IHM[CI_DG_MCP_FUNCIONANDO]=true;
    }
    else if(REG_IN_SIMU[SC_AN_MCP_ROTACAO]<300){
      REG_OUT_IHM[CI_DG_MCP_FUNCIONANDO]=false;
    }


    show = 100;
  } 
    //ATUALIZA ESCRITAS
    //ESCRITA DAS SAIDA IHM
    //REGS
    mbIHM.Hreg(OFFSET_REG_OUT_IHM+CI_AN_MCP_ROTACAO,REG_OUT_IHM[CI_AN_MCP_ROTACAO]);
    //COILS
    mbIHM.Coil(OFFSET_COIL_OUT_IHM+CI_DG_MCP_FUNCIONANDO,(bool) REG_OUT_IHM[CI_DG_MCP_FUNCIONANDO]);
    //ESCRITA SAIDAS DA SIMULACAO
    mb.writeHreg(remote,OFFSET_REG_OUT_SIMU+CS_AN_MCP_POSATUADOR,&REG_OUT_SIMU[0],1,cb,1);
}
