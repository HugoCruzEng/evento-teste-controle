#include "../signal/signal.h"

Signal::Signal(){
}

Signal::Signal(int id, char* description) : id(id), description(description){
    
}

int Signal::get_id(){
    return this->id;
}

char* Signal::get_description(){
    return this->description;
}

//-------------------------------------------------------------------------------------------
// All implementation for digital signal
bool Digital_signal::get_value(){
    return this->value;
}

void Digital_signal::set_value(bool value) {
    this->value = value;
}

//-------------------------------------------------------------------------------------------
// All implementation for digital inputs

Digital_input::Digital_input(int id, char* description, int time_millis) {
    this->id = id;
    this->description = description;
}

//-------------------------------------------------------------------------------------------
// All implementation for digital outputs

Digital_output::Digital_output(int id, char* description) {
    this->id = id;
    this->description = description;
}

//-------------------------------------------------------------------------------------------
// All implementation for analog signals

double Analog_signal::get_value(){
    return this->value;
}

void Analog_signal::set_value(double value) {
    this->value = value;
}

//-------------------------------------------------------------------------------------------
// All implementation for analog inputs

Analog_input::Analog_input(int id, char* description) {
    this->id = id;
    this->description = description;
}

//-------------------------------------------------------------------------------------------
// All implementation for analog outputs

Analog_output::Analog_output(int id, char* description) {
    this->id = id;
    this->description = description;
}

//-------------------------------------------------------------------------------------------
// All implementation for hmi Signals
template <class T>
Hmi_signal<T>::Hmi_signal(int id, char* description) {
    this->id = id;
    this->description = description;
}

/*template <class T>
T Hmi_signal<T>::get_value(){
    return this->value;
}

template <class T>
void Hmi_signal<T>::set_value(T value){
    this->value = value;
}*/