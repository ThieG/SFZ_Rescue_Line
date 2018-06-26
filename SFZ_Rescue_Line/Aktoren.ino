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
  int leftSpeed;
  int rightSpeed;
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
}

void SetzeMotoren(int direction, int speed)
{
  int leftSpeed = 0;
  int rightSpeed = 0;
  
  if(direction == 1){
    leftSpeed = -speed;
    rightSpeed = speed;
  }else if(direction == 2){
    leftSpeed = speed;
    rightSpeed = -speed;
  }else if(direction == 3){
    leftSpeed = -speed;
    rightSpeed = -speed;
  }else if(direction == 4){
    leftSpeed = speed;
    rightSpeed = speed;
  }

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

