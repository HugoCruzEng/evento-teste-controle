#include "../interface/interface.h"

#ifndef signal_h
#define signal_h 

// This class implements all kind of signal types necessary for the equipment/device controllers and HMI 
class Signal {

protected:
    int id;
    char* description;  // TODO: definir Tag para descrever o Sinal
    //Signal(int id, char* description);

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

public:
    double value;
    
public:
    double get_value();
    void set_value(double value);
};

class Analog_input : public Analog_signal {
    
public:
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
    T treat_signal();

public:
    Hmi_signal(int id, char* description);
    T get_value();
    void set_value(T value);
};

#endif