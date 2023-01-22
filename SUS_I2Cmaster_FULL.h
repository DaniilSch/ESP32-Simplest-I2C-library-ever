/*==========================================================================================================================
 ▄▄▄▄▄▄▄▄▄▄▄  ▄▄        ▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄ 
▐░░░░░░░░░░░▌▐░░▌      ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌
 ▀▀▀▀█░█▀▀▀▀ ▐░▌░▌     ▐░▌ ▀▀▀▀█░█▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌
     ▐░▌     ▐░▌▐░▌    ▐░▌     ▐░▌     ▐░▌       ▐░▌▐░▌       ▐░▌
     ▐░▌     ▐░▌ ▐░▌   ▐░▌     ▐░▌     ▐░█▄▄▄▄▄▄▄█░▌▐░▌       ▐░▌
     ▐░▌     ▐░▌  ▐░▌  ▐░▌     ▐░▌     ▐░░░░░░░░░░░▌▐░▌       ▐░▌
     ▐░▌     ▐░▌   ▐░▌ ▐░▌     ▐░▌     ▐░█▀▀▀▀█░█▀▀ ▐░▌       ▐░▌
     ▐░▌     ▐░▌    ▐░▌▐░▌     ▐░▌     ▐░▌     ▐░▌  ▐░▌       ▐░▌
 ▄▄▄▄█░█▄▄▄▄ ▐░▌     ▐░▐░▌     ▐░▌     ▐░▌      ▐░▌ ▐░█▄▄▄▄▄▄▄█░▌
▐░░░░░░░░░░░▌▐░▌      ▐░░▌     ▐░▌     ▐░▌       ▐░▌▐░░░░░░░░░░░▌
 ▀▀▀▀▀▀▀▀▀▀▀  ▀        ▀▀       ▀       ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀ 
                                                                 
 * ============================================================================
 *
 *    Filename: SUS_I2Cmaster_FULL.h
 *
 *    Brief:    I2C bus library enabling use of ESP32 as a Master device. FULL version.
 *              Part of "Simple Universal Solutions" (SUS) library pack. Spoonfeeding-grade documentation is included.
 * 
 *    Device:   ESP32
 *    Language: C
 *    Version:  1.0 "FULL"
 *    Revision: 2023-01-22 20:58:38
 *
 *    Author(s):   
 *              Daniil Shlee <ds3414755@gmail.com>
 * 
 *    Organization: 
 *              RMIT University/Orlar inc.
 *
 *    Description: 
 *              Yet another I2C bus library created with MAXIMUM readability, clarity, ease of use, integration and modification in mind.
 *              The code, documentation layout are optimized for ease or reading and comprehension, even by those who are completely new to I2C.
 *              All functions are COMPLETELY STANDALONE and do not depend on any 3rd party #defines, typedefs or abstractions - copy-paste with impunity!
 *              All it takes to add this library to your project is to #include this one .h file.
 *              
 *              If you feel like you can make the code run faster, feel free to fork - the lib is specifically designed for this ;) 
 *              Commented LOOOOOOOOONG version - full Doxygen documentation included.
 * 
 *              Library contains functions for:
 *                  1. Initializing ESP32 as an I2C master device on I2C bus
 *                  2. Scanning for any I2C slave devices connected to ESP32 and printing their I2C addresses
 *                  3. Pinging an I2C slave device with a particular address
 *                  4. Reading a byte of data from I2C slave device
 *                  5. Reading a byte of data from a register of I2C slave device
 *                  6. Reading a sequence/stream of bytes from I2C slave device
 *                  7. Writing a byte of data to I2C slave device
 *                  8. Writing a byte of data to a register of an I2C slave device
 *                  9. Writing a sequence/stream/array of data bytes to I2C slave device
 *                  10. Resetting a stuck I2C bus
 *              
 *              Required bare-minimum #includes:
 *                  #include <stdio.h>
 *                  #include "esp_log.h"
 *                  #include "driver/i2c.h"
 *                  #include "freertos/task.h"
 * 
 *              Example of general workflow with this library's functions:
 *                  0. #include the bare minimum official libraries. You will need those for ESP32 to function anyway.
 *                  1. >>CHECK YOUR I2C SLAVE DEVICE DATASHEET ON HOW TO COMMUNICATE WITH IT USING I2C<<. At least pretend to read it... 
 *                  2. Decide on what ESP32 pins are to be used with I2C. Decide on what I2C port of ESP32 you are going to use (0 or 1). Connect all the slave devices and pullup resistors. 
 *                  3. Run the SUS_I2C_Master_Init function in your code.
 *                  4. If you are unsure what is your slave device's I2C address, run SUS_I2C_Scan_For_Devices function. It will return all the addresses of all the found devices on the bus.
 *                  5. If you are sure of your slave device's address, run the SUS_I2C_Ping_Address function to confirm that your device is responding.
 *                  6. >>CHECK YOUR I2C SLAVE DEVICE DATASHEET ON HOW TO COMMUNICATE WITH IT USING I2C<<. Try to comprehend this time ;)
 *                  7. Run any of the read and/or write functions
 * 
*/
/*==========================================================================================================================
 ▄▄▄▄▄▄▄▄▄▄▄  ▄▄        ▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄ 
▐░░░░░░░░░░░▌▐░░▌      ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌
 ▀▀▀▀█░█▀▀▀▀ ▐░▌░▌     ▐░▌ ▀▀▀▀█░█▀▀▀▀  ▀▀▀▀█░█▀▀▀▀ 
     ▐░▌     ▐░▌▐░▌    ▐░▌     ▐░▌          ▐░▌     
     ▐░▌     ▐░▌ ▐░▌   ▐░▌     ▐░▌          ▐░▌     
     ▐░▌     ▐░▌  ▐░▌  ▐░▌     ▐░▌          ▐░▌           DONT FORGET THE HEADER FILES!
     ▐░▌     ▐░▌   ▐░▌ ▐░▌     ▐░▌          ▐░▌                 #include <stdio.h>
     ▐░▌     ▐░▌    ▐░▌▐░▌     ▐░▌          ▐░▌                 #include "esp_log.h"
 ▄▄▄▄█░█▄▄▄▄ ▐░▌     ▐░▐░▌ ▄▄▄▄█░█▄▄▄▄      ▐░▌                 #include "driver/i2c.h"
▐░░░░░░░░░░░▌▐░▌      ▐░░▌▐░░░░░░░░░░░▌     ▐░▌                 #include "freertos/task.h"
 ▀▀▀▀▀▀▀▀▀▀▀  ▀        ▀▀  ▀▀▀▀▀▀▀▀▀▀▀       ▀                                                     

*/

/**SUS_I2C_Master_Init: Initializes I2C peripheral of ESP32 as a master. Run BEFORE any other I2C-related functions.
 * 1. Parameter "I2C_master_port" is just an integer number 1 or 0, corresponding to two ports of ESP32 (there are two of these with indexes of 0 and 1).
 * 2. Parameter "SCL_pin_number" is an integer number (0-40) of the ESP32 Pin that you want to use for the CLOCK (SCL) line of I2C. ESP32's I2C peripheral is not hardwired to any particular pins - you can assign any GPIO WHICH IS NOT MARKED AS "INPUT ONLY" for this in software.
 * 3. Parameter "SDA_pin_number" is an integer number (0-40) of the ESP32 Pin that you want to use for the DATA (SDA) line of I2C. ESP32's I2C peripheral is not hardwired to any particular pins - you can assign any GPIO WHICH IS NOT MARKED AS "INPUT ONLY" for this in software.
 * IMPORTANT: "Pin numbers" in this scope refer to the pin numbers of the ESP32 CHIP ITSELF, and NOT of whatever devKit board you may have. Account for that when consulting pinouts off the internet. Your devKit's pinout should have this information.
 * 4. Parameter "speed" is an integer number (0-400000) that represents the frequency (or "speed", duh) of I2C communication bus in Hz (or "clocks per second"). Common values are: 100000 (100kHz) and 400000(400kHz).
 * EXAMPLE USE: SUS_I2C_Master_Init(0,18,19,100000); Initialize ESP32's I2C at I2C port 0, pin 18 as clock, pin 19 as data pin, 100kHz speed.
*/
esp_err_t SUS_I2C_Master_Init(uint8_t I2CportNumber, uint8_t SCL_pin_number, uint8_t SDA_pin_number, int speed)
{
    /*=============================STEP 1. Set up configuration struct and error code variable=======================================*/
    char *I2C_STATUS_TAG = "I2C STATUS";   //Tag for debug messages. No effect on I2C setup and/or operation. Purely for printing text.
    esp_err_t executionOutcome;                         //Variable used in error handling that will hold the error/success outcome codes. If it is 0 = all good, -1 = something went wrong.

    //Below is a C struct containing all the configuration settings used to set up I2C peripheral of ESP32.
    //It is of type "i2c_config_t" as defined in the I2C driver ("i2c.h") by Espressif themselves. 
    //Apparently it is done for clarity even though at a glance it is slightly confusing. Just roll with it, at the end of the day it is just a struct.
    i2c_config_t conf = {               
        .mode = I2C_MODE_MASTER,            //What mode you want this device to act on the I2C bus - master or slave
        .scl_io_num = SCL_pin_number,       //Pin number for CLOCK line
        .sda_io_num = SDA_pin_number,       //Pin number for DATA line
        .master.clk_speed = speed,          //Desired I2C bus Speed in Hz
        .sda_pullup_en = GPIO_PULLUP_ENABLE,//Whether to enable the internal Pullup Resistor on DATA line, as it will not function without it. Note, that you may need external pullup resistors even if you enable the internal pullups.
        .scl_pullup_en = GPIO_PULLUP_ENABLE,//Whether to enable the internal Pullup Resistor on CLOCK line. Note, that you may need external pullup resistors even if you enable the internal pullups.
        // .clk_flags = 0,                  //Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here.
    };
    
    /*============================STEP 2. Apply I2C configuration struct ===========================================================*/
    //Takes the I2C configuration struct from STEP1 and writes the values within to the I2C hardware registers. 
    executionOutcome = i2c_param_config(I2CportNumber, &conf);    //Execute "apply config" function and write the result (success/error) to the variable.
        if (executionOutcome != ESP_OK) {
            ESP_LOGE(I2C_STATUS_TAG,"Error occured while setting up I2C parameters. Check the i2c_config_t configuration struct. Code %d",executionOutcome);
            return executionOutcome;                                //On error, report the issue and exit the function immediately
        }
        else if (executionOutcome == ESP_OK) {
            ESP_LOGI(I2C_STATUS_TAG,"I2C parameters set successfully. Code %d",executionOutcome);
               //On success, continue to the next step: "installing" the I2C driver
        };
    /*=============================STEP 3. "Install" I2C (i.e. start I2C peripheral with the applied config)=========================*/
    //Execute install function and write the result (success/error) to the variable.
    //No ideas why Espressif chose the word "install" (associated with high-level OS and software) when all it does is write a bunch of values to the hardware registers and starts the I2C peripheral. 
    //Might've sounded fancy.

    executionOutcome = i2c_driver_install(I2CportNumber, conf.mode, 0, 0, 0); //Executes install function and writes the result (success/error) to the variable.

        //Handle the error case    
        if (executionOutcome != ESP_OK) {
            ESP_LOGI(I2C_STATUS_TAG,"Error occured while installing I2C driver. Check the port number and i2c_config_t configuration struct. Code %d",executionOutcome);
            return executionOutcome; //On error, report the issue and exit the function immediately
        }
        //Handle the success case
        else if (executionOutcome == ESP_OK) {
            ESP_LOGI(I2C_STATUS_TAG,"I2C driver installed successfully. Code %d",executionOutcome);
            return executionOutcome; //On success, exit the function immediately.
        };

        //Handle the exception case (neither success nor failure).
        ESP_LOGI(I2C_STATUS_TAG,"I2C driver installation finished inconclusively. Please check the code.");
        return executionOutcome;
    }


/*==========================================================================================================================
 ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄        ▄ 
▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░▌      ▐░▌
▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░▌░▌     ▐░▌
▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌▐░▌    ▐░▌
▐░█▄▄▄▄▄▄▄▄▄ ▐░▌          ▐░█▄▄▄▄▄▄▄█░▌▐░▌ ▐░▌   ▐░▌
▐░░░░░░░░░░░▌▐░▌          ▐░░░░░░░░░░░▌▐░▌  ▐░▌  ▐░▌
 ▀▀▀▀▀▀▀▀▀█░▌▐░▌          ▐░█▀▀▀▀▀▀▀█░▌▐░▌   ▐░▌ ▐░▌
          ▐░▌▐░▌          ▐░▌       ▐░▌▐░▌    ▐░▌▐░▌
 ▄▄▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░▌       ▐░▌▐░▌     ▐░▐░▌
▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌▐░▌      ▐░░▌
 ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀         ▀  ▀        ▀▀                                                                                           
*/

/**Scans the I2C bus for any devices of any address and lists all found addresses. Useful for determining the addresses of devices you may not know.
 * Parameter "I2CportNumber" is just an integer number 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * EXAMPLE USE: SUS_I2C_ScanForDevices(0); Lists all devices (and their addresses) connected to the I2C port 0.
*/
void SUS_I2C_ScanForDevices(int I2CportNumber)
{
    esp_err_t outcome;                         //variable used in error handling that will hold the error/success codes. If it is 0 = all good, -1 = something went wrong.
    char *I2C_SCAN_TAG = "I2C SCAN";       //Tag for debug messages
    uint8_t write_buf[2] = {0x00,0};                   //Initialize array of 2 values to be written to the I2C device. First value is a register address. Second value will be written to that register.
    
    ESP_LOGW(I2C_SCAN_TAG,"Starting scan: pinging all I2C addresses from 0 to 127.");
    for (size_t i = 0; i < 127; i++)
    {
        //printf("Pinging the device at the address %d...\n\r",i);
        outcome = i2c_master_write_to_device(I2CportNumber,i,write_buf,sizeof(write_buf),10/portTICK_PERIOD_MS);
        if (outcome==ESP_OK) 
            {
                ESP_LOGI(I2C_SCAN_TAG,"Device found at address %d (%#04x).",i,i);
            }
        else if (outcome!=ESP_OK) 
            {
                printf("No device found at address %d (%#04x).\n\r",i,i);
            };
    } //End of for loop  

}

/**Checks whether there is a device at a given I2C address by performing an I2C write of 0 (zero) to the register 0x0 of the device at that address.
 * Parameter "I2CportNumber" is just an integer number 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * Parameter "I2CdeviceAddressHex" is an integer number from 0 to 127 (as per I2C limit of 127 addresses). Preferrably should be written in a hex number format (0x) for clarity, but can be decimal too.
 * EXAMPLE USE: SUS_I2C_PingAddress(0,0x4A); Pings device (MAX44009) at I2C port 0 and address 0x4A.
*/
void SUS_I2C_PingAddress(int I2CportNumber, uint8_t I2CdeviceAddress)
{
    esp_err_t outcome;                         //variable used in error handling that will hold the error/success codes. If it is 0 = all good, -1 = something went wrong.
    char *I2C_PING_TAG = "I2C PING";       //Tag for debug messages
    uint8_t write_buf[2] = {0x00, 0};                   //Initialize array of 2 values to be written to the I2C device. First value is a register address. Second value will be written to that register.
    
    printf("Pinging the device at the address %d...\n\r",I2CdeviceAddress);
    outcome = i2c_master_write_to_device(I2CportNumber,I2CdeviceAddress,write_buf,sizeof(write_buf),10/portTICK_PERIOD_MS);
        if (outcome==ESP_OK) 
            {
                //printf("write to device %d completed successfully. Status %d.\n\r",I2CdeviceAddressHex, outcome);
                ESP_LOGI(I2C_PING_TAG,"Write to address %d completed successfully, there is likely a device present. Code %d.\n\r",I2CdeviceAddress, outcome);
            }
        else if (outcome!=ESP_OK) 
            {
                //printf("write failed. Error code %d.\n\r", outcome);
                ESP_LOGI(I2C_PING_TAG,"Failed to write to address %#04x. Code %d(%#04x). Device is either not connected properly or not responding.\n\r Check the I2C address value, physical contacts and/or pullup resistor values.\n\r Also, make ABSOLUTELY sure that you've run the I2C initialization routine first! \n\r",I2CdeviceAddress, outcome,outcome);
            };
    printf("Pinging finished.\n\r");
}


/*
 ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄  
▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░▌ 
▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌
▐░▌       ▐░▌▐░▌          ▐░▌       ▐░▌▐░▌       ▐░▌
▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄█░▌▐░▌       ▐░▌
▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌
▐░█▀▀▀▀█░█▀▀ ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░▌       ▐░▌
▐░▌     ▐░▌  ▐░▌          ▐░▌       ▐░▌▐░▌       ▐░▌
▐░▌      ▐░▌ ▐░█▄▄▄▄▄▄▄▄▄ ▐░▌       ▐░▌▐░█▄▄▄▄▄▄▄█░▌
▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌▐░░░░░░░░░░▌ 
 ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀         ▀  ▀▀▀▀▀▀▀▀▀▀  
*/

/**SUS_I2C_ReadRegister: Reads the slave's register by WRITING that register's 8-bit address to the I2C bus followed by a REPEATED START condition and then a READ request. Uses ESP-IDF's "I2C link queue" API method. Simplifies register operation of I2C slave devices that support this method.
 * PARAMETER "I2CportNumber" is just an integer number (uint8_t) 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * PARAMETER "I2CdeviceAddress" is an integer number (uint8_t)  from 0 to 127 (as per I2C limit of 127 addresses). Preferrably should be written in a hex number format (0x) for clarity, but can be decimal too.
 * PARAMETER "registerAddress" is an integer number (uint8_t) containing 8-bit address of the I2C slave device's register (look it up in the datasheet ;).
 * RETURNS uint8_t value read from the slave device's register.
 * EXAMPLE USE: uint8_t data = SUS_I2C_ReadRegister(0,0x4A,0x01); //Reads data value from device 0x04's register 0x01.
*/
uint8_t SUS_I2C_ReadRegister(uint8_t I2CportNumber, uint8_t I2CdeviceAddress, uint8_t registerAddress)
{
    char *I2C_READ_TAG = "I2C READ"; //Tag (essentially a text label) for debug messages.
    uint8_t read_value =0xf1;       // This variable will store the value read from the slave device's register.
    //uint8_t ACK_VAL = 0;            // ACKnowledge 
    uint8_t NACK_VAL = 1;           // NOT ACKnowledge 
    uint8_t WRITE_MODE = 0;         // Write mode - LOW bus
    uint8_t READ_MODE = 1;          // Read mode - HIGH bus
    esp_err_t outcome;              // Used to report error/success. If it is 0 = all good, -1 = something went wrong, 263 (0x107) = timeout.

    i2c_cmd_handle_t cmdSeq = i2c_cmd_link_create();			            // Creates the I2C command sequence list. This list will contain your I2C sequence. DOES NOT PERFORM ANY COMMANDS ON ITS OWN!
        i2c_master_start(cmdSeq); 												    // START condition.
        i2c_master_write_byte(cmdSeq,(I2CdeviceAddress<<1)|WRITE_MODE,true); 	    // Select I2C address and WRITE mode, check ACK from slave.
        i2c_master_write_byte(cmdSeq,registerAddress,true); 						// Select the register address of the slave by writing register address value to the slave. Check ACK from slave.
        i2c_master_start(cmdSeq); 	                                                // REPEATED START condition.
        i2c_master_write_byte(cmdSeq,(I2CdeviceAddress<<1)|READ_MODE,true); 		// Select I2C address and READ mode, check ACK from slave.
        i2c_master_read_byte(cmdSeq,&read_value,NACK_VAL); 						    // Read the register and write its value into the variable. Since this is the final byte we request from the slave, send Master NACK as per I2C protocol standard.
        i2c_master_stop(cmdSeq);                                                    // STOP condition. IMPORTANT! Physically releases the I2C line so it is no longer pulled down. If you dont add this command, your I2C SCL bus may get locked up at LOW level!
                                                       
    outcome = i2c_master_cmd_begin(I2CportNumber, cmdSeq, 10/portTICK_PERIOD_MS);   // THIS LINE PERFORMS ALL THE ABOVE I2C COMMANDS ON THE PHYSICAL BUS. Yes, this command makes the GPIOs go beep-boop, high-low, 3v3-0v... you get the idea. This is the "execute I2C commands" line.
        if (outcome==ESP_OK) 
            {
                ESP_LOGI(I2C_READ_TAG,"[I2C PORT %d], [Device %#04x], [Register %#04x] : read value %#04x. Code %#04x.",I2CportNumber,I2CdeviceAddress,registerAddress,read_value,outcome);
            }
        else if (outcome!=ESP_OK) 
            {
                //Check the I2C address value, physical contacts, pullup resistor values, I2C command sequence and/or bus signal rise rate (depends on overall capacitance).\n\r Also, make ABSOLUTELY sure that you've run the I2C initialization routine first! 
                ESP_LOGE(I2C_READ_TAG,"[I2C PORT %d], [Device %#04x], [Register %#04x] : read FAILED. Code %#04x.",I2CportNumber,I2CdeviceAddress,registerAddress,outcome);
                return 0;
            };

    i2c_cmd_link_delete(cmdSeq);            //Deletes the I2C command sequence to free the RAM.
 
    return read_value;                      //Return value received from the slave's register.
}

/**SUS_I2C_ReadRegister_EZ: Uses ESP-IDF's "Write-Read" wrapper function to read the register the "EASY WAY"(tm). However, underlying principle is the same as regular SUS_I2C_ReadRegister. Simplifies register operation of I2C slave devices that support this method.
 * Parameter "I2CportNumber" is just an integer number 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * Parameter "I2CdeviceAddressHex" is an integer number from 0 to 127 (as per I2C limit of 127 addresses). Preferrably should be written in a hex number format (0x) for clarity, but can be decimal too.
 * Parameter "registerAddress" is the 8-bit address of the I2C slave device's register (look it up in the datasheet ;).
 * EXAMPLE USE: uint8_t data = SUS_I2C_ReadRegister_EZ(0,0x4A,0x01); //Reads data value from device 0x04's register 0x01.
*/
uint8_t SUS_I2C_ReadRegister_EZ(int I2CportNumber,int I2CdeviceAddress, uint8_t registerAddress)
{
    char *I2C_READ_TAG = "I2C READ";    //Tag (essentially a text label) for debug messages.
    esp_err_t outcome;                  // Used to report error/success. If it is 0 = all good, -1 = something went wrong, 263 (0x107) = timeout.

    uint8_t read_value = 0xf1;          // This variable will store the value read from the slave device's register.    

    //ESP_LOGW(I2C_READ_TAG,"Attempting to read the value from register %#04x of the device %#04x",registerAddress,I2CdeviceAddressHex);
    outcome = i2c_master_write_read_device(0,I2CdeviceAddress,&registerAddress,1,&read_value,1,5/portTICK_PERIOD_MS);
        if (outcome==ESP_OK) 
            {
                ESP_LOGI(I2C_READ_TAG,"[I2C PORT %d], [Device %#04x], [Register %#04x] : read value %#04x. Code %#04x.",I2CportNumber,I2CdeviceAddress,registerAddress,read_value,outcome);
            }
        else if (outcome!=ESP_OK) 
            {
                //Check the I2C address value, physical contacts, pullup resistor values, I2C command sequence and/or bus signal rise rate (depends on overall capacitance).\n\r Also, make ABSOLUTELY sure that you've run the I2C initialization routine first! 
                ESP_LOGE(I2C_READ_TAG,"[I2C PORT %d], [Device %#04x], [Register %#04x] : read FAILED. Code %#04x.",I2CportNumber,I2CdeviceAddress,registerAddress,outcome);
                return 0;
            };
    return read_value;
}

/**SUS_I2C_ReadByte: Reads the byte of data from a given I2C slave device followed by a full STOP condition. Uses ESP-IDF's "I2C link queue" API method.
 * NOTE: When interfacing with I2C sensors, this function generally is not very useful if you are trying to read from the sensor's register(s). 
 * Most sensors require a WRITE-read sequence of I2C operations WITHOUT a STOP inbetween to first SELECT the register of the sensor, and only then READ - not just a simple READ. Consult your sensor device's datasheet.
 * PARAMETER "I2CportNumber" is just an integer number (uint8_t) 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * PARAMETER "I2CdeviceAddress" is an integer number (uint8_t)  from 0 to 127 (as per I2C limit of 127 addresses). Preferrably should be written in a hex number format (0x) for clarity, but can be decimal too.
 * RETURNS uint8_t value read from the slave device's register.
 * EXAMPLE USE: uint8_t data = SUS_I2C_ReadByte(0,0x4A);
*/
uint8_t SUS_I2C_ReadByteFromSlave(uint8_t I2CportNumber, uint8_t I2CdeviceAddress)
{
    char *I2C_READ_TAG = "I2C READ"; //Tag (essentially a text label) for debug messages.
    uint8_t read_value =0xf1;        // This variable will store the value read from the slave device's register. 0xf1 is just a random value to initiate the variable with.
    //uint8_t ACK_VAL = 0;           // ACKnowledge 
    uint8_t NACK_VAL = 1;            // NOT ACKnowledge 
    //uint8_t WRITE_MODE = 0;        // Write mode - LOW bus
    uint8_t READ_MODE = 1;           // Read mode - HIGH bus
    esp_err_t outcome;               // Used to report error/success. If it is 0 = all good, -1 = something went wrong, 263 (0x107) = timeout.

    i2c_cmd_handle_t cmdSeq = i2c_cmd_link_create();			            // Creates the I2C command sequence list. This list will contain your I2C sequence. DOES NOT PERFORM ANY COMMANDS ON ITS OWN!
        i2c_master_start(cmdSeq); 	                                                // START condition.
        i2c_master_write_byte(cmdSeq,(I2CdeviceAddress<<1)|READ_MODE,true); 		// Select I2C device and put it into the READ mode. Check ACK from slave.
        i2c_master_read_byte(cmdSeq,&read_value,NACK_VAL); 						    // Read the register and write its value into the variable. Since this is the final byte we request from the slave, send Master NACK as per I2C protocol standard.
        i2c_master_stop(cmdSeq);                                                    // STOP condition. IMPORTANT! Physically releases the I2C line so it is no longer pulled down. If you dont add this command, your I2C SCL bus may get locked up at LOW level!
                                                       
    outcome = i2c_master_cmd_begin(I2CportNumber, cmdSeq, 10/portTICK_PERIOD_MS);   // THIS LINE PERFORMS ALL THE ABOVE I2C COMMANDS ON THE PHYSICAL BUS.
        if (outcome==ESP_OK) 
            {
                ESP_LOGI(I2C_READ_TAG,"[I2C PORT %d], [Device %#04x] : read value %#04x. Code %#04x.",I2CportNumber,I2CdeviceAddress,read_value,outcome);
            }
        else if (outcome!=ESP_OK) 
            {
                //Check the I2C address value, physical contacts, pullup resistor values, I2C command sequence and/or bus signal rise rate (depends on overall capacitance).\n\r Also, make ABSOLUTELY sure that you've run the I2C initialization routine first! 
                ESP_LOGE(I2C_READ_TAG,"[I2C PORT %d], [Device %#04x] : read FAILED. Code %#04x.",I2CportNumber,I2CdeviceAddress,outcome);
                return 0;
            };

    i2c_cmd_link_delete(cmdSeq);            //Deletes the I2C command sequence to free the RAM.
 
    return read_value;                      //Return value received from the slave's register.
}

/**SUS_I2C_ReadByte: Reads the byte of data from a given I2C slave device followed by a full STOP condition. Uses ESP-IDF's "Read" wrapper function to do so the "EASY WAY"(tm). However, underlying principle is the same as regular SUS_I2C_ReadByte. 
 * NOTE: When interfacing with I2C sensors, this function generally is not very useful if you are trying to read from the sensor's register(s). 
 * Most sensors require a WRITE-read sequence of I2C operations WITHOUT a STOP inbetween to first SELECT the register of the sensor, and only then READ - not just a simple READ. Consult your sensor device's datasheet.
 * PARAMETER "I2CportNumber" is just an integer number (uint8_t) 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * PARAMETER "I2CdeviceAddress" is an integer number (uint8_t)  from 0 to 127 (as per I2C limit of 127 addresses). Preferrably should be written in a hex number format (0x) for clarity, but can be decimal too.
 * RETURNS uint8_t value read from the slave device's register.
 * EXAMPLE USE: uint8_t data = SUS_I2C_ReadByte(0,0x4A);
*/
void SUS_I2C_ReadByteFromSlave_EZ(int I2CportNumber,int I2CdeviceAddress)
{
    char *I2C_READ_TAG = "I2C READ";    //Tag (essentially a text label) for debug messages.
    esp_err_t outcome;                  // Used to report error/success. If it is 0 = all good, -1 = something went wrong, 263 (0x107) = timeout.

    uint8_t read_value = 0xf1;          // This variable will store the value read from the slave device's register. 0xf1 is just a random value to initiate the variable with.
    
    outcome = i2c_master_read_from_device(I2CportNumber, I2CdeviceAddress, &read_value, 1, 10/portTICK_PERIOD_MS);

        if (outcome==ESP_OK) 
        {
            ESP_LOGI(I2C_READ_TAG,"Read from the device  %#04x completed successfully, Code %d(%#04x).\n\r", I2CdeviceAddress, outcome,outcome);
        }
    else if (outcome!=ESP_OK) 
        {

            ESP_LOGE(I2C_READ_TAG,"Failed to read from device  %#04x. Code %d(%#04x).",I2CdeviceAddress, outcome,outcome);
        };

}

/*
 ▄         ▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄ 
▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌
▐░▌       ▐░▌▐░█▀▀▀▀▀▀▀█░▌ ▀▀▀▀█░█▀▀▀▀  ▀▀▀▀█░█▀▀▀▀ ▐░█▀▀▀▀▀▀▀▀▀ 
▐░▌       ▐░▌▐░▌       ▐░▌     ▐░▌          ▐░▌     ▐░▌          
▐░▌   ▄   ▐░▌▐░█▄▄▄▄▄▄▄█░▌     ▐░▌          ▐░▌     ▐░█▄▄▄▄▄▄▄▄▄ 
▐░▌  ▐░▌  ▐░▌▐░░░░░░░░░░░▌     ▐░▌          ▐░▌     ▐░░░░░░░░░░░▌
▐░▌ ▐░▌░▌ ▐░▌▐░█▀▀▀▀█░█▀▀      ▐░▌          ▐░▌     ▐░█▀▀▀▀▀▀▀▀▀ 
▐░▌▐░▌ ▐░▌▐░▌▐░▌     ▐░▌       ▐░▌          ▐░▌     ▐░▌          
▐░▌░▌   ▐░▐░▌▐░▌      ▐░▌  ▄▄▄▄█░█▄▄▄▄      ▐░▌     ▐░█▄▄▄▄▄▄▄▄▄ 
▐░░▌     ▐░░▌▐░▌       ▐░▌▐░░░░░░░░░░░▌     ▐░▌     ▐░░░░░░░░░░░▌
 ▀▀       ▀▀  ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀       ▀       ▀▀▀▀▀▀▀▀▀▀▀ 
*/

/**SUS_I2C_WriteToRegister: Writes to the slave's register by WRITING two 8-bit values to the I2C bus without STOP condition inbetween. Simplifies register operation of I2C devices that support this method.
 * NOTE: This is the function you should use to write to I2C sensor's registers.
 * Parameter "I2CportNumber" is just an integer number 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * Parameter "I2CdeviceAddressHex" is an integer number from 0 to 127 (as per I2C limit of 127 addresses). Preferrably should be written in a hex number format (0x) for clarity, but can be decimal too.
 * Parameter "registerAddress" is the 8-bit address of the I2C slave device's register (look it up in the datasheet ;).
 * Parameter "valueToWrite" is the 8-bit integer you want to write to the device. Can be written in decimal, hex or binary.
 * PARAMETER "recheckWrittenDataYN" is a boolean (true/false) that determines whether an additional check will be performed to verify the written value.
 * EXAMPLE USE: SUS_I2C_WriteToSlave_Register(0,0x4A,0x01,1); Writes the value 1 (0x01) to the register 0x01 of the device at I2C address 0x04A.
*/
void SUS_I2C_WriteToRegister(uint8_t I2CportNumber, uint8_t I2CdeviceAddress, uint8_t registerAddress, uint8_t valueToWrite)
{
    const char *I2C_WRITE_TAG = "I2C WRITE"; //Tag (essentially a text label) for debug messages.
    esp_err_t outcome;              // Used to report error/success. If it is 0 = all good, -1 = something went wrong, 263 (0x107) = timeout.

    uint8_t WRITE_MODE = 0;         // Write mode - LOW bus


    i2c_cmd_handle_t cmdSeq = i2c_cmd_link_create();
        i2c_master_start(cmdSeq);                                          //START condition. "Hey everyone on I2C bus! I'M GOING TO TALK TO ONE OF YOU!!1"
        i2c_master_write_byte(cmdSeq,(I2CdeviceAddress<<1)|WRITE_MODE,true);  //Select the slave with the given address and put it in the "WRITE TO" mode.
        i2c_master_write_byte(cmdSeq,registerAddress,true);                   //Select the register address of the device.
        i2c_master_write_byte(cmdSeq,valueToWrite,true);                      //Write the value 1 to the register on the device
        i2c_master_stop(cmdSeq);                                           //STOP condition. "I'm done talking. Dismissed!"

    outcome = i2c_master_cmd_begin(I2CportNumber, cmdSeq, 10/portTICK_PERIOD_MS);      //EXECUTE THE I2C COMMANDS!
    if (outcome==ESP_OK)
        {
            ESP_LOGI(I2C_WRITE_TAG,"[I2C PORT %d], [Device %#04x], [Register %#04x] : %#04x write OK. Code %#04x.",I2CportNumber,I2CdeviceAddress,registerAddress,valueToWrite,outcome);
        }
    else if (outcome!=ESP_OK) 
        {
            ESP_LOGE(I2C_WRITE_TAG,"[I2C PORT %d], [Device %#04x], [Register %#04x] : %#04x write FAILED. Code %#04x.",I2CportNumber,I2CdeviceAddress,registerAddress,valueToWrite,outcome);
        };

    i2c_cmd_link_delete(cmdSeq);
}

/**SUS_I2C_WriteToRegister_EX: Writes to the slave's register by WRITING two 8-bit values to the I2C bus without STOP condition inbetween. Performs an extra data integrity check by reading the written value from slave's memory address and comparing it to the original.
 * Parameter "I2CportNumber" is just an integer number 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * Parameter "I2CdeviceAddressHex" is an integer number from 0 to 127 (as per I2C limit of 127 addresses). Preferrably should be written in a hex number format (0x) for clarity, but can be decimal too.
 * Parameter "registerAddress" is the 8-bit address of the I2C slave device's register (look it up in the datasheet ;).
 * Parameter "valueToWrite" is the 8-bit integer you want to write to the device. Can be written in decimal, hex or binary.
 * EXAMPLE USE: SUS_I2C_WriteToSlave_Register(0,0x4A,0x01,1); Writes the value 1 (0x01) to the register 0x01 of the device at I2C address 0x04A.
*/
void SUS_I2C_WriteToRegister_EX(uint8_t I2CportNumber, uint8_t I2CdeviceAddress, uint8_t registerAddress, uint8_t valueToWrite)
{
    const char *I2C_WRITE_TAG = "I2C WRITE"; //Tag (essentially a text label) for debug messages.
    const char *I2C_WRITE_CHECK = "I2C WRITE CHECK"; //Tag (essentially a text label) for debug messages.
    uint8_t read_value =0xf1;       // This variable will store the value read from the slave device's register. 0xf1 is just a random default value.
    //uint8_t ACK_VAL = 0;            // ACKnowledge 
    uint8_t NACK_VAL = 1;           // NOT ACKnowledge 
    uint8_t WRITE_MODE = 0;         // Write mode - LOW bus
    uint8_t READ_MODE = 1;          // Read mode - HIGH bus
    esp_err_t outcome;              // Used to report error/success. If it is 0 = all good, -1 = something went wrong, 263 (0x107) = timeout.

    i2c_cmd_handle_t cmdSeq = i2c_cmd_link_create();
        i2c_master_start(cmdSeq);                                              //START condition. "Hey everyone on I2C bus! I'M GOING TO TALK TO ONE OF YOU!!1"
        i2c_master_write_byte(cmdSeq,(I2CdeviceAddress<<1)|WRITE_MODE,true);       //Select the slave with the given address and put it in the "WRITE TO" mode.
        i2c_master_write_byte(cmdSeq,registerAddress,true);                        //Select the register address of the device.
        i2c_master_write_byte(cmdSeq,valueToWrite,true);                           //Write the value 1 to the register on the device
        
    //Write checking code - reads the newly written value to confirm it has been correctly received.
    //Confirms the written data by reading the contents of the register we just wrote to.
        i2c_master_start(cmdSeq);                                              //REPEATED START condition.
        i2c_master_write_byte(cmdSeq,(I2CdeviceAddress<<1)|WRITE_MODE,true);       //Broadcast the slave's I2C address on the bus, write mode.
        i2c_master_write_byte(cmdSeq,registerAddress,true);                        //Select the register of the device.
        i2c_master_start(cmdSeq);//REPEATED START condition.
        i2c_master_write_byte(cmdSeq,(I2CdeviceAddress<<1)|READ_MODE,true);        //Select the device address and say "Imma read from you".
        i2c_master_read_byte(cmdSeq,&read_value,NACK_VAL);                         //Read the value from the register into the variable. Since this is the final byte we request from the slave, send Master NACK as per I2C protocol standard.

        i2c_master_stop(cmdSeq);                                               //STOP condition. "I'm done talking. Dismissed!"

    outcome = i2c_master_cmd_begin(I2CportNumber, cmdSeq, 10/portTICK_PERIOD_MS);          //EXECUTE THE I2C COMMANDS!
    if (outcome==ESP_OK) //Outcome is OK ;)
        {
            ESP_LOGI(I2C_WRITE_TAG,"[I2C PORT %d], [Device %#04x], [Register %#04x] : %#04x write OK. Code %#04x.",I2CportNumber,I2CdeviceAddress,registerAddress,valueToWrite,outcome);
            if (read_value == valueToWrite)
            {
                ESP_LOGW(I2C_WRITE_CHECK," Value %#04x of the register %#04x matches the input value %#04x. Write success confirmed.",read_value, registerAddress,valueToWrite);

            }
            else if (read_value != valueToWrite)
            {
                ESP_LOGE(I2C_WRITE_CHECK," Data mismatch: register %#04x contains %#04x, input value was: %#04x. Something went wrong during the data transfer.",registerAddress,read_value, valueToWrite);
            }
        }
    else if (outcome!=ESP_OK) //Outcome is NOT OK :(
        {
            //Check the I2C address value, physical contacts, pullup resistor values, I2C command sequence and/or bus signal rise rate (depends on overall capacitance).\n\r Also, make ABSOLUTELY sure that you've run the I2C initialization routine first! 
            ESP_LOGE(I2C_WRITE_TAG,"[I2C PORT %d], [Device %#04x], [Register %#04x] : %#04x write FAILED. Code %#04x.",I2CportNumber,I2CdeviceAddress,registerAddress,valueToWrite,outcome);
        };

    i2c_cmd_link_delete(cmdSeq);

}


/**SUS_I2C_WriteToRegister_EZ: Writes to the slave's register by WRITING two 8-bit values to the I2C bus without STOP condition inbetween.
 * Uses "write_to_device" wrapper function to write to the slave's register the "EASY WAY"(tm). However, underlying principle is the same as regular SUS_I2C_WriteToRegister.
 * Parameter "I2CportNumber" is just an integer number 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * Parameter "I2CdeviceAddressHex" is an integer number from 0 to 127 (as per I2C limit of 127 addresses). Preferrably should be written in a hex number format (0x) for clarity, but can be decimal too.
 * Parameter "registerAddress" is the 8-bit address of the I2C slave device's register (look it up in the datasheet ;).
 * Parameter "valueToWrite" is the 8-bit integer you want to write to the device. Can be written in decimal, hex or binary.
 * EXAMPLE USE: SUS_I2C_WriteToRegister_EZ(0,0x4A,0x01,1); Writes the value 1 (0x01) to the register 0x01 of the device at I2C address 0x04A.
*/
void SUS_I2C_WriteToRegister_EZ(int I2CportNumber,int I2CdeviceAddress, uint8_t registerAddress, uint8_t valueToWrite)
{
    const char *I2C_WRITE_TAG = "I2C WRITE";
    uint8_t write_buffer[2] = {registerAddress,valueToWrite};
    esp_err_t outcome;

    outcome = i2c_master_write_to_device(I2CportNumber,I2CdeviceAddress,write_buffer,2,10/portTICK_PERIOD_MS);
    if (outcome==ESP_OK)
        {
            ESP_LOGI(I2C_WRITE_TAG,"[I2C PORT %d], [Device %#04x], [Register %#04x] : %#04x write OK. Code %#04x.",I2CportNumber,I2CdeviceAddress,registerAddress,valueToWrite,outcome);
        }
    else if (outcome!=ESP_OK) 
        {
            ESP_LOGE(I2C_WRITE_TAG,"[I2C PORT %d], [Device %#04x], [Register %#04x] : %#04x write FAILED. Code %#04x.",I2CportNumber,I2CdeviceAddress,registerAddress,valueToWrite,outcome);
        };

}

/**SUS_I2C_WriteByte: Writes one 8-bit value to the device at a given I2C address and issues full STOP condition afterwards (i.e. releases the physical bus). Uses ESP-IDF's "I2C link queue" API method. 
 * NOTE: When interfacing with I2C sensors, this function generally will not be very useful if you are trying to write to the registers. 
 * Most sensors require a WRITE-WRITE sequence of I2C operations WITHOUT a STOP inbetween to first SELECT the register of the sensor, and only then WRITE - not just a simple WRITE. Consult your sensor device's datasheet.
 * Parameter "I2CportNumber" is just an integer number 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * Parameter "I2CdeviceAddressHex" is an integer number from 0 to 127 (as per I2C limit of 127 addresses). Preferrably should be written in a hex number format (0x) for clarity, but can be decimal too.
 * Parameter "value" is the 8-bit integer you want to write to the device. Can be written in decimal, hex or binary.
 * EXAMPLE USE: SUS_I2C_WriteByteToSlave(0,0x4A,0b00000001); Writes the value 0b00000001 (0x01 or 1) to the device at address 0x04A.
*/
void SUS_I2C_WriteByteToSlave(uint8_t I2CportNumber, uint8_t I2CdeviceAddress, uint8_t valueToWrite)
{
    char *I2C_WRITE_TAG = "I2C WRITE"; //Tag (essentially a text label) for debug messages.
    esp_err_t outcome;              // Used to report error/success. If it is 0 = all good, -1 = something went wrong, 263 (0x107) = timeout.

    uint8_t WRITE_MODE = 0;         // Write mode - LOW bus, hence 0.

    i2c_cmd_handle_t cmdSeq = i2c_cmd_link_create();                   // Creates the I2C command sequence list. This list will contain your I2C commands. DOES NOT PERFORM ANY COMMANDS ON ITS OWN!
        i2c_master_start(cmdSeq);                                              //START condition command.
        i2c_master_write_byte(cmdSeq,(I2CdeviceAddress<<1)|WRITE_MODE,true);   //Select the slave with the given address and put it in the "WRITE TO" mode.
        i2c_master_write_byte(cmdSeq,valueToWrite,true);                       //Write a byte (8bits) to the slave device. 
                                                                            //WARNING:  This will NOT write to the registers of I2C sensor "as is". 
                                                                            //          At most it might select the register address of the slave for subsequent writing. 
                                                                            //          If you need to access registers, use the  "WriteToRegister" function. Also, consult the I2C slave's DATASHEET.
        i2c_master_stop(cmdSeq);                                               //          STOP condition command. 

    outcome = i2c_master_cmd_begin(I2CportNumber, cmdSeq, 10/portTICK_PERIOD_MS);      //EXECUTE THE ABOVE I2C COMMANDS!
    if (outcome==ESP_OK)
        {
            ESP_LOGI(I2C_WRITE_TAG,"[I2C PORT %d], [Device %#04x] : [Value %#04x] write OK. Code %#04x.",I2CportNumber,I2CdeviceAddress,valueToWrite,outcome);
        }
    else if (outcome!=ESP_OK) 
        {
            ESP_LOGE(I2C_WRITE_TAG,"[I2C PORT %d], [Device %#04x] : [Value %#04x] write FAILED. Code %#04x.",I2CportNumber,I2CdeviceAddress,valueToWrite,outcome);
        };

    i2c_cmd_link_delete(cmdSeq);
}

/**SUS_I2C_WriteByte_EZ: Writes one 8-bit value to the device at a given I2C address and issues full STOP condition afterwards (i.e. releases the physical bus). Uses ESP-IDF's "write_to_device" "EASY WAY"(tm) wrapper function.
 * NOTE: When interfacing with I2C sensors, this function generally will not be very useful if you are trying to write to the registers. 
 * Most sensors require a WRITE-WRITE sequence of I2C operations WITHOUT a STOP inbetween, and not just a simple WRITE. Consult your sensor device's datasheet.
 * Parameter "I2CportNumber" is just an integer number 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * Parameter "I2CdeviceAddressHex" is an integer number from 0 to 127 (as per I2C limit of 127 addresses). Preferrably should be written in a hex number format (0x) for clarity, but can be decimal too.
 * Parameter "value" is the 8-bit integer you want to write to the device. Can be written in decimal, hex or binary.
 * EXAMPLE USE: SUS_I2C_WriteByteToSlave_EZ(0,0x4A,0b00000001); Writes the value 0b00000001 (0x01 or 1) to the device at address 0x04A.
*/
void SUS_I2C_WriteByteToSlave_EZ(int I2CportNumber,int I2CdeviceAddress, uint8_t valueToWrite)
{
    char *I2C_WRITE_TAG = "I2C WRITE";
    esp_err_t outcome;
    outcome = i2c_master_write_to_device(I2CportNumber,I2CdeviceAddress,&valueToWrite,1,5/portTICK_PERIOD_MS);
            if (outcome==ESP_OK) 
            {
                ESP_LOGI(I2C_WRITE_TAG,"[I2C PORT %d], [Device %#04x]: [Value %#04x] write OK. Code %#04x.",I2CportNumber,I2CdeviceAddress,valueToWrite,outcome);
            }
        else if (outcome!=ESP_OK) 
            {
                ESP_LOGE(I2C_WRITE_TAG,"[I2C PORT %d], [Device %#04x] : [Value %#04x] write FAILED. Code %#04x.",I2CportNumber,I2CdeviceAddress,valueToWrite,outcome);
            };

}

/**Writes multiple 8-bit values to the device at a given I2C address one after the other, without STOP conditions inbetween.
 * Parameter "I2CportNumber" is just an integer number 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * Parameter "I2CdeviceAddress" is an integer number from 0 to 127 (as per I2C limit of 127 addresses). Preferrably should be written in a hex number format (0x) for clarity, but can be decimal too.
 * Parameter "arrayOfValuesToWrite" is the array of 8-bit values you want to write to the device. Yes, simple as uint8_t myArray[2];
 * Paramwtwe "amountOfValuesToWrite" is the amount of values from the array you want to write. Set to array size if you want to write the entire array.
 * EXAMPLE USE: uint8_t writeList[5] = {1,2,3,4,5};
 *              SUS_I2C_WriteByteArrayToSlave_EZ(0,0x4A,writeList,2); //Writes first two values from the writeList array to the device with address 0x4A.
*/
void SUS_I2C_WriteByteArrayToSlave_EZ(int I2CportNumber,int I2CdeviceAddress, uint8_t *arrayOfValuesToWrite, uint8_t amountOfValuesToWrite)
{
    char *I2C_WRITE_TAG = "I2C WRITE";
    esp_err_t outcome;

    outcome = i2c_master_write_to_device(I2CportNumber,I2CdeviceAddress,arrayOfValuesToWrite,amountOfValuesToWrite,10/portTICK_PERIOD_MS);//i2c_master_write_to_device(I2CportNumber,I2CdeviceAddressHex,I2CwriteArray,sizeof(I2CwriteArray),10/portTICK_PERIOD_MS);
            if (outcome==ESP_OK) 
            {
                printf("Successfully wrote: ");
                for (size_t i = 0; i < amountOfValuesToWrite; i++)
                {
                    printf("%#04x ",arrayOfValuesToWrite[i]);
                    
                }
                printf("to device at address %#04x. Code %d(%#04x).\n\r",I2CdeviceAddress, outcome,outcome);
            }
        else if (outcome!=ESP_OK) 
            {
                ESP_LOGI(I2C_WRITE_TAG,"Failed to write to device at address %#04x. Code %d(%#04x).\n",I2CdeviceAddress, outcome,outcome);
            };

}


/**SUS_I2C_WriteByte: Directly control the I2C GPIO to send custom data pulses. Pushes one 8-bit value to the I2C bus followed by a full STOP.
 * WARNING: ADVANCED USERS ONLY. You will need to construct and supply your own 8-bit data packet! 
 * Parameter "I2CportNumber" is just an integer number 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * Parameter "valueToWrite" is the 8-bit integer you want to write to the device. Can be written in decimal, hex or binary.
 * EXAMPLE USE: SUS_I2C_WriteByteToBus_RAW(0,0b00000001); //Pushes a value of 0x01 onto the I2C bus.
*/
void SUS_I2C_WriteByteToBus_RAW(uint8_t I2CportNumber, uint8_t valueToWrite)
{
    char *I2C_WRITE_TAG = "I2C RAW WRITE"; //Tag (essentially a text label) for debug messages.
    esp_err_t outcome;              // Used to report error/success. If it is 0 = all good, -1 = something went wrong, 263 (0x107) = timeout.

    i2c_cmd_handle_t cmdSeq = i2c_cmd_link_create();                   // Creates the I2C command sequence list. This list will contain your I2C commands. DOES NOT PERFORM ANY COMMANDS ON ITS OWN!
        i2c_master_start(cmdSeq);                                           //START condition command.
        i2c_master_write_byte(cmdSeq,valueToWrite,true);                    //Pushes the byte onto the I2C bus
        i2c_master_stop(cmdSeq); 
    outcome = i2c_master_cmd_begin(I2CportNumber, cmdSeq, 10/portTICK_PERIOD_MS);      // THIS LINE PERFORMS ALL THE ABOVE I2C COMMANDS ON THE PHYSICAL BUS.
    if (outcome==ESP_OK)
        {
            ESP_LOGW(I2C_WRITE_TAG,"[I2C PORT %d] : [Value %#04x] RAW write OK. Code %d(%#04x).",I2CportNumber,valueToWrite,outcome,outcome);
        }
    else if (outcome!=ESP_OK) 
        {
            ESP_LOGE(I2C_WRITE_TAG,"[I2C PORT %d]: [Value %#04x] RAW write FAILED. Code %d(%#04x).",I2CportNumber,valueToWrite,outcome,outcome);
        };

    i2c_cmd_link_delete(cmdSeq);
}

/* 
 ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄ 
▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌
▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀▀▀  ▀▀▀▀█░█▀▀▀▀ 
▐░▌       ▐░▌▐░▌          ▐░▌          ▐░▌               ▐░▌     
▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄      ▐░▌     
▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌     ▐░▌     
▐░█▀▀▀▀█░█▀▀ ▐░█▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀      ▐░▌     
▐░▌     ▐░▌  ▐░▌                    ▐░▌▐░▌               ▐░▌     
▐░▌      ▐░▌ ▐░█▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄▄▄      ▐░▌     
▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌     ▐░▌     
 ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀       ▀                                                                                                                    
 */

/**Force-resets the I2C bus back to HIGH SCL and HIGH SDA by issuing stop-start-stop conditions. 
 * Use when either or both of your I2C bus SCL/SDA lines got physically locked down at LOW level for whatever reason. How to check? Use the LED and a resistor.
 * Parameter "I2CportNumber" is just an integer number 1 or 0, corresponding to two ports of ESP32 with indexes 1 and 0.
 * EXAMPLE USE: SUS_I2C_ResetBus(0); Resets SCL and SDA lines of I2C at port 0.
*/
void SUS_I2C_ResetBus(uint8_t I2CportNumber)
{
    const char *I2C_RESET_TAG = "I2C RESET"; //Tag (essentially a text label) for debug messages.
    esp_err_t outcome;              // Used to report error/success. If it is 0 = all good, -1 = something went wrong, 263 (0x107) = timeout.

    i2c_cmd_handle_t cmdSeq = i2c_cmd_link_create();	    // Creates the I2C command sequence list. This list will contain your I2C sequence. DOES NOT PERFORM ANY COMMANDS ON ITS OWN!
        
        i2c_master_stop(cmdSeq);                            // STOP condition.
        i2c_master_start(cmdSeq); 		                    // START condition.										
        i2c_master_stop(cmdSeq);                            // STOP condition.
                                                       
    outcome = i2c_master_cmd_begin(I2CportNumber, cmdSeq, 10/portTICK_PERIOD_MS);       // THIS LINE PERFORMS ALL THE ABOVE I2C COMMANDS ON THE PHYSICAL BUS.
    if (outcome==ESP_OK) 
        {
            ESP_LOGI(I2C_RESET_TAG,"Successfully reset the I2C bus at port %d. Code %#04x.\n\r",I2CportNumber, outcome);
        }
    else if (outcome!=ESP_OK) 
        {
            //Check the I2C address value, physical contacts, pullup resistor values, I2C command sequence and/or bus signal rise rate (depends on overall capacitance).\n\r Also, make ABSOLUTELY sure that you've run the I2C initialization routine first! 
            ESP_LOGE(I2C_RESET_TAG,"Force reset I2C port %d. Code %#04x.\n\r",I2CportNumber, outcome);
        };

    i2c_cmd_link_delete(cmdSeq);                                                        //Deletes the I2C command sequence to free the RAM.
}


/*
 ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄ 
▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌
▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌ ▀▀▀▀█░█▀▀▀▀  ▀▀▀▀█░█▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀ 
▐░▌       ▐░▌▐░▌       ▐░▌▐░▌       ▐░▌     ▐░▌          ▐░▌     ▐░▌       ▐░▌▐░▌          
▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄█░▌▐░▌       ▐░▌     ▐░▌          ▐░▌     ▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄▄▄ 
▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌     ▐░▌          ▐░▌     ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌
▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀█░█▀▀ ▐░▌       ▐░▌     ▐░▌          ▐░▌     ▐░█▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀█░▌
▐░▌          ▐░▌     ▐░▌  ▐░▌       ▐░▌     ▐░▌          ▐░▌     ▐░▌                    ▐░▌
▐░▌          ▐░▌      ▐░▌ ▐░█▄▄▄▄▄▄▄█░▌     ▐░▌      ▄▄▄▄█░█▄▄▄▄ ▐░▌           ▄▄▄▄▄▄▄▄▄█░▌
▐░▌          ▐░▌       ▐░▌▐░░░░░░░░░░░▌     ▐░▌     ▐░░░░░░░░░░░▌▐░▌          ▐░░░░░░░░░░░▌
 ▀            ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀       ▀       ▀▀▀▀▀▀▀▀▀▀▀  ▀            ▀▀▀▀▀▀▀▀▀▀▀ 
===============================================================================
|---Protips if you are sp00ked.
|______________________________
|---What the f is ESPLOGI?
    |   ESPLOGI is just a fancy printf() that comes in different flavours ;)
    |       ESPLOGI - lime green (information)
    |       ESPLOGW - banana yellow (warning)
    |       ESPLOGE - strawberry red (error)
    |   Usage and syntax is the same as printf() except you also should add the TAG parameter (which is just the label).
__________________________________
|---What is "&" ?
    |    When placed in front of the variable's name, & provides the memory address of the variable instead of the variable's direct value.
    |        int lul = 999;     //Variable "lul" declared at address 1234567
    |        printf("%d", lul);   //Will print 999
    |        printf("%d", &lul);  //Will print 1234567, a pointer value.
    |
    |    & is useful when the function takes the pointer (I.E. memory address) as an argument, but all you have is a variable's name.
    |    Example:
    |        i2c_master_write_read_device(uint8_t * write_buffer)
    |        
    |        The function above takes a pointer as an argument. If you do: 
    |            uint8_t lul = 999;
    |            i2c_master_write_read_device(lul);
    |        You will get a warning and the function will likely not work as intended.
    |
    |        Do the following instead if you want the function to use the variable lul:
    |            uint8_t lul = 999;
    |            i2c_master_write_read_device(&lul);



|  Example of reading a register from device address 0x04:
|    
|    CMD: [START][7BIT SLAVE ADDRESS][WRITE BIT][SLAVE ACK][8BIT REGISTER ADDRESS][SLAVE ACK][REPEATED START][7BIT SLAVE ADDRESS][READ BIT][SLAVE ACK][DATA TO BE READ][MASTER NACK][STOP]
|    SDA:    0           0x4A            0          0              0x03              0                                0x4A           1          0          0x29             1         1
|    SCL:    1      0101010101010       10         10         1010101010101010      10              10            10101010101010    10         10     1010101010101010     10         1
|    SCL:   HIGH    7 falling edges     1FE        1FE        8 falling edges       1FE             1FE           7 falling edges   1FE        1FE     8 falling edges     1FE       HIGH
|    Bits from SDA are processed on the falling edge of the clock by both master and slave.
*/

