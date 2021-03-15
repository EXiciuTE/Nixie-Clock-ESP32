void con_to_strongest_wifi(void){
    // get strongest WIFI
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("\nScan Start");

  uint8_t n=WiFi.scanNetworks();  //n: first use: number of found networks, second use: display, which ssid(n) is strongest;
  while(n==0){
    Serial.println("No Network found");
    n=WiFi.scanNetworks();  //n: first use: number of found networks, second use: display, which ssid(n) is strongest
    delay(2000);
  }
  for(i=0;i<n;i++){
    if(WiFi.SSID(i)==ssid1){
      Serial.print("Strongest Wifi is: ");
      Serial.print(ssid1);
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.println(")");
      n=1;
      i=0xf0;
    }
    else if(WiFi.SSID(i)==ssid2){
      Serial.print("Strongest Wifi is: ");
      Serial.print(ssid2);
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.println(")\n");
      n=2;
      i=0xf0; //leave for loop
    }
  }

  //connect to WiFi
  if(n==1){
    Serial.printf("Connecting to %s ", ssid1);
    WiFi.begin(ssid1, password1);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      if(WiFi.status() == WL_CONNECT_FAILED)
        WiFi.begin(ssid1, password1);
    }
    Serial.println(" CONNECTED");
  }
  if(n==2){
    Serial.printf("Connecting to %s ", ssid2);
    WiFi.begin(ssid2, password2);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      if(WiFi.status() == WL_CONNECT_FAILED)
        WiFi.begin(ssid2, password2);
    }
    Serial.println(" CONNECTED");
  }  
}
