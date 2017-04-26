/*!
****************************************************************************************************
* \file      SFZ_Rescue_Line.ino
*
* \ingroup   RESCUE_LINE
*
*            Arduino Software als Beispiel, wie so ein Programm funktionieren und aussehen kann.
*
****************************************************************************************************
*/
/*!
****************************************************************************************************
* \defgroup RESCUE_LINE     Robocup Rescue Line
****************************************************************************************************
*/
#include  "MeAuriga.h"


#define SERVO_LENKUNG_MITTE   90u  /**< Legt die Mittelstellung der Lenkung fest, also Geradeausfahren! */
#define SERVO_RECHTS_MAX       0u  /**< Legt den maximalen Ausschlag nach rechts fest! */
#define SERVO_LINKS_MAX      170u  /**< Legt den maximalen Ausschlag nach links fest! */

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Aktoren 
*/
/*------------------------------------------------------------------------------------------------*/
MeDCMotor MotorAntrieb(M1);

MePort ServoPort(PORT_6);
int16_t ServoLenkungPin = ServoPort.pin1();
Servo ServoLenkung;

MeRGBLed RGBLedOnBoard(0, 12);

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Sensoren
*/
/*------------------------------------------------------------------------------------------------*/
MeGyro GyroOnBoard(0, 0x69);

MePort LineArrayPort(PORT_7);
const int LineArrayPin = LineArrayPort.pin1();

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Globale Variablen und Funktionsprototypen die man hier halt so braucht!
*/
/*------------------------------------------------------------------------------------------------*/
typedef struct RoboterBetriebsDaten {
  uint8_t In_LineArray;

  int16_t Out_MotorAntriebGeschwindigkeit;
  int16_t Out_ServoLenkungPosition;
  
  int32_t Int_Abweichung;
  
} RoboterBetriebsDaten;
RoboterBetriebsDaten Roboter;

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

  Serial.begin(9600);
  
  Aktoren_Setup(&Roboter); 
  
  Sensoren_Setup();
  
  Anzeige_Setup();
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Arduino Main Loop
*
*            Wird durchgehend immer wieder durchlaufen, solange das Arduino-Board eingeschaltet ist.
*/
/*------------------------------------------------------------------------------------------------*/
void loop() {

  Serial.print(millis());
  Serial.println(" - Lese die Sensoren!");
  Sensoren_Update(&Roboter);

  Serial.print(millis());
  Serial.print(" - Linie: ");
  Serial.println(Roboter.In_LineArray, BIN); 

  Roboter.Int_Abweichung =  Abweichung(Roboter.In_LineArray);
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Abweichung von der schwarzen Line
*
*            Hier wird die Abweichung von der schwarzen Linie ermittelt, um diese anschliesend 
*            an den Regler fuer den Lenkausschlag zu geben.
*            
* \param           
*/
/*------------------------------------------------------------------------------------------------*/
int32_t Abweichung (uint8_t sensorWert)
{
  int32_t result = 0;
  switch(sensorWert) {
    case B00000000:
    case B00111111:
      break;
    default:
      break;
  }

  return result;
}


 



