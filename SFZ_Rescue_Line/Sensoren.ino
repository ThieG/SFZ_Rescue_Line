/*!
****************************************************************************************************
* \file      Sensoren.ino
*
* \ingroup   RESCUE_LINE
*
*            Sensoren Modul. Hier werden folgende Sensoren initialisiert und bedient:
*             - Me RGB Line Follower (http://learn.makeblock.com/en/rgb-line-follower/)
*             - Me Color Sensor (http://learn.makeblock.com/en/me-color-sensor-v1/)
*             - Onboard Gyro Sensor
*             - Ultraschall Abstands Sensor (http://learn.makeblock.com/en/me-ultrasonic-sensor/)
*
****************************************************************************************************
*/

#include "MeRGBLineFollower.h"

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Globale Variablen und Funktionsprototypen die man hier halt so braucht!
*/
/*------------------------------------------------------------------------------------------------*/
MeRGBLineFollower RGBLineFollower(PORT_9, ADDRESS2);

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Globale Sensoren Daten
* 
*           Dieser werden mit \ref Sensoren_Update() aktualisiert.
*/
/*------------------------------------------------------------------------------------------------*/
typedef struct SensorDaten {
  uint8_t LineArray;

} SensorDaten;
SensorDaten Sensoren;

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Sensoren Setup
*
*            Wird von der Arduino setup() Funktion aufgerufen um die angeschlossenen Sensoren
*            zu initialisiern, sofern notwendig.
*/
/*------------------------------------------------------------------------------------------------*/
void Sensoren_Setup (void)
{
  RGBLineFollower.begin();
  RGBLineFollower.updataAllSensorValue();
  RGBLineFollower.setRGBColour(RGB_COLOUR_RED);
  RGBLineFollower.setKp(0.3);
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Linefollower Abweichung von der schwarzen Linie     
*/
/*------------------------------------------------------------------------------------------------*/
int16_t Sensoren_LineAbweichung(void)
{
    return RGBLineFollower.getPositionOffset();
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Linefollower Aktuelle Schwarz/Weiß Zustand
* 
*             |---------------------------|     
*             |RGB1  |RGB2  |RGB3  |RGB4  |
*             |---------------------------| 
*/
/*------------------------------------------------------------------------------------------------*/
uint8_t Sensoren_LineAktuellerZustand(void)
{
    return RGBLineFollower.getPositionState();
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Linefollower Sensor ADC Werte     
*/
/*------------------------------------------------------------------------------------------------*/
int8_t Sensoren_LineAbweichung(int8_t sensorNum)
{
    int8_t adcResult = 0u;
    
    switch (sensorNum) {
        case 1:
            adcResult = RGBLineFollower.getADCValueRGB1();
            break;
        case 2:
            adcResult = RGBLineFollower.getADCValueRGB2();
            break;
        case 3:
            adcResult = RGBLineFollower.getADCValueRGB3();
            break;
        case 4:
            adcResult = RGBLineFollower.getADCValueRGB4();
            break;
    }

    return adcResult;
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Sensoren Update
*
*            Wird von der Arduino loop() Funktion zyklisch aufgerufen um die angeschlossenen Sensoren
*            ein zu lesen und die Daten bereit zu stellen.       
*/
/*------------------------------------------------------------------------------------------------*/
void Sensoren_Update (void)
{
    RGBLineFollower.loop();
}
