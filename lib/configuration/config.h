#ifndef config_h
#define config_h
/*
ARDUINO SERVER - INTERFACE COM IHM				
Coils			        Holding registers	
Address	Name		        Address	Name
0	MCP_PARTIR		    0	MCP_SETROTACAO
1	MCP_PARAR		    1	VALOR_PID_P
2	MCP_FUNCIONADO		2	VALOR_PID_I
			            3	VALOR_PID_D
			            4	MCP_ROTACAOATUAL
			            5	MCP_POSATUADOR			

SIMULADOR SERVER - INTERFACE COM MODELO				
Coils			        Holding registers	
Address	Name		        Address	Name
0	MCP_PARTIR		    0	MCP_ROTACAOATUAL
1	MCP_PARAR		    1	MCP_POSATUADOR
2	MCP_FUNCIONADO			
*/


#define ERROR_REQUEST                       -1

#define HMI_NUMBERS_MAX_SIGNALS              20
#define MODEL_DIGITAL_NUMBERS_MAX_SIGNALS    20
#define MODEL_ANALOG_NUMBERS_MAX_SIGNALS     20

//CONFIGURATION IP MODEL
#define MODEL_IP_ADDRESS_0          192
#define MODEL_IP_ADDRESS_1          168
#define MODEL_IP_ADDRESS_2          0
#define MODEL_IP_ADDRESS_3          3

//Signals MODEL
//Signals interface Propulsion Subsystem
#define MODEL_OFFSET_DIGITAL_INPUT      0
#define MODEL_OFFSET_ANALOG_INPUT       2   //100
#define MODEL_OFFSET_DIGITAL_OUTPUT     5
#define MODEL_OFFSET_ANALOG_OUTPUT      8

//DIGITAL
//INPUTS
#define MODEL_DI_STATUS                 MODEL_OFFSET_DIGITAL_INPUT
//OUTPUTS
#define MODEL_DO_START_COMMAND          MODEL_OFFSET_DIGITAL_OUTPUT
#define MODEL_DO_STOP_COMMAND           MODEL_OFFSET_DIGITAL_OUTPUT + 1

//ANALOG
//INPUTS
#define MODEL_AI_ROTATION               MODEL_OFFSET_ANALOG_INPUT 
//OUTPUTS
#define MODEL_AO_POSITION               MODEL_OFFSET_ANALOG_OUTPUT

//Signals HMI
//OFFSET Registers
#define HMI_OFFSET_BOOL     0
#define HMI_OFFSET_INT      3 //100
#define HMI_OFFSET_DOUBLE   5 //200

//Bools
#define START_COMMAND_HMI	HMI_OFFSET_BOOL
#define STOP_COMMAND_HMI    HMI_OFFSET_BOOL + 1
#define STATUS_HMI          HMI_OFFSET_BOOL + 2

//Ints
#define DEMAND_HMI            HMI_OFFSET_INT
#define ROTATION_HMI          HMI_OFFSET_INT + 1

//double
#define KP_HMI                	HMI_OFFSET_DOUBLE
#define KI_HMI                	HMI_OFFSET_DOUBLE + 2
#define KD_HMI                	HMI_OFFSET_DOUBLE + 4
#define ACTUATOR_POSITION_HMI 	HMI_OFFSET_DOUBLE + 6

#endif