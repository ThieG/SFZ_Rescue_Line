/*!
****************************************************************************************************
* \file      Aktoren.ino
*
* \ingroup   RESCUE_LINE
*
*            Aktoren Modul. Hier werden folgende Aktoren initialisiert und bedient:
*             - Antriebs Motor
*             - Lenkungs Servo
*
****************************************************************************************************
*/

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Globale Variablen und Funktionsprototypen die man hier halt so braucht!
*/
/*------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Aktoren Setup
*
*            Wird von der Arduino setup() Funktion aufgerufen um die angeschlossenen Aktoren
*            zu initialisiern, sofern notwendig.
*            
* \param    *roboter Referenz zu den Roboter Betriebsdaten. 
*/
/*------------------------------------------------------------------------------------------------*/
void Aktoren_Setup (RoboterBetriebsDaten* roboter)
{

  /* Servo fuer die Lenkung mit dem entsprechenden Pin verbinden und in Mittelstellung ansteuern... */
  ServoLenkung.attach(ServoLenkungPin);
  ServoLenkung.write(SERVO_LENKUNG_MITTE);
  roboter->Out_ServoLenkungPosition = SERVO_LENKUNG_MITTE;
  
  /* DC Antriebs Motor stoppen! */
  MotorAntrieb.stop();
  roboter->Out_MotorAntriebGeschwindigkeit = 0u;
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Aktoren Update
*
*            Wird von der Arduino loop() Funktion zyklisch aufgerufen um die 
*            angeschlossenen Aktoren zu bedienen.
*            
* \param    *roboter Referenz zu den Roboter Betriebsdaten. 
*/
/*------------------------------------------------------------------------------------------------*/
void Aktoren_Update (RoboterBetriebsDaten* roboter)
{

}

