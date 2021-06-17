#include "../Signal/Signal.h"

Signal::Signal(){
}

Signal::Signal(int id, char* description) : id(id), description(description){
    itf.add_hmi_signal(this);
}

int Signal::get_id(){
    return this->id;
}

char* Signal::get_description(){
    return this->description;
}

//-------------------------------------------------------------------------------------------
// All implementation for digital inputs


Digital_input::Digital_input(int id, char* description, int time_millis) {
    this->id = id;
    this->description = description;
}

bool Digital_input::get_value(){
    return this->value;
}

void Digital_input::set_value(bool value) {
    this->value = value;
}


//-------------------------------------------------------------------------------------------
// All implementation for digital outputs

Digital_output::Digital_output(int id, char* description) {
    this->id = id;
    this->description = description;
}

bool Digital_output::get_value(){
    return this->value;
}

void Digital_output::set_value(bool value) {
    this->value = value;
}

//-------------------------------------------------------------------------------------------
// All implementation for analog inputs

Analog_input::Analog_input(int id, char* description) {
    this->id = id;
    this->description = description;
}

double Analog_input::get_value(){
    return this->value;
}

void Analog_input::set_value(double value) {
    this->value = value;
}

//-------------------------------------------------------------------------------------------
// All implementation for analog outputs

Analog_output::Analog_output(int id, char* description) {
    this->id = id;
    this->description = description;
}

double Analog_output::get_value(){
    return this->value;
}

void Analog_output::set_value(double value) {
    this->value = value;
}

//-------------------------------------------------------------------------------------------

