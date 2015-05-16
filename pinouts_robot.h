// Pinouts defined in paperbot "The Design" document Resource Worksheet

const int led = 13;  // WARNING: assumes use of Arduino UNO not Sparkfun Pro Micro

// sparkfun TB6612FNG (PaperBot) motorshield and SN754410 (MicroRover) Motor Driver
//motor A connected between A01 and A02
//motor B connected between B01 and B02

const int STBY = 12;  // standby

//Motor A
const int PWMA = 3;  // Speed control 
const int AIN1 = 4; // Direction    **** guess A0 = D18
const int AIN2 = 7; // Direction    **** guess A1 = D19

//Motor B
const int PWMB = 5;  // Speed control
const int BIN1 = 8; // Direction
const int BIN2 = 9;  // Direction                            

// Legacy definitions 
// Sensor to Arduino Mega ADK Pin Mapping
#define MOTOR1CURRENT_PIN     A0   // Analog Pins
#define MOTOR2CURRENT_PIN     A1
#define TEMPERATURE_PIN       A2
#define CLEAN_BAT_PIN         A3
#define DIRTY_BAT_PIN         A4
                              // Digital Pins                             
#define TRIGGER_PIN_LEFT  22  // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN_LEFT     23  // Arduino pin tied to echo pin on ping sensor.
#define TRIGGER_PIN_RIGHT 24  // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN_RIGHT    25  // Arduino pin tied to echo pin on ping sensor.
#define SERVO_PIN_PAN     6  // Arduino pin tied to pan servo pin.
#define SERVO_PIN_TILT    2  // Arduino pin tied to tilt servo pin.


/******************* Packet IDs ****************
 * source: Arxterra
 ***************************************************/
#define COMMAND_PACKET_ID    0xA5
#define TELEMETRY_PACKET_ID  0xCA

/******************* Robot Commands ****************
 * source: Arxterra
 ***************************************************/
// Arxterra Commands to Numeric Value Mapping
//               Data[0] =     CMD TYPE | Qual | Arguments
//                           bit  7654321   0    Bytes    N = 1 + bytes 
#define MOVE            0x01   // 0000000   1     4      
#define CAMERA_MOVE     0x02   // 0000001   0     4
#define CAMERA_HOME     0x04   // 0000010   0     0
#define CAMERA_RESET    0x05   // 0000010   1     0
#define READ_EEPROM     0x06   // 0000011   0     3 
#define WRITE_EEPROM    0x07   // 0000011   1     3 + b
#define SAFE_ROVER      0x08   // 0000100   0     0
#define SLEEP           0x0A   // 0000101   0     0
#define WAKEUP          0x0B   // 0000101   1     0
#define HEADLIGHT_OFF   0x0C   // 0000110   0     0
#define HEADLIGHT_ON    0x0D   // 0000110   1     0
#define PING_INTERVAL   0x10   // 0001000   0
#define PING            0x11   // 0001000   1     1
#define HEADING         0x12   // 0001001   0
#define CURRENT_COORD   0x13   // 0001001   1         (float) Latitude, (float) Longitude
#define WAYPOINT_COORD  0x14   // 0001010   0
#define WAYPOINT_DELETE 0x16   // 0001011   0
#define WAYPOINT_MOVE   0x17   // 0001011   1
#define WAYPOINTS_OFF   0x18   // 0001100   0
#define WAYPOINTS_ON    0x19   // 0001100   1
#define WAYPOINTS_CLEAR 0x1A   // 0001101   0

// 0x40 - 0x5F  32 Custom Commands, 1 - 2 byte arguments

/******************* Robot Telemetry ***************
 * source: Arxterra
 ***************************************************/
 // Telemetry Identifiers to Numeric Value Mapping 
#define  MOTOR1_CURRENT_ID  0x01           // motor 1 is left motor
#define  MOTOR2_CURRENT_ID  0x02           // motor 2 is right motor
#define  TEMP_SENSOR_ID     0x03           // temperature sensor
#define  RANGE_LEFT_ID      0x04           // ultrasonic range 1 is left
#define  RANGE_RIGHT_ID     0x05           // ultrasonic range 2 is right
#define  CLEAN_BATTERY_ID   0x06           // Arduino battery
#define  DIRTY_BATTERY_ID   0x07           // DC and servo motors battery 
#define  PAN_POSITION_ID    0x08           // originally defined as pan and tilt
#define  TILT_POSITION_ID   0x09           // not in original definition
#define  EEPROM_RESPONSE_ID 0x0A           // sent in response to EEPROM Read Command
#define  EMERGENCY_ID       0x0B

#define  COMMAND_ECHO_ID    0x0D
#define  EXCEPTION_ID       0x0E           // arduino error code exception
#define  PONG_ID            0x11
#define  ROUTE_STATUS_ID    0x12
#define  WAYPOINT_ARRIVE_ID 0x13

 /********************** Exception Codes ********************
 *   01    Start byte 0xA5 expected
 *   02    Packet length out of range 1 - 20
 *   03    LRC checksum error
 *   04    Undefined command decoder FSM state
 *   05    Array out of range i >= 23
 ************************************************************/
 
 /********************** Emergency Codes ********************
 *   0x0100    Watchdog timeout 0x01 with ancillary byte 0x00  
 ************************************************************/
 #define WATCHDOG_TIMEOUT   0x0100
