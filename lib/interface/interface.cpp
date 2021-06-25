#include "../Interface/Interface.h"

ModbusIP mb_model;
uint16 mb_analog_read_buffer[MODEL_ANALOG_NUMBERS_MAX_SIGNALS];
bool mb_digital_read_buffer[MODEL_DIGITAL_NUMBERS_MAX_SIGNALS];

IPAddress model_address(
    (uint8_t) MODEL_IP_ADDRESS_0, 
    (uint8_t) MODEL_IP_ADDRESS_1, 
    (uint8_t) MODEL_IP_ADDRESS_2, 
    (uint8_t) MODEL_IP_ADDRESS_3
);

bool treat_analog_registers(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Modbus Transaction callback
    if (event == Modbus::EX_SUCCESS){
        for(Analog_input* ai : analog_input_list){
            ai->set_value(mb_analog_read_buffer[ai->get_id() - MODEL_OFFSET_ANALOG_INPUT]);
        }    
    }                  // If transaction got an error
    else if (event == Modbus::EX_TIMEOUT) {    // If Transaction timeout took place
        mb_model.disconnect(model_address); // Close connection to slave and
        mb_model.dropTransactions();        // Cancel all waiting transactions
    }
    return true;
}

bool treat_digital_registers(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Modbus Transaction callback
    if (event == Modbus::EX_SUCCESS){
        for(Digital_input* di : digital_input_list){
            di->set_value(mb_digital_read_buffer[di->get_id() - MODEL_OFFSET_DIGITAL_INPUT]);
        }
    }                  // If transaction got an error
    else if (event == Modbus::EX_TIMEOUT) {    // If Transaction timeout took place
        mb_model.disconnect(model_address); // Close connection to slave and
        mb_model.dropTransactions();        // Cancel all waiting transactions
    }
    return true;
}


Interface::Interface(){

}

void Interface::start_signal_interfaces(){
    
    //mb_hmi.server();
    mb_model.client();

    /*Iterator<Analog_signal*>* it = signals_list.get_analog_signals_iterator();
    //int i = 0;
    while(it->has_next()){
        //paramos aqui!!!!!!!!!!!!
        Analog_signal* signal = it->next();
        mb_hmi.addHreg(signal->get_id(), signal->get_value(),1);
        //a[i] = signal->get_description();
        //i++;
    }
    delete(it);*/

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

void Interface::receive_data(){
    
    if (!mb_model.isConnected(model_address)) {   // Check if connection to Modbus Slave is established
        mb_model.connect(model_address);           // Try to connect if no connection
    }
    //mb_model.readHreg(model_address, 0, REG_IN_SIMU, 1, cb, 1);


    mb_model.readHreg(
        model_address, 
        MODEL_OFFSET_ANALOG_INPUT, 
        mb_analog_read_buffer, 
        analog_input_list.size() < sizeof(mb_analog_read_buffer) ? analog_input_list.size() : sizeof(mb_analog_read_buffer), 
        treat_analog_registers, 
        1
    );
    //mb_model.readHreg(model_address, 0, teste, 1, treat_registers_after_read_mb, 1);
    //signals_list.get_model_analog_signal_by_id(3)->set_value(mb_read_buffer[0]);

    //int DIGITAL_INPUT_OFFSET = 3;
    
    mb_model.readCoil(
        model_address, 
        MODEL_OFFSET_DIGITAL_INPUT, 
        mb_digital_read_buffer, 
        digital_input_list.size() < sizeof(mb_digital_read_buffer) ? digital_input_list.size() : sizeof(mb_digital_read_buffer), 
        treat_digital_registers, 
        1
    );
    /*Iterator<Analog_signal> it = signals_list.get_analog_signals_iterator();
    while(it.has_next()){
        mb_model.readHreg(model_address, 0, REG_IN_SIMU, 1, cb, 1);
    }*/
    
    mb_model.task(); // Modbus task
}

void Interface::send_data(){
    //mb_model.writeHreg(model_address, OFFSET_REG_OUT_SIMU + CS_AN_MCP_POSATUADOR, &REG_OUT_SIMU[0], 1, cb,1);
}
