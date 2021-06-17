#include "../Interface/Interface.h"

Interface itf;

Interface::Interface(){

}

void Interface::start_signal_interfaces(){
    
    //mb_hmi.server();
    //mb_model.client();

    /*mbIHM.addHreg(OFFSET_REG_IN_IHM+IC_AN_MCP_ROTACAO,REG_IN_IHM[IC_AN_MCP_ROTACAO],1);
    mbIHM.addHreg(OFFSET_REG_IN_IHM+IC_AN_MCP_PIDP,REG_IN_IHM[IC_AN_MCP_PIDP],1);
    mbIHM.addHreg(OFFSET_REG_IN_IHM+IC_AN_MCP_PIDI,REG_IN_IHM[IC_AN_MCP_PIDI],1);
    mbIHM.addHreg(OFFSET_REG_IN_IHM+IC_AN_MCP_PIDD,REG_IN_IHM[IC_AN_MCP_PIDD],1);
    mbIHM.addHreg(OFFSET_REG_OUT_IHM+CI_AN_MCP_ROTACAO,REG_OUT_IHM[CI_AN_MCP_ROTACAO],1);
    //ADICIONA COIL DA IHM
    mbIHM.addCoil(OFFSET_COIL_IN_IHM+IC_DG_MCP_PARTIR,REG_COIL_IN_IHM[IC_DG_MCP_PARTIR]);
    mbIHM.addCoil(OFFSET_COIL_IN_IHM+IC_DG_MCP_PARAR,REG_COIL_IN_IHM[IC_DG_MCP_PARAR]);
    mbIHM.addCoil(OFFSET_COIL_OUT_IHM+CI_DG_MCP_FUNCIONANDO,REG_COIL_OUT_IHM[CI_DG_MCP_FUNCIONANDO]);
    */
}

void Interface::add_hmi_signal(Signal* sl){
    if(hmi_signals_index < HMI_NUMBERS_MAX_SIGNALS){
        hmi_signals[hmi_signals_index] = sl;
        hmi_signals_index++;
    }
}


void Interface::add_model_digital_signal(Signal* sl){
    if(model_digital_signals_index < MODEL_DIGITAL_NUMBERS_MAX_SIGNALS){
        model_digital_signals[model_digital_signals_index] = sl;
        model_digital_signals_index++;
    }
}

void Interface::add_model_analog_signal(Signal* sl){
    if(model_analog_signals_index < MODEL_ANALOG_NUMBERS_MAX_SIGNALS){
        model_analog_signals[model_analog_signals_index] = sl;
        model_analog_signals_index++;
    }
}

int Interface::get_hmi_signal_index(Signal* sl){
    for(int i = 0; i < hmi_signals_index; i++){
        if(hmi_signals[i]->get_id() == sl->get_id()){
            return i;
        }
    }
    return ERROR_REQUEST;
}

char* Interface::get_hmi_description_signal(int index){
    return hmi_signals[index]->get_description();
}

int Interface::get_hmi_id_signal(int index){
    return hmi_signals[index]->get_id();
}

int Interface::get_model_digital_signal_index(Signal* sl){
    for(int i = 0; i < model_digital_signals_index; i++){
        if(model_digital_signals[i]->get_id() == sl->get_id()){
            return i;
        }
    }
    return ERROR_REQUEST;
}

char* Interface::get_model_digital_description_signal(int index){
    return model_digital_signals[index]->get_description();
}

int Interface::get_model_digital_id_signal(int index){
    return model_digital_signals[index]->get_id();
}

int Interface::get_model_analog_signal_index(Signal* sl){
    for(int i = 0; i < model_analog_signals_index; i++){
        if(model_analog_signals[i]->get_id() == sl->get_id()){
            return i;
        }
    }
    return ERROR_REQUEST;
}

char* Interface::get_model_analog_description_signal(int index){
    return model_analog_signals[index]->get_description();
}

int Interface::get_model_analog_id_signal(int index){
    return model_analog_signals[index]->get_id();
}
