#ifndef config_h
#define config_h

#define ERROR_REQUEST                       -1

#define HMI_NUMBERS_MAX_SIGNALS              20
#define MODEL_DIGITAL_NUMBERS_MAX_SIGNALS    20
#define MODEL_ANALOG_NUMBERS_MAX_SIGNALS     20

//Signals interface Propulsion Subsystem
//DIGITAL
#define MODEL_DO_START_COMMAND      0
#define MODEL_DO_STOP_COMMAND       1

#define MODEL_IP_ADDRESS_0      192
#define MODEL_IP_ADDRESS_1      168
#define MODEL_IP_ADDRESS_2      0
#define MODEL_IP_ADDRESS_3      2

/*const int OFFSET_REG_IN_SIMU=0; 
const int NUM_IN_SIMU=1; //quatidade de defines de entrada SIMULACAO
uint16 REG_IN_SIMU[NUM_IN_SIMU]={0};

//SAIDAS
#define CS_AN_MCP_POSATUADOR 0
const int OFFSET_REG_OUT_SIMU=NUM_IN_SIMU; //OFFSET SAIDA=QUANTIDADE DE ENTRADAS 
const int NUM_OUT_SIMU=1; //qtde de defines de saida SIMULACAO
uint16 REG_OUT_SIMU[NUM_OUT_SIMU]={0}; */

#endif