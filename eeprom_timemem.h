#include "EEPROM.h"

//Adressen:
// on1  0x0000
// out1 0x0000+sizeof(unsigned short) (short=16bit)
// on2  ...
// out2 ...

int address=0;

void eeprom_write(void){
  address=0;
  EEPROM.writeUShort(address, on1);
  address+=sizeof(unsigned short);
  EEPROM.writeUShort(address, out1);
  address+=sizeof(unsigned short);
  EEPROM.writeUShort(address, on2);
  address+=sizeof(unsigned short);
  EEPROM.writeUShort(address, out2);
  address=0;
  EEPROM.commit();
  Serial.println("Neue Zeiten wurden abgespeichert");
  old_on1=on1;
  old_out1=out1;
  old_on2=on2;
  old_out2=out2;
}

void eeprom_read(void){
  address=0;
  on1=EEPROM.readUShort(address);
  address+=sizeof(unsigned short);
  out1=EEPROM.readUShort(address);
  address+=sizeof(unsigned short);
  on2=EEPROM.readUShort(address);
  address+=sizeof(unsigned short);
  out2=EEPROM.readUShort(address);
  address=0;
}

void eeprom_setup(){
  if (!EEPROM.begin(1000)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }
  eeprom_read();
  old_on1=on1;
  old_out1=out1;
  old_on2=on2;
  old_out2=out2;
}
