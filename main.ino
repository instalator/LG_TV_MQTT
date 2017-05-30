#include <SPI.h>
#include <Ethernet2.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {  0x2E, 0xED, 0xBA, 0x3E, 0x3E, 0xE2 };
IPAddress ip(192, 168, 1, 243);
IPAddress server(192, 168, 1, 190);

#define id_connect "LG_TV"
#define Prefix_subscribe "myhome/LG_TV/"
char buffer[100];
String Command = "";
String inputString = "";
boolean stringComplete = false;
unsigned long  k=0;

///////////////Объявляем порты ввода-вывода
const int start_DI_pin []= {2, 3}; // Порты Ввода
int n_DI_pin = sizeof(start_DI_pin) / sizeof(start_DI_pin[0])-1; //Вычисляем длинну массива

const int start_DO_pin []= {9}; //Порты Вывода
int n_DO_pin = sizeof(start_DO_pin) / sizeof(start_DO_pin[0])-1; //Вычисляем длинну массива
////////////////////////////////////////////////////////////////////////////
void callback(char* topic, byte* payload, unsigned int length) {
    payload[length] = '\0';
    String strTopic = String(topic);
    String strPayload = String((char*)payload);
    callback_iobroker(strTopic, strPayload);
}

EthernetClient ethClient;
PubSubClient client(ethClient);

void reconnect() {
  while (!client.connected()) {
    if (client.connect(id_connect)) {
      client.subscribe("myhome/LG_TV/#");
    } else {
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  inputString.reserve(100);

  for(int i=0 ;i<=n_DI_pin; i++) { pinMode (start_DI_pin [i], INPUT); }
  for(int i=0 ;i<=n_DO_pin; i++) { pinMode (start_DO_pin [i], OUTPUT); }
  
  client.setServer(server, 1883);
  client.setCallback(callback);
  Ethernet.begin(mac, ip);
  delay(1500);
  
    if (client.connect(id_connect)) {
   StatusLG(); //Статусы аппаратуры
    client.publish("myhome/LG_TV/out", "0");
    client.publish("myhome/LG_TV/in", "0");
    client.publish("myhome/LG_TV/Status", "false");
    client.publish("myhome/LG_TV/Source", "0");
    client.publish("myhome/LG_TV/Screen_OFF", "false");
    client.publish("myhome/LG_TV/Power", "false");
    client.publish("myhome/LG_TV/RemoteKey", "0");
    
    client.subscribe("myhome/LG_TV/#");
  }
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  StatusLG();
 
  if (k == 35000){
      Command = "ka 01 ff"; //***LGTV_PWR
      LGTV_CommandSend(Command);
      }
      if (k >= 65000){
      k = 0;
      Command = "xb 01 ff"; //***LGTV_PWR
      LGTV_CommandSend(Command);
      }
  k++;
  
    if (stringComplete) {
      inputString = "";
      stringComplete = false;
    }
}
