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

class Digital_input : public Signal {

private:   
    bool value;
    int time_millis;
    bool treat_signal();

public:
    Digital_input(int id, char* description, int time_millis = 2000);
    bool get_value();
    void set_value(bool value);
};


class Digital_output : public Signal {

private:
    bool value;
    
public:
    Digital_output(int id, char* description);
    bool get_value();
    void set_value(bool value);
};


class Analog_input : public Signal {
    
private:
    double value;
    double* previous_inputs;
    double treat_signal();
    
public:
    Analog_input(int id, char* description);
    double get_value();
    void set_value(double value);
};

class Analog_output : public Signal {
    
private:
    double value;
    
public:
    Analog_output(int id, char* description);
    //double treat_signal();
    double get_value();
    void set_value(double value);
};

template<class T>
class Hmi_signal : public Signal {
    
private:
    T value;
    T treat_signal();

public:
    T get_value();
    void set_value(T value);
};
#endif