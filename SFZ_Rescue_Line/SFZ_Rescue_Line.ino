/*!
****************************************************************************************************
* \file      SFZ_Rescue_Line.ino
*
* \ingroup   RESCUE_LINE
*
*            Arduino Software als Beispiel, wie so ein Programm funktionieren und aussehen kann.
*            
* \note      Fuer den Auriga muss das "Arduino Mega2560" Board eingestellt und
*            das "MeAuriga.h" File includiert werden.
****************************************************************************************************
*/
/*!
****************************************************************************************************
* \defgroup RESCUE_LINE     Robocup Rescue Line
****************************************************************************************************
*/
#include "MeAuriga.h"
#include "SFZ_Rescue_Line.h"
#include "MeRGBLineFollower.h"

#define LOOP_UPDATE_RATE_MS 50

/*----------------------------------------------------------------------------*/
/*!
* \brief    Sring Objects for Test Communication
*/
/*----------------------------------------------------------------------------*/
String meinTextVonDerKonsole = "";
unsigned int meinTextLaenge = meinTextVonDerKonsole.length();

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Globale Variablen und Funktionsprototypen die man hier halt so braucht!
*/
/*------------------------------------------------------------------------------------------------*/
RoboterBetriebsDaten Roboter;

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Bedientasten
*/
/*------------------------------------------------------------------------------------------------*/
Me4Button myButtons(PORT_9);
uint8_t keyPressedPrevious;

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Linefollower PID Regelparameter und Konstanten!
*/
/*------------------------------------------------------------------------------------------------*/
float PID_kp = 1.0; 
float PID_ki = 0.0;
float PID_kd = 0.0;
float PID_IntegralValue;
float PID_DerivativeValue;

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Arduino Setup
*
*            Wird beim Start des Programms (entweder nach dem uebertragen auf das Board oder 
*            nach Druecken des Reset-Tasters) einmalig aufgerufen, 
*            um z. B. Pins als Eingang oder Ausgang zu definieren.
*/
/*------------------------------------------------------------------------------------------------*/
void setup() {

  Serial.begin(115200);
  Serial.println(F(" "));
  Serial.println(F("------------------------------------"));
  Serial.println(F("    _____ ______ ______ "));
  Serial.println(F("   / ____|  ____|___  / "));
  Serial.println(F("  | (___ | |__     / /  "));
  Serial.println(F("   \\___ \\|  __|   / /   "));
  Serial.println(F("   ____) | |     / /__  "));
  Serial.println(F("  |_____/|_|    /_____| "));
  Serial.println(F(" "));
  Serial.println(F("------------------------------------"));
  
  Serial.println(F("INFO: Aktoren Setup..."));
  Aktoren_Setup(); 
  Serial.println(F("------------------------------------"));
  Serial.println(F("INFO: Sensoren Setup..."));
  Sensoren_Setup();
  Serial.println(F("------------------------------------"));
  Serial.println(F("INFO: Anzeige Setup..."));
  Anzeige_Setup();
  Serial.println(F("------------------------------------"));
  Serial.println(F("INFO: Tippe help "));
  
  Roboter.Out_MotorAntriebGeschwindigkeit = 60;
  
  Roboter.Out_RGBSensorFarbe = RGB_COLOUR_GREEN;
  Sensoren_LineAendereFarbe(Roboter.Out_RGBSensorFarbe);

  Roboter.Out_RGBEmpfindlichkeit = 0.3;
  Sensoren_LineAendereEmpfindlichkeit(Roboter.Out_RGBEmpfindlichkeit);
  
  Roboter.Stat_LineAktFertigFlag = true;
  Roboter.Stat_EnableSerialLog = 0;
  Roboter.Stat_LoopCounter = 0u;
  Roboter.Stat_LoopDurationMax = 0u;

  PID_IntegralValue = (float)Roboter.Out_MotorAntriebGeschwindigkeit;
  PID_DerivativeValue = 0.0;
  
  delay(100);
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Arduino Main Loop
*
*            Wird durchgehend immer wieder durchlaufen, solange das Arduino-Board eingeschaltet ist.
*/
/*------------------------------------------------------------------------------------------------*/
void loop() 
{ 
  static unsigned long NaechsterLoop = LOOP_UPDATE_RATE_MS;
  
  do {
    Sensoren_Update();    
  } while (NaechsterLoop >= millis());
  NaechsterLoop = (millis() + LOOP_UPDATE_RATE_MS);
  
  uint8_t taste = BedienTasten_Update();
  
  KonsoleCmd_Update();
      
  // Test_LineSensor();
  Test_FollowLine();
  
  
  Aktoren_Update();
  Anzeige_Update();
 
  Roboter.Stat_LoopCounter++;
  
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Linenfolger Test Program
*
*            Hiermit werden die RGB LEDs zyklisch umgeschalten und die ADC Werte an den 
*            Seriellen Plotter geschrieben!
*/
/*------------------------------------------------------------------------------------------------*/
void Test_FollowLine(void)
{
  static bool writeLabels = true;
  
  Roboter.In_Abweichung =  Sensoren_LineAbweichung();

  PID_IntegralValue =  PID_IntegralValue + Roboter.In_Abweichung;
  PID_DerivativeValue = Roboter.In_Abweichung - Roboter.In_LetzteAbweichung;
  int16_t PID_MotorGeschwindigkeit = (PID_kp * Roboter.In_Abweichung) + (PID_ki * PID_IntegralValue) + (PID_kd * PID_DerivativeValue);

  int16_t rightSpeed = Roboter.Out_MotorAntriebGeschwindigkeit + PID_MotorGeschwindigkeit;
  int16_t leftSpeed  = -1 * (Roboter.Out_MotorAntriebGeschwindigkeit - PID_MotorGeschwindigkeit);
  
  Roboter.In_LetzteAbweichung = Roboter.In_Abweichung;
  
  Aktoren_SetSpeed(leftSpeed, rightSpeed);
  
  if (Roboter.Stat_EnableSerialLog != 0) {
    if (writeLabels) {
      Serial.println("Abweichung, Links, Rechts");
      writeLabels = false;    
    } else {
      Serial.print(Roboter.In_Abweichung);
      Serial.print(",");
      Serial.print(leftSpeed);
      Serial.print(",");
      Serial.println(rightSpeed);
    }
  } else {
    writeLabels = true;     
  }
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Liniensensor Test Funktion
*
*            Hiermit werden die RGB LEDs zyklisch umgeschalten und die ADC Werte an den 
*            Seriellen Plotter geschrieben!
*/
/*------------------------------------------------------------------------------------------------*/
void Test_LineSensor(void) 
{
  static bool writeLabels = true;
  
  if (writeLabels) {
    Serial.println("Sensor,RGB_1,RGB_2,RGB_3,RGB_4");
    writeLabels = false;    
  } else {
    if (Roboter.Stat_EnableSerialLog != 0) {
      Serial.print(Roboter.Out_RGBSensorFarbe * 20u);
      Serial.print(",");
      Serial.print(Sensoren_LineADCWert(1));
      Serial.print(",");
      Serial.print(Sensoren_LineADCWert(2));
      Serial.print(",");
      Serial.print(Sensoren_LineADCWert(3));
      Serial.print(",");
      Serial.println(Sensoren_LineADCWert(4));
    }
  }
    
  if ((Roboter.Stat_LoopCounter % 100) == 0u) {
    Sensoren_LineAendereFarbe(Roboter.Out_RGBSensorFarbe);
    if (Roboter.Out_RGBSensorFarbe >= RGB_COLOUR_BLUE) {
      Roboter.Out_RGBSensorFarbe = RGB_COLOUR_RED;
    } else {
      Roboter.Out_RGBSensorFarbe++;
    }
  }
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Bedientasten Einlesen
* 
* \return    Gibt KEY_1 ... KEY_4 zurueck wenn die Taste gedrueckt wird, ansosnten KEY_NULL.
*/
/*------------------------------------------------------------------------------------------------*/
uint8_t BedienTasten_Update (void)
{
  uint8_t curKeyState;
  uint8_t keyPressed = myButtons.pressed();
  
  if (keyPressedPrevious != keyPressed) {
    curKeyState = keyPressed;
  } else {
    curKeyState = KEY_NULL;  
  }

  keyPressedPrevious = keyPressed;

  return curKeyState;
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Konsolen Kommandoparser 
*/
/*------------------------------------------------------------------------------------------------*/
void KonsoleCmd_Update(void)
{
  while(Serial.available()) {
     char inChar = Serial.read();
     meinTextVonDerKonsole += inChar;  
  }
  int meinLetztesZeichen = (meinTextVonDerKonsole.length() - 1);
  if (meinTextVonDerKonsole.charAt(meinLetztesZeichen) == '\n') {
    
    /*-------------------------------------------------*/
    /* Motor Grundgeschwindigkeit setzen               */
    /*-------------------------------------------------*/    
    if (meinTextVonDerKonsole.startsWith("set geschw ")) {
      String myString = meinTextVonDerKonsole.substring(11);
      Serial.println("----------------------------------");
      Roboter.Out_MotorAntriebGeschwindigkeit = myString.toInt();
      
      Serial.print("INFO: Set Motorgeschwindigkeit to: "); 
      Serial.println(Roboter.Out_MotorAntriebGeschwindigkeit);

    /*-------------------------------------------------*/
    /* RGB Empfindlichkeit                             */
    /*-------------------------------------------------*/
    } else if (meinTextVonDerKonsole.startsWith("set empf ")) {
      String myString = meinTextVonDerKonsole.substring(9);
      Serial.println("----------------------------------");
      Roboter.Out_RGBEmpfindlichkeit = myString.toFloat();
      Sensoren_LineAendereEmpfindlichkeit(Roboter.Out_RGBEmpfindlichkeit);
      
      Serial.print("INFO: Set RGB Sensor Empfindlichkeit to: "); 
      Serial.println(Roboter.Out_RGBEmpfindlichkeit);

    /*-------------------------------------------------*/
    /* Proportionalfaktor kp                           */
    /*-------------------------------------------------*/
    } else if (meinTextVonDerKonsole.startsWith("set kp ")) {
      String myString = meinTextVonDerKonsole.substring(7);
      Serial.println("----------------------------------");
      PID_kp = myString.toFloat();
            
      Serial.print("INFO: Set kp Faktor to: "); 
      Serial.println(PID_kp);

    /*-------------------------------------------------*/
    /* Enable/Disable log output                       */
    /*-------------------------------------------------*/
    } else if (meinTextVonDerKonsole.startsWith("log ")) {
      String myString = meinTextVonDerKonsole.substring(4);      
      Roboter.Stat_EnableSerialLog = myString.toInt();

      /* Hier keinen Ausgabe mehr, da ansonsten die Labels im Seriellen Plotter */
      /* unter Umstaenden nicht korrekt sein koennten! */  
               
    /*-------------------------------------------------*/
    /* help                                            */
    /*-------------------------------------------------*/      
    }  else if (meinTextVonDerKonsole.startsWith("show")) {      
      Serial.println("----------------------------------");      
                       
      
      Serial.print("INFO: Max Loop Dauer: "); 
      Serial.println(Roboter.Stat_LoopDurationMax);    
      Serial.print("INFO: Motorgeschwindigkeit: "); 
      Serial.println(Roboter.Out_MotorAntriebGeschwindigkeit);            
      Serial.print("INFO: RGB Sensor Empfindlichkeit: "); 
      Serial.println(Roboter.Out_RGBEmpfindlichkeit);
      Serial.print("INFO: kp Faktor: "); 
      Serial.println(PID_kp);
      Serial.print("INFO: ki Faktor: "); 
      Serial.println(PID_ki);
      Serial.print("INFO: kd Faktor: "); 
      Serial.println(PID_kd);

    /*-------------------------------------------------*/
    /* Enable/Disable log output                       */
    /*-------------------------------------------------*/
    } else if (meinTextVonDerKonsole.startsWith("help")) {      
      Serial.println("----------------------------------");
      Serial.println("HELP: show          - Gibt die aktuellen Robotereinstellungen aus");
      Serial.println("HELP: set geschw x  - Setzt die Motorgeschwindigkeit auf den Wert x");
      Serial.println("HELP: set empf x.xx - Setzt die RGB Sensor Empfindlichkeit auf den Wert x.xx");
      Serial.println("HELP: set kp x.xx   - Setzt den kp auf den Wert x.xx");
      Serial.println("HELP: log x         - Startet(1), stoppt(0) die serielle Ausgabe");

    }
           
    meinTextVonDerKonsole = "";
  }
}
