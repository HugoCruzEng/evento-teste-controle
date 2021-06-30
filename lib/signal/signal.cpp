#include "../signal/signal.h"

std::vector<Digital_input*> digital_input_list;
std::vector<Analog_input*> analog_input_list;
std::vector<Digital_output*> digital_output_list;
std::vector<Analog_output*> analog_output_list;

std::vector<Hmi_signal<bool>*> hmi_bool_signal_list;
std::vector<Hmi_signal<int>*> hmi_int_signal_list;
std::vector<Hmi_signal<double>*> hmi_double_signal_list;

Signal::Signal() {
}

Signal::Signal(int id, char* description) : id(id), description(description) {
    
}

int Signal::get_id() {
    return this->id;
}

char* Signal::get_description() {
    return this->description;
}

//-------------------------------------------------------------------------------------------
// All implementation for digital signal
bool Digital_signal::get_value() {
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

    digital_input_list.push_back(this);
}

//-------------------------------------------------------------------------------------------
// All implementation for digital outputs
Digital_output::Digital_output(int id, char* description) {
    this->id = id;
    this->description = description;

    digital_output_list.push_back(this);
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

    analog_input_list.push_back(this);
}

//-------------------------------------------------------------------------------------------
// All implementation for analog outputs
Analog_output::Analog_output(int id, char* description) {
    this->id = id;
    this->description = description;

    analog_output_list.push_back(this);
}

//-------------------------------------------------------------------------------------------
// All implementation for hmi Signals
template<>
Hmi_signal<bool>::Hmi_signal(int id, char* description) {

    this->id = id;
    this->description = description;
    
    hmi_bool_signal_list.push_back(this);
}

template<>
Hmi_signal<int>::Hmi_signal(int id, char* description) {

    this->id = id;
    this->description = description;
    
    hmi_int_signal_list.push_back(this);
}

template<>
Hmi_signal<double>::Hmi_signal(int id, char* description) {

    this->id = id;
    this->description = description;
    
    hmi_double_signal_list.push_back(this);
}
