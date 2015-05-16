/******************* Emergency Flags ****************
 * source: Found in CommunicationRobotPilot Folder
 ***************************************************/
/*

all clear = 0 or null,
set = One Byte combinable flags bits{
 1 = latency           0b00000001
 2 = obstacle,         0b00000010
 4 = stall,            0b00000100
 8 = unsafe position,  0b00001000
 16 = battery,         0b00010000
 32 = temperature      0b00100000
 64 = command time-out ==> from arduino
*/

/********************** Telemetry Packet *********************
 * When using Bluetooth or OTG this is where the Command ID  * 
 * and associated bytes are obtained. 
 * Packet Structure based on CCSDS Standards
 * http://public.ccsds.org/publications/archive/102x0b5s.pdf *
 *
 * State Byte   
 *       Index  Bits  Description        Default            EEPROM Example
 *   0   0       3    3.1.1 Version Number 110       
 *               3    3.1.2 Packet ID         010
 *               2    Reserved                   10         data[0] = 0xCA                      
 *   1   1       4    Reserved             000      
 *               4    3.1.4 Packet Length     00001 - 10100 data[1] = 0x14 Bytes in Telemetry Data Field
 *                                                                         excluding checksum
 *   2   2            3.2 Telemetry Data Packet Field       data[2] = 0x0A EEPROM response
 *       :                                                       :
 *       N+1          where N = 00001 - 10100               data[21] = 16th parameter
 *   3   N+2          checksum                              data[22] = longitudinal redundancy check (LRC)
 *                    warning: does not protect against byte reversals http://en.wikipedia.org/wiki/Checksum
 *   4                Error State 
 ************************************************************/

/******************* Robot Sensors ****************
* source: Found in CommunicationRobotPilot Folder
 ***************************************************/
   
uint16_t sensor_value;              // Used for Current Sensor
                                    // last sensor value sent to control panel
                                    // used for comparison with current sensor value
                                    // if different data packet is sent to the control panel
uint16_t  currentM1=0;              // 10 bit right justified value from ADC
uint16_t  currentM2=0;              // 10 bit right justified value from ADC
uint16_t  tempChassis=0;            // 10 bit right justified value from ADC
uint16_t  positionPan=0;
uint16_t  positionTilt=0;

 /************************  Send Data ************************
 *   This is where sensor value is checked and if different  *
 *  a data packet of three bytes (Command ID and associated) *
 *                is sent from Arduino to Phone              *
 *************************************************************/
  
void sendData(){
     uint16_t data;
     int16_t battery_value;
     int16_t sensor_value;
     static uint16_t pingRangeL=0;
     static uint16_t pingRangeR=0;
     const  int16_t tolerance = 4;    
    
    #if MicroRover
    sensor_value = getPanPosition();
    if (sensor_value != positionPan){
      positionPan = sensor_value;          // update
      sendWordPacket(0x08, sensor_value);
    }
    sensor_value = getTiltPosition();
    if (sensor_value != positionTilt){
      positionTilt = sensor_value;          // update
      sendWordPacket(0x09, sensor_value);
    }
    #endif

#if pinger == TRUE
      data= getRangeLeft();
   if(abs(data-pingRangeL) > tolerance){
      pingRangeL=data;     
      sendWordPacket(RANGE_LEFT_ID, pingRangeL); // distance sensor data package
      }
      
      data= getRangeRight();
   if(abs(data-pingRangeR) > tolerance){
      pingRangeR=data;     
      sendWordPacket(RANGE_RIGHT_ID, pingRangeR); // distance sensor data package
      }  
#endif


#if Motor_Battery == TRUE     
        battery_value = readFuelGauge(DIRTY_BAT_PIN,battery_motor_V0,battery_motor_dV,battery_motor_Vsafe);   
    if ( !((batteryMotorsV - tolerance <= battery_value) && (battery_value <= batteryMotorsV + tolerance)) ) {
      if (batteryMotorsV == FLAG){
        if (battery_value > 10){
          // come out of safe mode when battery is charged to at least 10%
          batteryMotorsV = battery_value;
        }
        // stay in safe mode
      } 
      else{
        batteryMotorsV = battery_value;   // update
        if (battery_value == FLAG) {
          // battery has just been depleted
          safeRover();   // Need to actually sleep the rover ****
          // Serial.println("Motor Battery Depleted");    // ****
        }
        else {
          // normal operation
          batteryMotorsV = battery_value;                        // update  
          sendWordPacket(DIRTY_BATTERY_ID,(uint16_t) battery_value);   // ****
          // Serial.print("Motor Battery Voltage = ");
          // Serial.println(batteryMotorsV);
        }
      }
    }
#endif    
#if Digital_Battery == TRUE     
  battery_value = readFuelGauge(CLEAN_BAT_PIN,battery_digital_V0,battery_digital_dV,battery_digital_Vsafe);
    if ( !((batteryDigitalV - tolerance <= battery_value) && (battery_value <= batteryDigitalV + tolerance)) ) {
      if (batteryDigitalV == FLAG){
        if (battery_value > 10){
          // come out of safe mode when battery is charged to at least 10%
          batteryDigitalV = battery_value;
        }
        // stay in safe mode
      } 
      else{
        batteryDigitalV = battery_value;   // update
        if (battery_value == FLAG) {
          // battery has just been depleted
          safeRover();   // Need to actually sleep the rover      ****
          // Serial.println("Clean Battery Depleted");         // ****
        }
        else {
          // normal operation
          batteryDigitalV = battery_value;            // update  
          sendWordPacket(CLEAN_BATTERY_ID,(uint16_t) battery_value); // ****
          // Serial.print("Clean Battery Voltage = ");
          // Serial.println(batteryDigitalV);
        }
      }
    }
#endif

 /*   
    if(millis() - timer > 500) {  
   //Add all different parameter that will be worked on
    sensor_value = analogRead(MOTOR1CURRENT_PIN);
    if (sensor_value != currentM1){
      currentM1 = sensor_value;               // update
     sendWordPacket(MOTOR1_CURRENT_ID,sensor_value);
    }
      
    sensor_value = analogRead(MOTOR2CURRENT_PIN);
    if (sensor_value != currentM2){
      currentM2 = sensor_value;               // update
      sendWordPacket(MOTOR2_CURRENT_ID,sensor_value);
    }
    sensor_value = analogRead(TEMPERATURE_PIN);
    if (sensor_value != tempChassis); {
      tempChassis = sensor_value;             // update
      sendWordPacket(TEMP_SENSOR_ID,sensor_value);
    }
    timer = millis(); //reset the timer 
   }
*/  
}

/* EEPROM Response Example
 * i =  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22
 * test data     1  2  3  4  5  6  7  8  9  A  B  C  D  E  F 10
 *                                                               | <- checksum
 * note: response does not include address or number of bytes, 
 *       which was included in the request.
 */   

void sendPacket(uint8_t id,  uint8_t data_field[], uint8_t N)  // alt. uint8_t * data_field
{
  static uint8_t data[23];  // 23 bytes = ID + Length + SENSOR + maximum number of parameters 19 + Checksum
                            // EEPROM read/write maximum block size = 16
                            // maximum index 22
  uint8_t datum;
  uint8_t checksum = 0;     // LRC byte

  data[0] = TELEMETRY_PACKET_ID;
  data[1] = N+1;            // id + eeprom data
  data[2] = id;
  checksum = data[0] ^ data[1] ^ data[2];  // update LRC
  for(uint8_t i = 0; i < N; i++){
   datum = data_field[i];
   data[i+3] = datum;
   checksum ^= datum;
  }
  data[N+3] = checksum;      // N+3 = last byte address
  
  #if bluetooth
  Serialx.write(data,N+4);   // N+4 = number of bytes to send
  #else
  Serial.write(data,N+4);
  #endif
}

void sendPacket(uint8_t id)  // alt. uint8_t * data_field
{
  uint8_t data[4];  // 4 bytes = ID + Length + id + Checksum
  data[0] = TELEMETRY_PACKET_ID;
  data[1] = 1;             // id only
  data[2] = id;
  data[3] = data[0] ^ data[1] ^ data[2];  // update LRC
  
  #if bluetooth
  Serialx.write(data,4);   // 4 = number of bytes to send
  #else
  Serial.write(data,4);
  #endif
}

// ****** Overload as sendPacket ********
void sendWordPacket(uint8_t id, uint16_t value){
  uint8_t wordData [2] = {highByte(value), lowByte(value)};
  sendPacket(id, wordData, 2);    // bug fix: was 3 in version v7
  
  // sendPacket(id, uint8_t [2] {highByte(value),lowByte(value)},  3);
}
