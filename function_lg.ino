
//----------------------------------- Functions of commands ------------------------------------//
void LGTV_CommandSend(String Command) {
        delay(50); 
       int ln =  Command.length ()+1;
        char charBufVar[ln];
        Command.toCharArray(charBufVar, ln);
           int i;
            for (i = 0; i <= ln ; i++) {
              Serial.print(charBufVar[i]);
              delay(5);
            }
            Serial.print('\r');
            delay(1); 
        serialEvent();
        client.publish("myhome/LG_TV/Status", "false");
        StatusLG();
}

void StatusLG(){
          String str = inputString;
          if (stringComplete == true){
            if (str == "a 01 OK00x")client.publish("myhome/LG_TV/Power", "false");
            if (str == "a 01 NG00x")client.publish("myhome/LG_TV/Power", "false");
            if (str == "a 01 OK01x")client.publish("myhome/LG_TV/Power", "true");
            if (str == "b 01 OK10x")client.publish("myhome/LG_TV/Source", "TV");
            if (str == "b 01 OK90x")client.publish("myhome/LG_TV/Source", "HDMI1");
            if (str == "b 01 OK91x")client.publish("myhome/LG_TV/Source", "HDMI2");
            if (str == "b 01 OK92x")client.publish("myhome/LG_TV/Source", "HDMI3");
            if (str == "b 01 OK93x")client.publish("myhome/LG_TV/Source", "HDMI4");
            if (str == "b 01 OK20x")client.publish("myhome/LG_TV/Source", "AV1");
            if (str == "b 01 OK21x")client.publish("myhome/LG_TV/Source", "AV2");
            if (str == "b 01 OK40x")client.publish("myhome/LG_TV/Source", "PC");
            if (str == "d 01 OK00x")client.publish("myhome/LG_TV/Screen_OFF", "false");
            if (str == "d 01 OK01x")client.publish("myhome/LG_TV/Screen_OFF", "true");
            client.publish("myhome/LG_TV/Status", "true");
            char charVar[20];
            inputString.toCharArray(charVar, 20);
            client.publish("myhome/LG_TV/out", charVar);
          }
     }
     
////////////////////////////////////Статусы Брокеру/////////////////////////////////////
void serialEvent() {
  while (Serial.available()>0) {
    char inChar = (char)Serial.read(); 
    inputString += inChar;
    /*
                  char charVar[20];
                  inputString.toCharArray(charVar, 20);
                  client.publish("myhome/test/RS232_in", charVar);  
      */
    if (inChar == 'x') {
      inputString.replace(" ", "");
      char charVar[20];
      inputString.toCharArray(charVar, 20);
      client.publish("myhome/LG_TV/in", charVar);
      stringComplete = true;
      StatusLG();
    } 
    if (inChar == '\n') {
      inputString.replace(" ", "");
      char charVar[20];
      inputString.toCharArray(charVar, 20);
      client.publish("myhome/LG_TV/in", charVar);
      stringComplete = true;
      StatusLG();
    } 
  }
}
