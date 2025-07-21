/* Umlaute für HTML:
 * Ä: client.print("&Auml");
 * ü: client.print("&uuml");
 * Also: & + Buchstabe + uml
 * 
 * ß: client.print("&szlig");
 */
static uint16_t counter=0;
static uint16_t get_time_cnt=0;

uint16_t onoff_time_convertion(uint16_t val, int16_t diff);

void connection_check(){
  if(counter==0xffff){
    //reconnect
    
    get_time_cnt++;
    // Serial.println("Connection check");
    // if(WiFi.status() != WL_CONNECTED){
    //   Serial.println("Disconnected :O");
    //   Serial.println("try to reconnect");
    //   WiFi.mode(WIFI_STA);
    //   WiFi.disconnect();
    //   delay(100);
    //   uint8_t n=WiFi.scanNetworks();  //n: first use: number of found networks, second use: display, which ssid(n) is strongest;
    //   for(i=0;i<n;i++){
    //     if(WiFi.SSID(i)==ssid1){
    //       n=1;
    //       i=0xf0;
    //     }
    //     else if(WiFi.SSID(i)==ssid2){
    //       n=2;
    //       i=0xf0; //leave for loop
    //     }
    //   }
    // }

    if(get_time_cnt==0xffff){
      Serial.println("get time");
      //deactivate Wifi first, cause it is reactivated in sub routine
      // WiFi.disconnect(true);
      // WiFi.mode(WIFI_OFF);
      // delay(500);
      grab_NTP();
      // server_setup();
    }
  }
  counter++;
}

void server_loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();


            // the content of the HTTP response follows the header:
            client.print("<br>");
            client.print("<br><br><h3>Nixie Clock ESP32 v1.1 --- Einstellungen</h3><br>");
            client.print("Bitte die Zeitbereiche, in denen die Uhr akiv sein soll, mit den Kn&oumlpfen einstellen.<br>");
            client.print("Die Uhrzeit ist in einem g&uumlltigen Format einzustellen<br>");
            client.print("Zum Beispiel: '1425' (14:25 Uhr), '0205' (02:05 Uhr)<br>");
            client.print("Um einen Zeitbereich nicht zu nutzen, bitte zweimal die identische Zeit eintragen.<br>");
            client.print("Au&szligerhalb der eingestellten Zeiten ist die Uhr ausgeschaltet.<br><br>");
            client.print("Aktuelle Zeit: ");
            client.println(localTime);

            client.print("<h4>Uhrzeit 1 an:&emsp;"); client.print(on1); client.print("&emsp;&emsp;&emsp;Uhrzeit 1 aus:&emsp;"); client.print(out1); client.print("</h4>");
            client.print("<br>");
            
            client.print("<a href=\"/on1/add0500\"> <button type='button' name='on1+5h'  formtarget='_self'>+5 hour</button></a> &ensp; <a href=\"/on1/sub0500\"> <button type='button' name='on1-5h' formtarget='_self'>-5 hour</button></a>&emsp;&emsp;");
            client.print("<a href=\"/out1/add0500\"><button type='button' name='out1+5h' formtarget='_self'>+5 hour</button></a> &ensp; <a href=\"/out1/sub0500\"> <button type='button' name='out1-5h' formtarget='_self'>-5 hour</button></a><br>");
            
            client.print("<a href=\"/on1/add0100\"> <button type='button' name='on1+1h'  formtarget='_self'>+1 hour</button></a> &ensp; <a href=\"/on1/sub0100\"> <button type='button' name='on1-1h' formtarget='_self'>-1 hour</button></a>&emsp;&emsp;");
            client.print("<a href=\"/out1/add0100\"><button type='button' name='out1+1h' formtarget='_self'>+1 hour</button></a> &ensp; <a href=\"/out1/sub0100\"> <button type='button' name='out1-1h' formtarget='_self'>-1 hour</button></a><br>");
            
            client.print("<a href=\"/on1/add0015\"> <button type='button' name='on1+15m' formtarget='_self'>+15 min</button></a> &nbsp; <a href=\"/on1/sub0015\"> <button type='button' name='on1-15m' formtarget='_self'>-15 min</button></a>&emsp;&emsp;");
            client.print("<a href=\"/out1/add0015\"><button type='button' name='out1+15m' formtarget='_self'>+15 min</button></a> &nbsp; <a href=\"/out1/sub0015\"> <button type='button' name='out1-15m' formtarget='_self'>-15 min</button></a><br>");
            
            client.print("<a href=\"/on1/add0005\"> <button type='button' name='on1+5m'  formtarget='_self'>+5 min</button></a> &emsp;&nbsp; <a href=\"/on1/sub0005\"><button type='button' name='on1-5m' formtarget='_self'>-5 min</button></a>&emsp;&emsp;");
            client.print("<a href=\"/out1/add0005\"><button type='button' name='out1+5m' formtarget='_self'>+5 min</button></a> &emsp;&nbsp; <a href=\"/out1/sub0005\"> <button type='button' name='out1-5m' formtarget='_self'>-5 min</button></a><br>");
            
            client.print("<a href=\"/on1/add0001\"> <button type='button' name='on1+1m'  formtarget='_self'>+1 min</button></a> &emsp;&nbsp; <a href=\"/on1/sub0001\"> <button type='button' name='on1-1m' formtarget='_self'>-1 min</button></a>&emsp;&emsp;");
            client.print("<a href=\"/out1/add0001\"><button type='button' name='out1+1m' formtarget='_self'>+1 min</button></a>  &emsp;&nbsp; <a href=\"/out1/sub0001\"> <button type='button' name='out1-1m' formtarget='_self'>-1 min</button></a><br>");
            
            client.print("<br>");
            client.print("<br>");

            client.print("<h4>Uhrzeit 2 an:&emsp;"); client.print(on2); client.print("&emsp;&emsp;&emsp;Uhrzeit 2 aus:&emsp;"); client.print(out2); client.print("</h4>");
            client.print("<br>");


            client.print("<a href=\"/on2/add0500\"> <button type='button' name='on2+5h'  formtarget='_self'>+5 hour</button></a> &ensp; <a href=\"/on2/sub0500\"> <button type='button' name='on2-5h' formtarget='_self'>-5 hour</button></a>&emsp;&emsp;");
            client.print("<a href=\"/out2/add0500\"><button type='button' name='out2+5h' formtarget='_self'>+5 hour</button></a> &ensp; <a href=\"/out2/sub0500\"> <button type='button' name='out2-5h' formtarget='_self'>-5 hour</button></a><br>");
            
            client.print("<a href=\"/on2/add0100\"> <button type='button' name='on2+1h'  formtarget='_self'>+1 hour</button></a> &ensp; <a href=\"/on2/sub0100\"> <button type='button' name='on2-1h' formtarget='_self'>-1 hour</button></a>&emsp;&emsp;");
            client.print("<a href=\"/out2/add0100\"><button type='button' name='out2+1h' formtarget='_self'>+1 hour</button></a> &ensp; <a href=\"/out2/sub0100\"> <button type='button' name='out2-1h' formtarget='_self'>-1 hour</button></a><br>");
            
            client.print("<a href=\"/on2/add0015\"> <button type='button' name='on2+15m' formtarget='_self'>+15 min</button></a> &nbsp; <a href=\"/on2/sub0015\"> <button type='button' name='on2-15m' formtarget='_self'>-15 min</button></a>&emsp;&emsp;");
            client.print("<a href=\"/out2/add0015\"><button type='button' name='out2+15m' formtarget='_self'>+15 min</button></a> &nbsp; <a href=\"/out2/sub0015\"> <button type='button' name='out2-15m' formtarget='_self'>-15 min</button></a><br>");
            
            client.print("<a href=\"/on2/add0005\"> <button type='button' name='on2+5m'  formtarget='_self'>+5 min</button></a> &emsp;&nbsp; <a href=\"/on2/sub0005\"><button type='button' name='on2-5m' formtarget='_self'>-5 min</button></a>&emsp;&emsp;");
            client.print("<a href=\"/out2/add0005\"><button type='button' name='out2+5m' formtarget='_self'>+5 min</button></a> &emsp;&nbsp; <a href=\"/out2/sub0005\"> <button type='button' name='out2-5m' formtarget='_self'>-5 min</button></a><br>");
            
            client.print("<a href=\"/on2/add0001\"> <button type='button' name='on2+1m'  formtarget='_self'>+1 min</button></a> &emsp;&nbsp; <a href=\"/on2/sub0001\"> <button type='button' name='on2-1m' formtarget='_self'>-1 min</button></a>&emsp;&emsp;");
            client.print("<a href=\"/out2/add0001\"><button type='button' name='out2+1m' formtarget='_self'>+1 min</button></a>  &emsp;&nbsp; <a href=\"/out2/sub0001\"> <button type='button' name='out2-1m' formtarget='_self'>-1 min</button></a><br>");

            client.print("<br>");
            client.print("<br>");
            client.print("<a href=\"/2/status2\"><button type='button' name='STATUS' value='2' formtarget='_self'>&Uumlbernehmen</button></a><br>");
            
            client.print("<br>");
            
            client.print("<h4>Master-Schalter ");
            if(clock_active&0x1)
              client.println("an.</h4>");
            else
              client.println("aus.</h4>");
            client.println("<h4>(Overwrites Zeitbereich)</h4>");
            
            client.print("<a href=\"/2/status1\"><button type='button' name='STATUS' value='1' formtarget='_self'>Anschalten</button></a>&emsp;&emsp;");
            client.print("<a href=\"/2/status0\"><button type='button' name='STATUS' value='0' formtarget='_self'>Ausschalten</button></a>&emsp;&emsp;");
            client.print("<a href=\"/2/status3\"><button type='button' name='STATUS' value='0' formtarget='_self'>Aktuallisieren</button></a>");
            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        //Response Handler  #############################################################

        if(currentLine.endsWith("GET /on1/add0001")) on1=onoff_time_convertion(on1,1);      if(currentLine.endsWith("GET /on1/sub0001")) on1=onoff_time_convertion(on1,-1);
        if(currentLine.endsWith("GET /on1/add0005")) on1=onoff_time_convertion(on1,5);      if(currentLine.endsWith("GET /on1/sub0005")) on1=onoff_time_convertion(on1,-5);
        if(currentLine.endsWith("GET /on1/add0015")) on1=onoff_time_convertion(on1,15);     if(currentLine.endsWith("GET /on1/sub0015")) on1=onoff_time_convertion(on1,-15);
        if(currentLine.endsWith("GET /on1/add0100")) on1=onoff_time_convertion(on1,100);    if(currentLine.endsWith("GET /on1/sub0100")) on1=onoff_time_convertion(on1,-100);
        if(currentLine.endsWith("GET /on1/add0500")) on1=onoff_time_convertion(on1,500);    if(currentLine.endsWith("GET /on1/sub0500")) on1=onoff_time_convertion(on1,-500);

        if(currentLine.endsWith("GET /out1/add0001")) out1=onoff_time_convertion(out1,1);   if(currentLine.endsWith("GET /out1/sub0001")) out1=onoff_time_convertion(out1,-1);
        if(currentLine.endsWith("GET /out1/add0005")) out1=onoff_time_convertion(out1,5);   if(currentLine.endsWith("GET /out1/sub0005")) out1=onoff_time_convertion(out1,-5);
        if(currentLine.endsWith("GET /out1/add0015")) out1=onoff_time_convertion(out1,15);  if(currentLine.endsWith("GET /out1/sub0015")) out1=onoff_time_convertion(out1,-15);
        if(currentLine.endsWith("GET /out1/add0100")) out1=onoff_time_convertion(out1,100); if(currentLine.endsWith("GET /out1/sub0100")) out1=onoff_time_convertion(out1,-100);
        if(currentLine.endsWith("GET /out1/add0500")) out1=onoff_time_convertion(out1,500); if(currentLine.endsWith("GET /out1/sub0500")) out1=onoff_time_convertion(out1,-500);

        if(currentLine.endsWith("GET /on2/add0001")) on2=onoff_time_convertion(on2,1);      if(currentLine.endsWith("GET /on2/sub0001")) on2=onoff_time_convertion(on2,-1);
        if(currentLine.endsWith("GET /on2/add0005")) on2=onoff_time_convertion(on2,5);      if(currentLine.endsWith("GET /on2/sub0005")) on2=onoff_time_convertion(on2,-5);
        if(currentLine.endsWith("GET /on2/add0015")) on2=onoff_time_convertion(on2,15);     if(currentLine.endsWith("GET /on2/sub0015")) on2=onoff_time_convertion(on2,-15);
        if(currentLine.endsWith("GET /on2/add0100")) on2=onoff_time_convertion(on2,100);    if(currentLine.endsWith("GET /on2/sub0100")) on2=onoff_time_convertion(on2,-100);
        if(currentLine.endsWith("GET /on2/add0500")) on2=onoff_time_convertion(on2,500);    if(currentLine.endsWith("GET /on2/sub0500")) on2=onoff_time_convertion(on2,-500);

        if(currentLine.endsWith("GET /out2/add0001")) out2=onoff_time_convertion(out2,1);   if(currentLine.endsWith("GET /out2/sub0001")) out2=onoff_time_convertion(out2,-1);
        if(currentLine.endsWith("GET /out2/add0005")) out2=onoff_time_convertion(out2,5);   if(currentLine.endsWith("GET /out2/sub0005")) out2=onoff_time_convertion(out2,-5);
        if(currentLine.endsWith("GET /out2/add0015")) out2=onoff_time_convertion(out2,15);  if(currentLine.endsWith("GET /out2/sub0015")) out2=onoff_time_convertion(out2,-15);
        if(currentLine.endsWith("GET /out2/add0100")) out2=onoff_time_convertion(out2,100); if(currentLine.endsWith("GET /out2/sub0100")) out2=onoff_time_convertion(out2,-100);
        if(currentLine.endsWith("GET /out2/add0500")) out2=onoff_time_convertion(out2,500); if(currentLine.endsWith("GET /out2/sub0500")) out2=onoff_time_convertion(out2,-500);


        if(currentLine.endsWith("GET /2/status0")){ //Deactivate Clock
          clock_active=0x0; //b0=0: shutdown;  b1=1: on, glowing, b1=0: wrong time
          digitalWrite(SHDN,LOW);
        }
        if(currentLine.endsWith("GET /2/status1")){ //Activate Clock
          clock_active|=0x1; //b0=0: shutdown;  b1=1: on, glowing, b1=0: wrong time
          digitalWrite(SHDN,HIGH);
        }
        if(currentLine.endsWith("GET /2/status2")){
          eeprom_write();
        }
        if(currentLine.endsWith("GET /2/status2")){
          ;
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");

    //Start with time convertion
  }
}



uint16_t onoff_time_convertion(uint16_t val, int16_t diff){
  val+=diff;
  if(val%100>59){
    if(diff>0){   //positive aenderung
      val+=40;
      //val=val+((val%100)-60)-60;
    }
    else{         //negative aenderung
      val-=40;
    }
  }
  if(val>=2400){
    if(diff>0){   //positive aenderung
      val=0+val-2400;
    }
    else{         //negative aenderung
      val=2359-(0xffff-val);
      if(val%100>59){
        val+=40;  //to show correct time while change full hours
      }
    }    
  }
  return val;
}
