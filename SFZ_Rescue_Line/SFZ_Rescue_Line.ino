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
#include "MeAuriga.h"
#include "SFZ_Rescue_Line.h"

#define LOOP_UPDATE_RATE_MS  50

#define MOTOR_STOP     0
#define FAHR_N_VORNE   1
#define FAHR_N_HINTEN  2
#define DREH_N_RECHTS  3
#define DREH_N_LINKS   4

LinieFunktion LinieAktionCfg[] = {
  { B000000, Akt_FahrtGerade,    FAHR_N_VORNE, 100 },
  { B000001, Akt_DrehtAufStelle, FAHR_N_HINTEN, 150 },
  { B000010, Akt_Dreht,          DREH_N_LINKS, 255 },
    
  { B111111, Akt_KeineAktion, MOTOR_STOP, 0 }  
};

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Globale Variablen und Funktionsprototypen die man hier halt so braucht!
*/
/*------------------------------------------------------------------------------------------------*/
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

  Roboter.Stat_LineAktFertigFlag = true;
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
  CallBackFunk LineCallbackFunk;
  unsigned long NaechsterLoop = (millis() + LOOP_UPDATE_RATE_MS);
  
  Sensoren_Update();  
  
  Roboter.In_LineArrayWert = LiesLineArray();
  Roboter.In_Abweichung =  Abweichung(Roboter.In_LineArrayWert);

  if (Roboter.Stat_LineAktFertigFlag) {
    LineCallbackFunk = LinieAktionCfg[0].CallBackFunk;  
    Roboter.Stat_LineAktFertigFlag = LineCallbackFunk(LinieAktionCfg[0].richtung, LinieAktionCfg[0].geschw);
  } else {
    Roboter.Stat_LineAktFertigFlag = LineCallbackFunk(LinieAktionCfg[0].richtung, LinieAktionCfg[0].geschw);   
  }
  
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


bool Akt_KeineAktion(int richtung, int geschw)
{

  return true;
}

bool Akt_FahrtGerade(int richtung, int geschw)
{

  return true;
}

bool Akt_DrehtAufStelle(int richtung, int geschw)
{

  return true;
}

bool Akt_Dreht(int richtung, int geschw)
{

  return true;
}




