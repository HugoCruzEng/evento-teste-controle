#ifndef signals_list_h
#define signals_list_h

// This class implements all kind of interfaces necessary for communication between equipment/device controllers and HMI/plant
#include "signal.h"
#include "../configuration/config.h"

template<class T>
class Iterator {
private:
    T* list;
    int size;
    int index;

public:
    Iterator<T>(T* list, int size);
    T next(){
        if(index < size){
            return list[index++];
        }
        return nullptr;
        
    }
    bool has_next(){
        return index < size;
    }
};

class Signals_list {
    
    private:
        //int hmi_signals_index;
        //Signal* hmi_signals[HMI_NUMBERS_MAX_SIGNALS];

        int model_digital_signals_index;
        Digital_signal* model_digital_signals[MODEL_DIGITAL_NUMBERS_MAX_SIGNALS];

        int model_analog_signals_index;
        Analog_signal* model_analog_signals[MODEL_ANALOG_NUMBERS_MAX_SIGNALS];
        
    public:
        Signals_list();
        Iterator<Digital_signal*>* get_digital_signals_iterator();
        Iterator<Analog_signal*>* get_analog_signals_iterator();

        /*template<typename T>
        T* add(T* sl);*/
        
        void add(Digital_signal* sl);
        void add(Analog_signal* sl);
        
        Analog_signal* get_model_analog_signal_by_id(int id);
        //Digital_signal* get_digital
        /*
        int get_hmi_signal_index(Signal* sl);
        char* get_hmi_description_signal(int index);
        int get_hmi_id_signal(int index);

        int get_model_digital_signal_index(Signal* sl);
        char* get_model_digital_description_signal(int index);
        int get_model_digital_id_signal(int index);

        int get_model_analog_signal_index(Signal* sl);
        char* get_model_analog_description_signal(int index);
        int get_model_analog_id_signal(int index);
        */
};

extern Signals_list signals_list;

#endif