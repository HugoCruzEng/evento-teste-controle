#include "signals_list.h"

std::vector<Digital_input*> digital_input_list;
std::vector<Analog_input*> analog_input_list;
std::vector<Digital_output*> digital_output_list;
std::vector<Analog_output*> analog_output_list;
std::vector<Hmi_signal<int>*> hmi_int_signal_list;
std::vector<Hmi_signal<double>*> hmi_double_signal_list;
std::vector<Hmi_signal<bool>*> hmi_bool_signal_list;
