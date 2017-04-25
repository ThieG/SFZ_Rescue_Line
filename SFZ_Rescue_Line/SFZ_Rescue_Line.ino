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

  Aktoren_Setup();

  Anzeige_Setup();
  
  Sensoren_Setup();

}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Arduino Main Loop
*
*            Wird durchgehend immer wieder durchlaufen, solange das Arduino-Board eingeschaltet ist.
*/
/*------------------------------------------------------------------------------------------------*/
void loop() {

  GyroOnBoard.update();
}


