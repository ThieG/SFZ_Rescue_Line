


typedef struct RoboterBetriebsDaten {
  bool Stat_LineAktFertigFlag;
  unsigned long Stat_LoopCounter;
  unsigned long Stat_LoopDurationMax;
  uint8_t Stat_EnableSerialLog;

  int16_t Out_MotorAntriebGeschwindigkeit;
  int16_t Out_ServoLenkungPosition;
  uint8_t Out_RGBSensorFarbe;
  float   Out_RGBEmpfindlichkeit;
  
  int16_t In_Abweichung;
  int16_t In_LetzteAbweichung;
  
} RoboterBetriebsDaten;
