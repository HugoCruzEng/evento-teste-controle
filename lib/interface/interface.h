#ifndef interface_h
#define interface_h

// This class implements all kind of interfaces necessary for communication between equipment/device controllers and HMI/plant
#include "../signal/signals_list.h"
#include "../configuration/config.h"

#include <ModbusIP_ESP8266.h>

class Interface {
    
    private:
        // ModbusIP object
        //ModbusIP mb_model;
        //ModbusIP mb_hmi;
        
        //IPAddress model_address(MODEL_IP_ADDRESS_0, MODEL_IP_ADDRESS_1, MODEL_IP_ADDRESS_2, MODEL_IP_ADDRESS_3);    // Address of Modbus servidor Simulacao
    public:
        Interface();
        
        void start_signal_interfaces(); 
              
        void receive_data(uint16* teste);
        void send_data();

        //bool treat_registers_after_read_mb(Modbus::ResultCode event, uint16_t transactionId, void* data); // Modbus Transaction callback

};

#endif