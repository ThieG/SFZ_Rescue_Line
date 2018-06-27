

typedef struct LinieFunktion {
  uint8_t LinieWert;
  bool (*CallBackFunk) (int, int);
  int richtung;
  int geschw;
} LinieFunktion;


typedef struct RoboterBetriebsDaten {
  bool Stat_LineAktFertigFlag;

  int16_t Out_MotorAntriebGeschwindigkeit;
  int16_t Out_ServoLenkungPosition;
  
  int8_t  In_LineArrayWert;
  int32_t In_Abweichung;
  
} RoboterBetriebsDaten;


typedef bool (*CallBackFunk) (int, int);

bool Akt_KeineAktion(int richtung, int geschw);
bool Akt_FahrtGerade(int richtung, int geschw);
bool Akt_DrehtAufStelle(int richtung, int geschw);
bool Akt_Dreht(int richtung, int geschw);
