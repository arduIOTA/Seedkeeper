#include "Arduino.h"
#include "EEPROM.h"
#include "ArduIOTA_FactoryDefault.h"
#include "ArduIOTA_Pin.h"

ArduIOTA_Pin::ArduIOTA_Pin(byte aPinStart, byte aPinStop, byte pinLength, byte aFD)  {
 this->adressePinStart = aPinStart;
 this->adressePinStop = aPinStop;
 this->pinLength = pinLength;
 this->adresseFactoryDefault = aFD;
}

String ArduIOTA_Pin::GetPin() // get pin from eeprom
{
  String r = "";
  for (byte i = this->adressePinStart; i <= this->adressePinStop ; i++) 
  {
    char c = EEPROM.read(i);  
    r += c;
  }

  return r;
}

int ArduIOTA_Pin::SetPin() // Set pin to eeprom
{
  byte buf[this->pinLength]; 

  Serial.print("Please Enter ");
  Serial.println(String(this->pinLength) + " digit for PIN");

  Serial.setTimeout(60000L);
  Serial.readBytesUntil('#', (char *) buf, this->pinLength);
  String pinEingabe = String((char*) buf);
  int pinEingabeLength = (String((char*) buf)).length();

  if((String((char*) buf)) == "")
  {
    Serial.println("Please enter PIN");
    return -1;
  }
  else if((String((char*) buf)).length() != this->pinLength)
  {
     Serial.println("PIN must digit");
     return -1;
  }
  else if((String((char*) buf)).length() == this->pinLength)
  {
    for (byte i = 0; i < this->pinLength ; i++) 
    {
      EEPROM.write(i + this->adressePinStart, buf[i]);
    }  
    return 0;
  }
}

bool ArduIOTA_Pin::VerifyPin() //verifiy the pin
{
  byte buf[this->pinLength];

  for (byte i = 0; i < this->pinLength ; i++) 
  {
    buf[i] = 0;
  }
  
  if(!this->setupStart)
  {
    Serial.println("Enter PIN");
  }

  Serial.setTimeout(5000L);
  Serial.readBytesUntil('#', (char *) buf, this->pinLength);
  String pinEingabe = (String((char*)buf)).substring(0, this->pinLength);

  if(this->GetPin() == pinEingabe)
  {
    isAuth = true;
  }
  else
  {
    isAuth = false;
  }
  
  return isAuth;
}
