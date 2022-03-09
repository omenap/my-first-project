#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <ESP8266WebServer.h>
ESP8266WebServer webserver(80);

#define FIREBASE_HOST "iot-smart-plug-bfa5e-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "EE3tYKYyl1jxYKh9QkwLf03XJVfIjSpgqEr1gvv0"
#define WIFI_SSID "Collin powell"
#define WIFI_PASSWORD "12345678"
int button = 5;
int led = 4;
int A = 0;
int B = 0;
int C = 0;
FirebaseData firebaseData;
FirebaseData loadData;
void setup() {
  Serial.begin(115200);
  pinMode(button,INPUT);
  pinMode(led,OUTPUT);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() !=WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println("Connected");
}
void loop() {
  B = digitalRead(button);
  delay (50);
  if(B!=A){
    if(B==HIGH){
      if(C==0){
        C=1;
        digitalWrite (led,HIGH);
        String state = "on"; 
        Firebase.setString(firebaseData,"/smartDB/loadState",state);
        }
        else{
          C=0;
          digitalWrite(led,LOW);
          String state = "off";
          Firebase.setString(firebaseData,"/smartDB/loadState",state);
        }
    }
  }
 A=B; 
  
}

