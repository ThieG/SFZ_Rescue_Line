/*!
****************************************************************************************************
* \file      Sensoren.ino
*
* \ingroup   RESCUE_LINE
*
*            Sensoren Modul. Hier werden folgende Sensoren initialisiert und bedient:
*             - Linefollower Array
*             - Onboard Gyro Sensor
*             - Ultraschall Abstands Sensor
*
****************************************************************************************************
*/

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Globale Variablen und Funktionsprototypen die man hier halt so braucht!
*/
/*------------------------------------------------------------------------------------------------*/
uint8_t   LineArray_Data[3u];
MePort LineArrayPort(PORT_7);
const int LineArrayPin = LineArrayPort.pin1();

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
  Sensoren.LineArray = 0xFF;
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
    Sensoren.LineArray = UpdateLineArray();
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Linefollower Array Daten      
*/
/*------------------------------------------------------------------------------------------------*/
uint8_t  LiesLineArray(void) {
  return Sensoren.LineArray;
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Me Line Follower Array
*
*            Beispiel Program, wie das Sensor Array Modul ausgelesen wird.
*            
* \return    Akteuller Wert aller 6 Sensoren als Bitfeld:
*              - 1 : Sensor sieht schwarz
*              - 0 : Sensor sieht weiß
*              
* \note      Ein Rueckgabewert von 0xFF zeigt, das ein Fehler aufgetreten ist!
*/
/*------------------------------------------------------------------------------------------------*/
static uint8_t UpdateLineArray (void)
{
    long time_out_flag = 0;
    pinMode(LineArrayPin, OUTPUT);
    digitalWrite(LineArrayPin, LOW);
    delayMicroseconds(980);
    digitalWrite(LineArrayPin, HIGH);
    delayMicroseconds(40);
    pinMode(LineArrayPin, INPUT_PULLUP);
    delayMicroseconds(50);
    time_out_flag = millis();
    while((digitalRead(LineArrayPin) == 0)&&((millis() - time_out_flag) < 6));
    time_out_flag = millis();
    while((digitalRead(LineArrayPin) == 1)&&((millis() - time_out_flag) < 6));
    for(uint8_t k=0; k<3; k++) {
        LineArray_Data[k] = 0x00;
        for(uint8_t i=0;i<8;i++) {
            time_out_flag = millis();
            while(digitalRead(LineArrayPin) == 0&&((millis() - time_out_flag) < 6));
            uint32_t HIGH_level_read_time = micros();
            time_out_flag = millis();
            while(digitalRead(LineArrayPin) == 1&&((millis() - time_out_flag) < 6));
            HIGH_level_read_time = micros() - HIGH_level_read_time;
            if(HIGH_level_read_time > 50 && HIGH_level_read_time < 100) {
                LineArray_Data[k] |= (0x80 >> i);
            }
        }
    }
    if (LineArray_Data[1] == (uint8_t)(~(uint8_t)LineArray_Data[0])) {    
         /* Index 0: Invertierte Ausgabe (schwart(0) und weiss(1) */     
         /* Index 0: Ausgabe (schwart(1) und weiss(0) */
         return ((SwapBitOrder(LineArray_Data[1]) >> 2) & 0x3F); 
    } else {
        return 0xFF;
    }
}

static uint8_t SwapBitOrder(uint8_t value) {
  uint8_t result = 0x00;

  for (uint8_t i = 0u; i < 8u; i++) {    
    if ((value & (0x01 << i)) != 0u) {
      result |= (0x80 >> i);
    }
  }
  return result;
}

