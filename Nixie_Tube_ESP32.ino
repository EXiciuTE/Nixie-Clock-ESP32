// USE "ESP32 DEV MODUL" Board
// Connect: "http://nixie-clock" (192.168.178.29)

//Define Wifi related

const char* ssid1     = "TP-Link_AC1200";
const char* password1 = "welchespasswort?";
const char* ssid2     = "FRITZ!Box 7590 CB 2,4GHz";
const char* password2 = "97882521488135805688";

// Define Clock related
//Naming differs from Hardware!!! HW:x4x-->SW:x1x
                                //HW:x3x-->SW:x2x
                                //HW:x2x-->SW:x3x
                                //HW:x1x-->SW:x4x
#define h10 33
#define h20 32
#define h30 5 //original: 35  (connected on Tube PCB, not ESP PCB)
#define h40 4 //original: 34  (connected on Tube PCB, not ESP PCB)
#define h01 14
#define h02 27
#define h03 26
#define h04 25
#define m10 19
#define m20 21
#define m30 22
#define m40 23
#define m01 15
#define m02 16
#define m03 17
#define m04 18
#define SHDN 12

  //#########################################################################
  // Defines
uint8_t i=0;
uint8_t clock_active=0x1; //b0=0: deactivated (on by default);  b1=1: on, glowing, b1=0: wrong time
static uint16_t on1,out1,on2,out2=0;
static uint16_t old_on1,old_out1,old_on2,old_out2=0;
uint16_t localTime=0;

  //#########################################################################
  // Includes
#include "Pins_ctrl.h"  //pin_setup(); - show_num(int tube, int number) 0=h10;1=h01;2=m10;3=m01
#include <WiFi.h>
#include "eeprom_timemem.h"

WiFiServer server(80);
#include "scan_wifi.h"
#include "get_NTP.h"
#include "ESP32Server_setTime.h"




  //#########################################################################
  // Dummy Routines
void set_nixie(uint16_t val);

  //#########################################################################
  // Setup
void setup() {
  Serial.begin(115200);
  delay(10);
  pin_setup();
  eeprom_setup(); //führt eeprom_read(); aus
  delay(10);
  grab_NTP();     //starts wifi, gets NTP, disconnects wifi
  delay(10);
  server_setup(); //starts wifi again but different xD
}

  
  //#########################################################################
  // Loop
void loop() {
  static uint16_t old_hour,old_min=0;
  
  //#########################################################################
  //Start WIFI Code

  //reconnect nessacary?
  connection_check();
  
  server_loop();  //-->on1,out1,on2,out2
  localTime=getlocalTime();
  //Serial.print("Local Time: "); Serial.println(localTime);

  //#########################################################################
  // An/Auszeiten mit Uhrzeit abgleichen
  //clock_active b0=0: shutdown;  b1=1: on, glowing, b1=0: wrong time
  if(clock_active&0x01){
    if( ((localTime>=old_on1&&localTime<=old_out1) || ((localTime>=old_on2&&localTime<=old_out2))) ){ //Anzeige an!
      clock_active|=0x02;
      digitalWrite(SHDN,HIGH);
    }
    else{   //Anzeige aus
      clock_active=0x01;
      digitalWrite(SHDN,LOW);
    }
  }

  //#########################################################################
  //anti catode poisoning
  if(old_hour!=localTime/100){
    old_hour=localTime/100;
    old_min=(localTime%100)/10;
    
    for(i=0;i<40;i++){
      set_nixie(random(9999));
      delay(25);
    }
    for(i=0;i<30;i++){
      set_nixie((random(999)*10)+(localTime%10));
      delay(33);
    }
    for(i=0;i<24;i++){
      set_nixie((random(99)*100)+(localTime%100));
      delay(42);
    }
    for(i=0;i<20;i++){
      set_nixie((random(9)*1000)+(localTime%1000));
      delay(50);
    }
  }
  else{
    if(old_min!=(localTime%100)/10){
      old_min=(localTime%100)/10;
      for(i=0;i<10;i++){
        set_nixie((localTime+(1000+i)%10000/1000)*1000 + (localTime+(100*i)%1000/100)*100 +(localTime+(10*i)%100/10)*10 + ((localTime+i)%10));
        delay(100);
      }
    }
  }

  //#########################################################################
  //normal Output
  set_nixie(localTime);
}

void set_nixie(uint16_t val){
  //void show_num(int tube, int number);  //1=m01;2=m10;3=h01;4=h10
  show_num(4,val%10);
  show_num(3,(val%100)/10);
  show_num(2,(val%1000)/100);
  show_num(1,(val/1000));
}
