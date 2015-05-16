// battery type(s)
#define LiPO  FALSE     // Pathfinder
#define NiMH  TRUE     // MicroRover
#define LiFePO4  FALSE   // PaperBot

/**************** Robot Configuration **************
 * Set Battery Properties                          *
 ***************************************************/
#define Digital_Battery TRUE         // TRUE if digital battery is used or using a single battery design.
#define Motor_Battery FALSE          // FALSE if no motor battery is used.
#define digital_battery_chem LiFePO4 // Digital battery chemical type(LiPO, NiMH, LiFePO4) ****************
#define digital_battery_cells 1      // Digital battery # of cells
#define motor_battery_chem NA        // Motor battery chemical type (LiPO, NiMH, LiFePO4, or NA)  **********
#define motor_battery_cells 0        // Motor battery # of cells

/************ Robot Battery Sensors ****************
* source: Found in CommunicationRobotPilot Folder
 ***************************************************/

int16_t   batteryDigitalV = 0;
int16_t   batteryMotorsV = 0;

 /******************* Battery Definitions ****************
 *      Battery properties are defined here        *
 *********************************************************/

// Battery Voltage Data
// LiPO
double  LiPO_V1 = 4.0;        // volts/cell, 90% point on LiPO curve at 1C
double  LiPO_V0 = 3.4;        // volts/cell, 10% point on LiPO curve at 1C
double  LiPO_Vsafe = 3.2;     // volts/cell, 2.7 volts/cell = discharged voltage 
// NiMH
double  NiMH_V1 = 1.1875;     // volts/cell
double  NiMH_V0 = 0.89;       // volts/cell
double  NiMH_Vsafe = 0.87;    // volts/cell, 0.9 volts/cell = discharged voltage
// LiFePO4
double  LiFePO4_V1 = 3.2;      // volts/cell
double  LiFePO4_V0 = 2.7;      // volts/cell
double  LiFePO4_Vsafe = 2.7;   // volts/cell, 0.9 volts/cell = discharged voltage

#if Digital_Battery == TRUE       // If Using a Digital or Single Battery Check whether it's LiPO, NiMH, or LiFePO4
                                  // to use correct battery values.
  #if digital_battery_chem == LiPO
    double d_V1=LiPO_V1;
    double d_V0=LiPO_V0;
    double d_Vsafe=LiPO_Vsafe;
  #elif digital_battery_chem == NiMH
    double d_V1=NiMH_V1;
    double d_V0=NiMH_V0;
    double d_Vsafe=NiMH_Vsafe;
  #elif digital_battery_chem == LiFePO4
    double d_V1=LiFePO4_V1;
    double d_V0=LiFePO4_V0;
    double d_Vsafe=LiFePO4_Vsafe; 
  #endif
  
  // Digital Battery
  double  cells_per_digital_battery = digital_battery_cells;              // 1S, 2S, or 3S
  double  battery_digital_V1 = cells_per_digital_battery * d_V1;          // volts, 90% point on battery curve at 1C
  double  battery_digital_V0 = cells_per_digital_battery * d_V0;          // volts, 10% point on battery curve at 1C
  double  battery_digital_dV  = battery_digital_V1 - battery_digital_V0;  // difference
  double  battery_digital_Vsafe = cells_per_digital_battery * d_Vsafe;    // volts, 2.7 volts/cell = discharged voltage 
#endif

#if Motor_Battery == TRUE         // If Using a Motor Battery Check whether it's LiPO, NiMH, or LiFePO4
                                  // to use correct battery values.
  #if motor_battery_chem == LIPO
    double m_V1=LiPO_V1;
    double m_V0=LiPO_V0;
    double m_Vsafe=LiPO_Vsafe;
  #elif motor_battery_chem == NiMH
    double m_V1=NiMH_V1;
    double m_V0=NiMH_V0;
    double m_Vsafe=NiMH_Vsafe;
  #elif motor_battery_chem == LiFePO4
    double m_V1=LiFePO4_V1;
    double m_V0=LiFePO4_V0;
    double m_Vsafe=LiFePO4_Vsafe;
    
  #endif
  // Motor Battery
    double  cells_per_motor_battery = motor_battery_cells;           // 1S, 2S, or 3S
    double  battery_motor_V1 = cells_per_motor_battery * m_V1;       // volts, 90% point on battery curve at 1C
    double  battery_motor_V0 = cells_per_motor_battery * m_V0;       // volts, 10% point on battery curve at 1C
    double  battery_motor_dV  = battery_motor_V1 - battery_motor_V0; // difference
    double  battery_motor_Vsafe = cells_per_motor_battery * m_Vsafe; // volts, 2.7 volts/cell = discharged voltage
#endif
