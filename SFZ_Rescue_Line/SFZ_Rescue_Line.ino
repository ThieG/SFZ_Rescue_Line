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

#define LOOP_UPDATE_RATE_MS  50

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Globale Variablen und Funktionsprototypen die man hier halt so braucht!
*/
/*------------------------------------------------------------------------------------------------*/
typedef struct RoboterBetriebsDaten {
  uint8_t In_LineArray;

  int16_t Out_MotorAntriebGeschwindigkeit;
  int16_t Out_ServoLenkungPosition;
  
  int8_t  In_LineArrayWert;
  int32_t In_Abweichung;
  
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
  
  Aktoren_Setup(); 
  
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
void loop() 
{ 
  unsigned long NaechsterLoop = (millis() + LOOP_UPDATE_RATE_MS);
  
  Sensoren_Update();  
  
  Roboter.In_LineArrayWert = LiesLineArray();
  Roboter.In_Abweichung =  Abweichung(Roboter.In_LineArrayWert);

  SetzeMotoren(1, 0);
  
  Aktoren_Update();
  Anzeige_Update();

  while (NaechsterLoop >= millis()) {};
  
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


 



