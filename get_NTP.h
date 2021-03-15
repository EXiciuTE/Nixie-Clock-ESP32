//const char* ssid1     = "TP-Link_AC1200";
//const char* ssid2     = "FRITZ!Box 7590 CB 2,4GHz";

#include "time.h"

const char* ntpServer = "europe.pool.ntp.org";
const char* Timezone_Daysafetime = "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00";
//https://remotemonitoringsystems.ca/time-zone-abbreviations.php
//https://github.com/espressif/arduino-esp32/issues/3797

struct tm timeinfo;

void grab_NTP(){
  con_to_strongest_wifi();
  
  //init and get the time
  Serial.print("Get time from: ");
  Serial.println(ntpServer);
  configTzTime(Timezone_Daysafetime,ntpServer);
  while(!getLocalTime( &timeinfo, 0 ) ){
    vTaskDelay( 10/ portTICK_PERIOD_MS);
  }
  Serial.println("Time successfully obtained.");
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

uint16_t getlocalTime(void){
  static uint16_t NTP=0;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time :(");
  }
  NTP=(timeinfo.tm_hour*100)+(timeinfo.tm_min);
  return NTP;
}
