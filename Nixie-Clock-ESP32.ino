// install WiFiManager by tzapu v2.0.17
// install "esp32" by espressive board package (v3.2.0)
// USE "ESP32 DEV MODUL" Board

#include <WiFiManager.h>
#include <EEPROM.h>

// WiFi credential handling ##################
WiFiManager wm;
char ssid[32];
char pass[32];
bool shouldSaveConfig = false;
WiFiServer server(80);

// Time related variables ####################
uint16_t localTime=0;
static uint16_t on1,out1,on2,out2=0;
static uint16_t old_on1,old_out1,old_on2,old_out2=0;

// GPIO related variables #####################
int wifi_config_button = 0;
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

// Miscellaneous variables
uint8_t clock_active=0x1; //b0=0: deactivated (on by default);  b1=1: on, glowing, b1=0: wrong time
uint8_t i=0;

//own headers
#include "Pins_ctrl.h"  //pin_setup(); - show_num(int tube, int number) 0=h10;1=h01;2=m10;3=m01
#include "eeprom_timemem.h"
#include "NTP.h"
#include "ESP32Server_setTime.h"

  //#########################################################################
  // Functions

// Callback to save config after web server updated SSID and password
void saveConfigCallback(){
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

// Function to write new Credentials to EEPROM
void saveCredentials(const char* newSSID, const char* newPASS){
  // save SSID
  for(int i=0;i<32;i++){
    EEPROM.write(0+i,newSSID[i]);
  }
  for(int i=0;i<32;i++){
    EEPROM.write(1000+i,newPASS[i]);
  }
  EEPROM.commit();
}

// Function to load Credentials from EEPROM
void readCredentials(){
  Serial.println("Reading WiFi credentials from EEPROM...");
  for (int i=0; i<32; i++){
    ssid[i] = EEPROM.read(0+i);
  }
  ssid[31]='\0';
  
  for (int i=0; i<32; i++){
    pass[i] = EEPROM.read(100+i);
  }
  pass[31]='\0';

  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("PASS: ");
  Serial.println(pass);

}

void set_nixie(uint16_t val){
  // Function to update outputs (Nixie Tubes)
  //void show_num(int tube, int number);  //1=m01;2=m10;3=h01;4=h10
  show_num(4,val%10);
  show_num(3,(val%100)/10);
  show_num(2,(val%1000)/100);
  show_num(1,(val/1000));
}

  //#########################################################################
  // Setup
void setup() {
  Serial.begin(115200);
  eeprom_setup();
  // EEPROM.begin(512);
  pin_setup();
  
  pinMode(wifi_config_button,INPUT_PULLUP);
  //pinmodes

  wm.setSaveConfigCallback(saveConfigCallback);

  // wait for 3 seconds, since used button is the BOOT button! --> first restart/apply power, then press the button
  Serial.println("press \\BOOT\\ button to enter new credentials");
  delay(3000);

  //if button pressed, new credentials can be applied
  if(digitalRead(wifi_config_button) == LOW){
    Serial.println("Button pressed, starting WiFiManager...");
    //wm.resetSettings(); // Reset to enable setup mode
    wm.startConfigPortal("ESP32_Config");
    delay(100);
    
    //Save config to EEPROM if needed
    if (shouldSaveConfig){
      saveCredentials(wm.getWiFiSSID().c_str(), wm.getWiFiPass().c_str());
      Serial.println("Credentials saved.");
      ESP.restart();  // Restart to apply settings
    } else {
      Serial.println("no new Credentials saved.");
      ESP.restart();  // Restart to apply settings
    }
  }
  else {
    //Load credentials from EEPROM
    readCredentials();
    Serial.print(wm.autoConnect(ssid,pass));
    grab_NTP();
    localTime=getlocalTime();
    server.begin();
  }
  Serial.println("Setup complete!");
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
