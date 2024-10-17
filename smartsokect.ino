#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <EEPROM.h>
#include "page.h"
ESP8266WebServer server(150);
WebSocketsServer webSocket = WebSocketsServer(81);
int pin = 3;     
int button = 0;
int oldflag ;    
int flag = LOW;      
int buttonState;             
int lastButtonState = HIGH; 
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;  
unsigned long startMillis;  
unsigned long currentMillis;
unsigned long  period = 0;
int timeEn = LOW;
char* GPIO2State = "off";
char* Ten;
 
//char* ssid = "project";
char* ssid = "Abd Kareem";
char* password = "frws861425";


void setup()
{
  EEPROM.begin(512);
  checkflagState();
  pinMode(button, INPUT);
  pinMode(pin, OUTPUT);   
  digitalWrite(pin, flag);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
  }
  server.on("/",[](){
    server.send_P(200, "text/html", webpage);  
  });
  
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop()
{
  oldflag=flag;
  delay(20);
  readboutton();
  EEPROM.put(0,flag);
  EEPROM.commit(); 
  if(timeEn==HIGH){
    timer();
    webSocket.broadcastTXT( Ten = "1   ", sizeof(Ten));  // send to the client that there is a timer is running
    delay(20);
   }  
  if (flag == 1) {
    digitalWrite(pin, HIGH);
    GPIO2State = "on  ";
  }
  else           {
    digitalWrite(pin, LOW);
    GPIO2State = "off ";
  }
  webSocket.loop();
  server.handleClient();
  if(flag!=oldflag){
    webSocket.broadcastTXT(GPIO2State, sizeof(GPIO2State));
  }

}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
 if(type == WStype_TEXT){
    if(payload[0] == '#'){
      period = (unsigned long) strtol((const char *) &payload[1], NULL, 10);
      if (period==0){
      timeEn=LOW;
      webSocket.broadcastTXT(GPIO2State, sizeof(GPIO2State));
      }
      else{
        timeEn=HIGH;
        startMillis = millis()/1000;
      } 
   }
   else if (payload[0] == '*'){webSocket.broadcastTXT(GPIO2State, sizeof(GPIO2State));}
   else {flag=!flag;}
 } 
}
/////
void readboutton() {
  int reading = digitalRead(button);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        flag = !flag;
      }
    }
  }

  lastButtonState = reading;
}
void timer()
{
  currentMillis = millis()/1000;  
  if (currentMillis - startMillis >= period)  
  {
    flag=!flag;
    timeEn=LOW; 
  }
}

void checkflagState() {
   flag =  EEPROM.get(0,flag);
  if (flag == 1) {
    digitalWrite(pin, HIGH);
    GPIO2State = "on  ";
  }
  else           {
    digitalWrite(pin, LOW);
    GPIO2State = "off ";
  }
}
