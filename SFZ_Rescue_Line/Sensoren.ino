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
* \note      Bei der original MeUltrasonicSensor.cpp wird der timeout (ABSTAND_MAX_CM) nicht
*            mehr verwendet und ist somit unwirksam. Wer das haben möchte muss eben die alte 
*            Version nehmen!
*
****************************************************************************************************
*/

#include "MeRGBLineFollower.h"

#define ABSTAND_MAX_CM  100

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Globale Variablen und Funktionsprototypen die man hier halt so braucht!
*/
/*------------------------------------------------------------------------------------------------*/
MeRGBLineFollower RGBLineFollower(PORT_7, ADDRESS2);
MeUltrasonicSensor AbstandsSensor(PORT_8);

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Globale Sensoren Daten
* 
*           Dieser werden mit \ref Sensoren_Update() aktualisiert.
*/
/*------------------------------------------------------------------------------------------------*/
typedef struct SensorDaten {
  uint8_t  LineArray;
  uint16_t AbstandCm;
  long     AbstandUpdateTime;
  
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
  Serial.println(F("INFO: RGB Linefollower started..."));
  RGBLineFollower.begin();
  RGBLineFollower.updataAllSensorValue();

  /* Set dafault Werte */
  RGBLineFollower.setRGBColour(RGB_COLOUR_GREEN);
  RGBLineFollower.setKp(0.3);

  /* Initale Messung */
  Serial.println(F("INFO: Ultraschall Sensor..."));
  Sensoren.AbstandCm = AbstandsSensor.distanceCm(ABSTAND_MAX_CM);
  long MessDauer = AbstandsSensor.measure();
  Serial.print("INFO: Bei einem Abstand von ");
  Serial.print(Sensoren.AbstandCm);
  Serial.print("cm ");
  Serial.print("dauert die Mssung ca. ");
  Serial.print(MessDauer);
  Serial.println("us");
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Linefollower Messfarbe Aendern     
* 
* \param     neueFarbe RGB_COLOUR_RED(1), RGB_COLOUR_GREEN(2), RGB_COLOUR_BLUE(3)          
*/
/*------------------------------------------------------------------------------------------------*/
void Sensoren_LineAendereFarbe(uint8_t neueFarbe)
{
    RGBLineFollower.setRGBColour(neueFarbe);
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Linefollower Empfindlichkeit Aendern     
*/
/*------------------------------------------------------------------------------------------------*/
void Sensoren_LineAendereEmpfindlichkeit(float empfindlichkeit)
{
    RGBLineFollower.setKp(empfindlichkeit);  
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
uint8_t Sensoren_LineADCWert(int8_t sensorNum)
{
    uint8_t adcResult = 0u;
    
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
* \brief     Abstandswerte in cm    
*/
/*------------------------------------------------------------------------------------------------*/
uint16_t Sensoren_AbstandCm(void)
{
  return Sensoren.AbstandCm;
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
    
    if((millis() - Sensoren.AbstandUpdateTime) > 10) {
        Sensoren.AbstandUpdateTime = millis();
        Sensoren.AbstandCm = AbstandsSensor.distanceCm(ABSTAND_MAX_CM);
    }
}
