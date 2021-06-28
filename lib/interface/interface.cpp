#include "../Interface/Interface.h"

ModbusIP mb_hmi;
ModbusIP mb_model;

uint16_t mb_analog_read_buffer[MODEL_ANALOG_NUMBERS_MAX_SIGNALS];
uint16_t mb_analog_write_buffer[MODEL_ANALOG_NUMBERS_MAX_SIGNALS];
bool mb_digital_read_buffer[MODEL_DIGITAL_NUMBERS_MAX_SIGNALS];
bool mb_digital_write_buffer[MODEL_DIGITAL_NUMBERS_MAX_SIGNALS];

IPAddress model_address(
    (uint8_t) MODEL_IP_ADDRESS_0, 
    (uint8_t) MODEL_IP_ADDRESS_1, 
    (uint8_t) MODEL_IP_ADDRESS_2, 
    (uint8_t) MODEL_IP_ADDRESS_3
);

bool treat_write_registers(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Modbus Transaction callback
    if (event == Modbus::EX_TIMEOUT) {    // If Transaction timeout took place
        mb_model.disconnect(model_address); // Close connection to slave and
        mb_model.dropTransactions();        // Cancel all waiting transactions
    }
    return true;
}

bool treat_analog_read_registers(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Modbus Transaction callback
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

bool treat_digital_read_registers(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Modbus Transaction callback
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
    
    mb_hmi.server();
    setup_hmi_data();

    mb_model.client();
}

void Interface::setup_hmi_data(){
    mb_hmi.addCoil(HMI_OFFSET_BOOL, 0, hmi_bool_signal_list.size());
    mb_hmi.addHreg(HMI_OFFSET_INT, 0, hmi_int_signal_list.size()); 
    mb_hmi.addHreg(HMI_OFFSET_DOUBLE, 0, 2 * hmi_double_signal_list.size());    
}

void Interface::receive_data(){
    mb_model.task(); // Modbus task
    model_receive_data();
    hmi_receive_data();   
}

void Interface::send_data(){
    model_send_data();
    hmi_send_data();
}

void Interface::model_receive_data(){
    if (!mb_model.isConnected(model_address)) {   // Check if connection to Modbus Slave is established
        mb_model.connect(model_address);           // Try to connect if no connection
    }

    mb_model.readHreg(
        model_address, 
        MODEL_OFFSET_ANALOG_INPUT, 
        mb_analog_read_buffer, 
        analog_input_list.size() < sizeof(mb_analog_read_buffer) ? analog_input_list.size() : sizeof(mb_analog_read_buffer), 
        treat_analog_read_registers, 
        1
    );
    
    mb_model.readCoil(
        model_address, 
        MODEL_OFFSET_DIGITAL_INPUT, 
        mb_digital_read_buffer, 
        digital_input_list.size() < sizeof(mb_digital_read_buffer) ? digital_input_list.size() : sizeof(mb_digital_read_buffer), 
        treat_digital_read_registers, 
        1
    );
}

void Interface::model_send_data(){
    for(Digital_output* dout : digital_output_list){
        mb_digital_write_buffer[dout->get_id() - MODEL_OFFSET_DIGITAL_OUTPUT] = dout->get_value();
    }

    mb_model.writeCoil(
        model_address, 
        MODEL_OFFSET_DIGITAL_OUTPUT, 
        mb_digital_write_buffer, 
        digital_output_list.size(),
        treat_write_registers,
        1
    );

    for(Analog_output* aout : analog_output_list){
        mb_analog_write_buffer[aout->get_id() - MODEL_OFFSET_ANALOG_OUTPUT] = aout->get_value();
    }

    mb_model.writeHreg(
        model_address, 
        MODEL_OFFSET_ANALOG_OUTPUT, 
        mb_analog_write_buffer, 
        analog_output_list.size(),
        treat_write_registers,
        1
    );
}

void Interface::hmi_receive_data(){
    for(Hmi_signal<bool>* hs_bool : hmi_bool_signal_list){

    }
}

void Interface::hmi_send_data(){

}

