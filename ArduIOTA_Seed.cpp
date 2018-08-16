#include "Arduino.h"
#include "EEPROM.h"
#include "ArduIOTA_Seed.h"
#include "ArduIOTA_Menu.h"
#include "AESLib.h"

#define constantSeedSuffix "*******"
#define arrayLength 9
#define IOTASeedLength 81 

ArduIOTA_Seed::ArduIOTA_Seed (byte aSeedStart, byte aSeedStop, byte seedLength, uint8_t *key)  {
  this->adrSeedStart = aSeedStart;
  this->adrSeedStop = aSeedStop;
  this->seedLength = seedLength;
  this->key = key;
}

String ArduIOTA_Seed::GibSeed()
{
  String r;
  for (byte i = this->adrSeedStart; i <= this->adrSeedStop ; i++) 
  {
    char c = EEPROM.read(i);  
    r += c;
  }

  return r;
}

String ArduIOTA_Seed::EncryptSeed(String s[])
{
  String r = "";

  for (int i = 0; i < arrayLength; i++)
  {  
    s[i].concat(constantSeedSuffix);
    Serial.print(i);  Serial.println(":vorher> " + s[i]); 
    aes256_enc_single(key, s[i].c_str());
    Serial.println("nachher > " + s[i]);
    r += s[i].c_str();   
  }
  
  return r;
}

String ArduIOTA_Seed::DecryptSeed(String s[])
{
  String r = "";  
  String v = "";
    
  for (int i = 0; i < arrayLength; i++)
  {
    v += s[i];
    Serial.print(i);  Serial.println(":vorher> " + s[i]);
    aes256_dec_single(key, s[i].c_str());
    String st = s[i].c_str();
    Serial.println("nachher > " + st);  
    r += st.substring(0,arrayLength);
  }

  return r.substring(0, arrayLength * arrayLength);
}

void ArduIOTA_Seed::GetSeed()
{
  String decSed[] = {
    GibSeed().substring(0  , 16), 
    GibSeed().substring(16 , 32),
    GibSeed().substring(32 , 48), 
    GibSeed().substring(48 , 64), 
    GibSeed().substring(64 , 80), 
    GibSeed().substring(80 , 96), 
    GibSeed().substring(96 , 112), 
    GibSeed().substring(112, 128), 
    GibSeed().substring(128, 144)
    };

  for (int i = 0; i < arrayLength; i++)
  {
    Serial.print(i);  Serial.println(":vorher> " + decSed[i]);
  }

  Serial.println();
  Serial.println("> " + DecryptSeed(decSed));
  
  return;
}

int ArduIOTA_Seed::SetSeed()
{
  byte buf[this->seedLength] = {};
  char arr[this->seedLength] = {};

  Serial.setTimeout(60000);
  
  if(!this->setSeedGestartet)
  {
    Serial.println();
    Serial.println("Enter your Seed (Seed must end with # | Cancel = X#)");
    setSeedGestartet = true;
  }

  Serial.readBytesUntil('#', (char *) buf, this->seedLength);
  String choise = (String((char*)buf)).substring(0,this->seedLength);
  int choiseLength = choise.length();
  
  if(choise == "X")
  {
    this->setSeedGestartet = false;
    return 0;
  }
  else if(choiseLength > IOTASeedLength)
  {
    Serial.print("Seed longer then ");
    Serial.println(IOTASeedLength);
    this->setSeedGestartet = false;
    return -1;
  }
  else if(choiseLength < IOTASeedLength)
  {
    Serial.print("Seed shorter then ");
    Serial.println(IOTASeedLength);
    this->setSeedGestartet = false;
    return -1;
  }

  String s[] = {
    (String((char*)buf)).substring(0, arrayLength),
    (String((char*)buf)).substring(arrayLength * 1, arrayLength * 2),
    (String((char*)buf)).substring(arrayLength * 2, arrayLength * 3),
    (String((char*)buf)).substring(arrayLength * 3, arrayLength * 4),
    (String((char*)buf)).substring(arrayLength * 4, arrayLength * 5),
    (String((char*)buf)).substring(arrayLength * 5, arrayLength * 6),
    (String((char*)buf)).substring(arrayLength * 6, arrayLength * 7),
    (String((char*)buf)).substring(arrayLength * 7, arrayLength * 8),
    (String((char*)buf)).substring(arrayLength * 8, arrayLength * 9)               
    };

  strcpy (arr, EncryptSeed(s).c_str());
  
  for (byte i = 0; i < this->seedLength ; i++) 
  {
    EEPROM.write(i + this->adrSeedStart, arr[i]);
  }  

  Serial.println("Seed saved successful");
  
  this->setSeedGestartet = false; 

  return 0;
}

