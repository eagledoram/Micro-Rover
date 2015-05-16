// Altered by Eagled'Or Am from sparkfun_TB6612FNG and L298N motor shield code
void setup_SN754410(){
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);  // motor A
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);  // motor B
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
  stop_SN754410();       // brake  
}

void stop_SN754410()        // initialize or stop L298N
{
  digitalWrite(AIN1, HIGH);  // motor 1 short brake
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);  // motor 2 short brake
  digitalWrite(BIN2, HIGH);
  digitalWrite(STBY, HIGH);  // L298N enabled 
}

void safeRover()
{
  digitalWrite(STBY, HIGH);  // L298N disabled (high impedance) 
}

void move_SN754410(uint8_t * motordata)
{
  run_SN754410(motordata[3], AIN1, AIN2);  // configure H-bridge for motor A (left)
  analogWrite(PWMA, motordata[4]);          // set speed motor A (left motor)
  run_SN754410(motordata[5], BIN1, BIN2);  // configure H-bridge for motor B (right)
  analogWrite(PWMB, motordata[6]);          // set speed motor B (right motor)
}

void run_SN754410(uint8_t dir, uint8_t pin_in1, uint8_t pin_in2)
{
  uint8_t IN1;  // see L298N Control Function Truth Table atIf nothing  bottom of page
  uint8_t IN2;
  
  switch (dir)  // set dir = motordata[1] for motor A (left) 
  {
    case 1:  // FORWARD
      IN1 = HIGH;
      IN2 = LOW;
      break;
    case 2:  // BACKWARD
      IN1 = LOW;
      IN2 = HIGH;
      break;
    case 3:  // BRAKE
      IN1 = HIGH;
      IN2 = HIGH;
      break;
    case 4:  // RELEASE
      IN1 = LOW;
      IN2 = LOW;
      break;
    default:
      IN1 = LOW;
      IN2 = LOW;
  }
  digitalWrite(pin_in1, IN1);
  digitalWrite(pin_in2, IN2); 
}


/*
Arxterra Command Format
  left motor A   
    motordata[3]
    FORWARD = index 1, BACKWARD = index 2, BRAKE = index 3, RELEASE = index 4
    motordata[4]
    0 - 255
  right motor B   
    motordata[5]
    FORWARD = index 1, BACKWARD = index 2, BRAKE = index 3, RELEASE = index 4
    motordata[6]
    0 - 255
*/

/* sparkfun_TB6612FNG/L298N Control Functions
     Source: H-SW Control Functions found in the Datasheet on Page 4
             https://www.sparkfun.com/datasheets/Robotics/TB6612FNG.pdf
     Pin#  = IN1    IN2
     Logic = inPin1 inPin2  Mode
              0     0       OFF (High Impedance)     
              0     1       BACKWARD (CCW)
              1     0       FORWARD  (CW)
              1     1       Short brake
*/
