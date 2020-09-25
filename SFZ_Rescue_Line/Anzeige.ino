/*!
****************************************************************************************************
* \file      Anzeige.ino
*
* \ingroup   RESCUE_LINE
*
*            Anzeigen Modul. Hier werden folgende Anzeigen initialisiert und bedient:
*             - RGB Ring
*
****************************************************************************************************
*/

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Globale Variablen und Funktionsprototypen die man hier halt so braucht!
*/
/*------------------------------------------------------------------------------------------------*/
MeRGBLed RGBLedOnBoard(0, 12);

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Anzeige Setup
*
*            Wird von der Arduino setup() Funktion aufgerufen um die angeschlossenen Anzeigen
*            zu initialisiern, sofern notwendig.
*/
/*------------------------------------------------------------------------------------------------*/
void Anzeige_Setup(void)
{
  
  RGBLedOnBoard.setpin(44);
  RGBLedOnBoard.setColor(0, 0, 0, 0); /* 0 -> Alle RGBs ausschalten, ansonsten 1 bis 12.... */
  RGBLedOnBoard.show();
  
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Anzeige Update
*
*            Wird von der Arduino loop() Funktion zyklisch aufgerufen um die Anzeige neu zu machen.      
*/
/*------------------------------------------------------------------------------------------------*/
void Anzeige_Update (void)
{
  RGBLedOnBoard.show();   
}
