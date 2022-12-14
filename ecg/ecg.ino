#include <Arduino.h>
#include <WiFi.h>
#include <SocketIoClient.h>

const char* ssid     = "INFINITUMF89F_2.4"; //"INFINITUMC2A2_2.4"
const char* password = "MM3Xx2D4Qc";        //"Dus2qzqyFC"
const char* server = "34.125.28.185"; //Enter server adress
const uint16_t port = 5001; // Enter server port
int payload_entero;

SocketIoClient socketIO;
#define VARIABLE_LABEL "sensor" // Assing the variable label
#define ONBOARD_LED 2
 
#define SENSOR A0 // Set the A0 as SENSOR

char str_sensor[10];
 
/****************************************
 * Main Functions
 ****************************************/
void setup() {
  pinMode(ONBOARD_LED,OUTPUT);
  Serial.begin(115200);
  connectWiFi_STA();
  socketIO.begin(server, port);
  socketIO.on("desde_servidor",procesar_mensaje_recibido);
  
  pinMode(SENSOR, INPUT); 
  
}
 
void loop() {
  
  float sensor = analogRead(SENSOR); 
  
  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(sensor, 4, 2, str_sensor);
  Serial.println(str_sensor);
  socketIO.emit("nuevo_mensaje",str_sensor);
  delay(5);
  socketIO.loop();
}

void connectWiFi_STA()
{
   delay(10);
   Serial.println("");
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   { 
     delay(100);  
     Serial.print('.'); 
   }
   Serial.println("");
   Serial.print("Iniciado STA:\t");
   Serial.println(ssid);
   Serial.print("IP address:\t");
   Serial.println(WiFi.localIP());
}

void procesar_mensaje_recibido(const char * payload, size_t length) {
 Serial.printf("Mensaje recibido: %s\n", payload);
 String paystring = String(payload);
 if(paystring == "ON")
 {
  digitalWrite(ONBOARD_LED,HIGH);
 }
 else if(paystring == "OFF")
 {
  digitalWrite(ONBOARD_LED,LOW);
 }
}
