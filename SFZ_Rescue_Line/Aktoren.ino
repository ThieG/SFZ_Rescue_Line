

void Aktoren_Setup (void)
{

  ServoLenkung.attach(ServoLenkungPin);
  ServoLenkung.write(SERVO_LENKUNG_MITTE);

  MotorAntrieb.stop();
}

