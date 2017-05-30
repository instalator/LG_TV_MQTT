//--------------------------------- Functions ---------------------------------//
/////////////////////////////////От Брокера//////////////////////////////////////////////
void callback_iobroker(String strTopic, String strPayload){
  if (strTopic == "myhome/LG_TV/Power") {
    if (strPayload == "true") {
      Command = "ka 01 01"; //*****Включить телевизор
      LGTV_CommandSend(Command);
    }
    else if (strPayload == "false") {
      Command = "ka 01 00"; //*****Выключить телевизор
      LGTV_CommandSend(Command);
    }
  } 
  //////////////////////////////////////////////////////////////////
  if (strTopic == "myhome/LG_TV/RemoteKey") {
      String Key = strPayload;
      Command = "mc 01 " + Key; //*****Кнопки пульта
      LGTV_CommandSend(Command);
  }
/////////////////////////////////////////////////////////////////////// 
  if (strTopic == "myhome/LG_TV/Status") {
    if (strPayload == "true") {
    /*  Command = "ka 00 ff"; //***LGTV_PWR
      LGTV_CommandSend(Command);*/
      
      Command = "xb 01 ff"; //***Проверка LGTV_Source
      LGTV_CommandSend(Command);
    }
  }
/////////////////////////////////////////////////////////////////////
  if (strTopic == "myhome/LG_TV/Source") {
    if (strPayload == "tv") {
      Command = "xb 01 10"; //*****Антенна
      LGTV_CommandSend(Command);
    }
    else if (strPayload == "hdmi1") {
       Command = "xb 01 90"; //*****HDMI_1
       LGTV_CommandSend(Command);
    }
    else if (strPayload == "hdmi2") {
       Command = "xb 01 91"; //*****HDMI_2
       LGTV_CommandSend(Command);
    }
    else if (strPayload == "hdmi3") {
       Command = "xb 01 92"; //*****HDMI_3
       LGTV_CommandSend(Command);
    }
        else if (strPayload == "hdmi4") {
       Command = "xb 01 93"; //*****HDMI_4
       LGTV_CommandSend(Command);
    }
    else if (strPayload == "av1") {
       Command = "xb 01 20"; //*****AV_1
       LGTV_CommandSend(Command);
    }
    else if (strPayload == "av2") {
       Command = "xb 01 21"; //*****AV_2
       LGTV_CommandSend(Command);
    }
    else if (strPayload == "pc") {
       Command = "xb 01 40"; //*****PC
       LGTV_CommandSend(Command);
    }
  }
  /////////////////////////////////////////////////////////////////////
   if (strTopic == "myhome/LG_TV/Screen_OFF") {
    if (strPayload == "true") {
      Command = "kd 01 01"; //*****Выключить экран
      LGTV_CommandSend(Command);
    }
    else if (strPayload == "false") {
       Command = "kd 01 00"; //*****Включить экран
       LGTV_CommandSend(Command);
    }
   }
}

