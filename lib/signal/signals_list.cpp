#include "signals_list.h"

Signals_list signals_list;

Signals_list::Signals_list(){
    model_digital_signals_index = 0;
    model_analog_signals_index = 0;
}

/*template<typename T>
T* Signals_list::add(T* sl){
  
    if(dynamic_cast<Hmi_signal<double>*>(sl) != nullptr || 
        dynamic_cast<Hmi_signal<int>*>(sl) != nullptr ||
        dynamic_cast<Hmi_signal<bool>*>(sl) != nullptr
        ){
        if(hmi_signals_index < HMI_NUMBERS_MAX_SIGNALS){
            hmi_signals[hmi_signals_index] = sl;
            hmi_signals_index++;
        }
    }
    else if (dynamic_cast<Digital_signal*>(sl) != nullptr){
        if(model_digital_signals_index < MODEL_DIGITAL_NUMBERS_MAX_SIGNALS){
            model_digital_signals[model_digital_signals_index] = sl;
            model_digital_signals_index++;
        }
    }
    else if (dynamic_cast<Analog_signal*>(sl) != nullptr){
        if(model_analog_signals_index < MODEL_ANALOG_NUMBERS_MAX_SIGNALS){
            model_analog_signals[model_analog_signals_index] = sl;
            model_analog_signals_index++;
        }
    }

    return sl;
}*/

/*
Hmi_signal* Signals_list::add(Hmi_signal* sl){
    if(hmi_signals_index < HMI_NUMBERS_MAX_SIGNALS){
        //mb_hmi.addHreg(sl->get_id(), slget_value()->); // paramos aqui!
       
        hmi_signals[hmi_signals_index] = sl;
        hmi_signals_index++;
    }
    return sl;
}
*/

void Signals_list::add(Digital_signal* sl){
    if(model_digital_signals_index < MODEL_DIGITAL_NUMBERS_MAX_SIGNALS){
        model_digital_signals[model_digital_signals_index] = sl;
        model_digital_signals_index++;
    }
}


void Signals_list::add(Analog_signal* sl){
    if(model_analog_signals_index < MODEL_ANALOG_NUMBERS_MAX_SIGNALS){
        model_analog_signals[model_analog_signals_index] = sl;
        model_analog_signals_index++;
    }
}

Analog_signal* Signals_list::get_model_analog_signal_by_id(int id){
    for(int i = 0; i < model_analog_signals_index; i++){
        if(model_analog_signals[i]->get_id() == id){
            return model_analog_signals[i];
        }
        return nullptr; 
    }
}

Iterator<Digital_signal*>* Signals_list::get_digital_signals_iterator(){
    return new Iterator<Digital_signal*>(model_digital_signals, model_digital_signals_index);
}

Iterator<Analog_signal*>* Signals_list::get_analog_signals_iterator(){
    return new Iterator<Analog_signal*>(model_analog_signals, model_analog_signals_index);
}

template<class T>
Iterator<T>::Iterator(T* list, int size) : list(list), size(size) {
    index = 0;
}

/*template<class T>
T Iterator<T>::next(){
    //if(index < size){
        return list[index++];
    //}
    //else{
     //   return nullptr;
    //}
}

template<class T>
bool Iterator<T>::has_next(){
    return index < size;
}

template class Iterator<Digital_signal>;
template class Iterator<Analog_signal>;
*/