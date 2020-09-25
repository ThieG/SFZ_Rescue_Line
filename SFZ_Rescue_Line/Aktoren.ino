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
MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Globale Aktoren Daten
* 
*           Dieser werden mit \ref Aktoren_Update() aktualisiert.
*/
/*------------------------------------------------------------------------------------------------*/
typedef struct AktorenDaten {
  int16_t leftSpeed;
  int16_t rightSpeed;
  
} AktorenDaten;
AktorenDaten Aktoren;

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Aktoren Setup
*
*            Wird von der Arduino setup() Funktion aufgerufen um die angeschlossenen Aktoren
*            zu initialisiern, sofern notwendig.
*/
/*------------------------------------------------------------------------------------------------*/
void Aktoren_Setup (void)
{ 
  /* DC Antriebs Motor stoppen! */
  attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
  attachInterrupt(Encoder_2.getIntNum(), isr_process_encoder2, RISING); 

  /* Set Pwm 8KHz */
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Aktoren Update
*
*            Wird von der Arduino loop() Funktion zyklisch aufgerufen um die 
*            angeschlossenen Aktoren zu bedienen. 
*/
/*------------------------------------------------------------------------------------------------*/
void Aktoren_Update (void)
{
  Encoder_1.setTarPWM(Aktoren.leftSpeed);
  Encoder_2.setTarPWM(Aktoren.rightSpeed);

  Encoder_1.loop();
  Encoder_2.loop();
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Aktoren Motorgescheindigkeit Aendern
*/
/*------------------------------------------------------------------------------------------------*/
void Aktoren_SetSpeed(int16_t leftSpeed, int16_t rightSpeed)
{
  Aktoren.leftSpeed = leftSpeed;
  Aktoren.rightSpeed = rightSpeed;
}

void isr_process_encoder1(void)
{
  if(digitalRead(Encoder_1.getPortB()) == 0){
    Encoder_1.pulsePosMinus();
  }else{
    Encoder_1.pulsePosPlus();
  }
}

void isr_process_encoder2(void)
{
  if(digitalRead(Encoder_2.getPortB()) == 0){
    Encoder_2.pulsePosMinus();
  }else{
    Encoder_2.pulsePosPlus();
  }
}
