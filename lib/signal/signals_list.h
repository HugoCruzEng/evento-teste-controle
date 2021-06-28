#ifndef signals_list_h
#define signals_list_h

// This class implements all kind of interfaces necessary for communication between equipment/device controllers and HMI/plant
#include "signal.h"
#include "../configuration/config.h"
#include <vector>

extern std::vector<Digital_input*> digital_input_list;
extern std::vector<Analog_input*> analog_input_list;
extern std::vector<Digital_output*> digital_output_list;
extern std::vector<Analog_output*> analog_output_list;
extern std::vector<Hmi_signal<int>*> hmi_int_signal_list;
extern std::vector<Hmi_signal<double>*> hmi_double_signal_list;
extern std::vector<Hmi_signal<bool>*> hmi_bool_signal_list;

#endif