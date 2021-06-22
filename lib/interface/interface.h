#ifndef interface_h
#define interface_h

// This class implements all kind of interfaces necessary for communication between equipment/device controllers and HMI/plant
#include "../signal/signal.h"
#include "../configuration/config.h"

//#include <ModbusIP_ESP8266.h>

class Interface {
    
    private:
        int hmi_signals_index;
        Signal* hmi_signals[HMI_NUMBERS_MAX_SIGNALS];

        int model_digital_signals_index;
        Signal* model_digital_signals[MODEL_DIGITAL_NUMBERS_MAX_SIGNALS];

        int model_analog_signals_index;
        Signal* model_analog_signals[MODEL_ANALOG_NUMBERS_MAX_SIGNALS];

        // ModbusIP object
        //ModbusIP mb_model;
        //ModbusIP mb_hmi;
        
    public:
        Interface();
        void start_signal_interfaces(); 
              
        //void receive_data();
        //void send_data();
        
        void add_hmi_signal(Signal* sl);
        void add_model_digital_signal(Signal* sl);
        void add_model_analog_signal(Signal* sl);
        
        int get_hmi_signal_index(Signal* sl);
        char* get_hmi_description_signal(int index);
        int get_hmi_id_signal(int index);

        int get_model_digital_signal_index(Signal* sl);
        char* get_model_digital_description_signal(int index);
        int get_model_digital_id_signal(int index);

        int get_model_analog_signal_index(Signal* sl);
        char* get_model_analog_description_signal(int index);
        int get_model_analog_id_signal(int index);
};

extern Interface itf;

#endif