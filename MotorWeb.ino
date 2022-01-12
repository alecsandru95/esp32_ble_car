/*******************************************************************
    A sketch for controlling a toy car with using a web page 
    hosted on a ESP8266
    
    Main Hardware:
    - NodeMCU Development Board cp2102 (Look for the one with the square chip beside the USB port)
    - NodeMCU Motor Shield (L2932)
    
    Written by Brian Lough
    https://www.youtube.com/channel/UCezJOfu7OtqGzd5xrP3q6WA
 *******************************************************************/

#include <WiFi.h>
#include <WebServer.h>

// These are the pins used to control the motor shield

#define DRIVE_1 25 // Motor B
#define DRIVE_2 26

#define STEER_1 18 // Motor A
#define STEER_2 19

// ----------------
// Set your WiFi SSID and Password here
// ----------------
const char* ssid = "****";
const char* password = "****";

bool reconnecting = false;
WebServer server(80);

const char *webpage = 
#include "motorPage.h"
;

void handleRoot() {
  motorStop(DRIVE_1, DRIVE_2);
  motorStop(STEER_1, STEER_2);

  server.send(200, "text/html", webpage);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void motorStop(int pinA, int pinB){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
}
void motorCounterRotate(int pinA, int pinB){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);  
}
void motorRotate(int pinA, int pinB){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH); 
}

void setup(void){

  pinMode(DRIVE_1, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(DRIVE_2, OUTPUT);

  pinMode(STEER_1, OUTPUT);
  pinMode(STEER_2, OUTPUT);

  delay(100);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.on("/forward", [](){
    Serial.println("forward");
    motorRotate(DRIVE_1, DRIVE_2);
    server.send(200, "text/plain", "forward");
  });

  server.on("/driveStop", [](){
    Serial.println("driveStop");
    motorStop(DRIVE_1, DRIVE_2);
    server.send(200, "text/plain", "driveStop");
  });

  server.on("/back", [](){
    Serial.println("back");
    motorCounterRotate(DRIVE_1, DRIVE_2);
    server.send(200, "text/plain", "back");
  });

  server.on("/right", [](){
    Serial.println("right");
    motorCounterRotate(STEER_1, STEER_2);
    server.send(200, "text/plain", "right");
  });

  server.on("/left", [](){
    Serial.println("left");
    motorRotate(STEER_1, STEER_2);
    server.send(200, "text/plain", "left");
  });

  server.on("/steerStop", [](){
    Serial.println("steerStop");
    motorStop(STEER_1, STEER_2);
    server.send(200, "text/plain", "steerStop");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP Server Started");
}

void loop(void){
  server.handleClient();
  
  if(WiFi.status() != WL_CONNECTED){
    motorStop(DRIVE_1, DRIVE_2);
    motorStop(STEER_1, STEER_2);
    
    Serial.println("Reconnecting to WiFi");
    WiFi.reconnect();

    while(WiFi.status() != WL_CONNECTED){
      delay(100);
      Serial.print(".");
    }
  }
}
