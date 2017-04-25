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
* \brief     Anzeige Setup
*
*            Wird von der Arduino setup() Funktion aufgerufen um die angeschlossenen Anzeigen
*            zu initialisiern, sofern notwendig.
*/
/*------------------------------------------------------------------------------------------------*/
void Anzeige_Setup(void)
{
  RGBLedOnBoard.setColor(0, 150, 150, 150); /* 0 -> Alle RGBs anschalten, ansonsten 1 bis 12.... */
  RGBLedOnBoard.show();
  
}

