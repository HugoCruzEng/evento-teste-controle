#ifndef interface_h
#define interface_h

// This class implements all kind of interfaces necessary for communication between equipment/device controllers and HMI/plant
#include "../signal/signal.h"
#include "../configuration/config.h"

#include <vector>

#include <ModbusIP_ESP8266.h>

class Interface {
    
    private:
        void setup_hmi_data();

    public:
        Interface();
        
        void start_signal_interfaces(); 
        void model_receive_data();
        void model_send_data();
        void update_interface_data();
};

#endif