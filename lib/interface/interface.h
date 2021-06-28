#ifndef interface_h
#define interface_h

// This class implements all kind of interfaces necessary for communication between equipment/device controllers and HMI/plant
#include "../signal/signals_list.h"
#include "../configuration/config.h"

#include <vector>

#include <ModbusIP_ESP8266.h>

class Interface {
    
    private:
        void model_receive_data();
        void model_send_data();
        
        void setup_hmi_data();
        void hmi_receive_data();
        void hmi_send_data();

    public:
        Interface();
        
        void start_signal_interfaces(); 
        void receive_data();
        void send_data();
};

#endif