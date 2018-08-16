#ifndef __ArduIOTA_PIN__
#define __ArduIOTA_PIN__

#include "Arduino.h"

class ArduIOTA_Pin {
private:

 byte adressePinStart;
 byte adressePinStop;
 byte pinLength;
 byte adresseFactoryDefault;
 uint8_t *key;

public:
  bool isAuth;
  bool setupStart;

  ArduIOTA_Pin(byte adressePinStart, byte adressePinStop, byte pinLength, byte adresseFactoryDefault);
  String GetPin();
  int SetPin();
  bool VerifyPin();
};

#endif
