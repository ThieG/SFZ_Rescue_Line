

uint8_t   LineArray_Data[3];

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Sensoren Setup
*
*            Wird von der Arduino Setup() Funktion aufgerufen um die angeschlossenen Sensoren
*            zu initialisiern, sofern notwendig.
*/
/*------------------------------------------------------------------------------------------------*/
void Sensoren_Setup (void)
{
  GyroOnBoard.begin();
}



/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Me Line Follower Array
*
*            Beispiel Program, wie das Sensor Array Modul angesteuert wird.
*            
* \return               
*/
/*------------------------------------------------------------------------------------------------*/
uint8_t getLineArray()
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
     return LineArray_Data[0];
  } else {
    return 0xFF;
  }
}

