#ifndef signal_h
#define signal_h 

#include <vector>
#include "../configuration/config.h"

// This class implements all kind of signal types necessary for the equipment/device controllers and HMI 
class Signal {

protected:
    int id;
    char* description;  // TODO: definir Tag para descrever o Sinal

public:
    Signal();
    Signal(int id, char* description);
    int get_id();   
    char* get_description();
};

class Digital_signal : public Signal {

private:
    bool value;

public:
    bool get_value();
    void set_value(bool value);
};

class Digital_input : public Digital_signal {

private:   
    int time_millis;
    bool treat_signal();

public:
    Digital_input(int id, char* description, int time_millis = 2000);
};

class Digital_output : public Digital_signal {
    
public:
    Digital_output(int id, char* description);
};

class Analog_signal : public Signal{

private:
    double value;
    
public:
    double get_value();
    void set_value(double value);
};

class Analog_input : public Analog_signal {
    
private:
    double* previous_inputs;
    double treat_signal();
    
public:
    Analog_input(int id, char* description);
};

class Analog_output : public Analog_signal {
    
public:
    Analog_output(int id, char* description);
};

template<class T>
class Hmi_signal : public Signal {
    
private:
    T value;
    //T treat_signal();

public:
    Hmi_signal<T>(int id, char* description);

    T get_value(){
        return this->value;
    }
    
    void set_value(T value){
        this->value = value;
    }
};

extern std::vector<Digital_input*> digital_input_list;
extern std::vector<Analog_input*> analog_input_list;
extern std::vector<Digital_output*> digital_output_list;
extern std::vector<Analog_output*> analog_output_list;

extern std::vector<Hmi_signal<bool>*> hmi_bool_signal_list;
extern std::vector<Hmi_signal<int>*> hmi_int_signal_list;
extern std::vector<Hmi_signal<double>*> hmi_double_signal_list;

#endif
