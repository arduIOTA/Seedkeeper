#ifndef __ArduIOTA_SEED__
#define __ArduIOTA_SEED__

#include "Arduino.h"
#include "AESLib.h"

class ArduIOTA_Seed {
private:
 byte adrSeedStart;
 byte adrSeedStop;
 byte seedLength;  
 bool showMenu;
 bool loopStart;
 bool setSeedGestartet;
 uint8_t *key;
 
 String GibSeed();

public:
 ArduIOTA_Seed(byte adresseSeedStart, byte adresseSeedStop, byte seedLength, uint8_t *key);
    
 void GetSeed();
 int SetSeed();
 
 String ReturnSeed();
 String EncryptSeed(String s[]);
 String DecryptSeed(String s[]);
};

#endif
