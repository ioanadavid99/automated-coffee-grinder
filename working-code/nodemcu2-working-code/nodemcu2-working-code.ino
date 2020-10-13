/*
 * Author:        Ioana David
 * Last modified: Oct. 12 2020
 * Purpose:       This code will run on NodeMCU #2 and enable it as the server. It will interrupt NodeMCU #1 whenever it receives a signal from a web/mobile app
 *                that a user wants to grind coffee. 
 *                
 *                
 * Author: https://www.instructables.com/id/WiFi-Communication-Between-Two-ESP8266-Based-MCU-T/
 */

#include <SPI.h>
#include <ESP8266WiFi.h>

byte ledPin = 2;
// removed SSID and password for security reasons 
char ssid[] = "";
char pass[] = ""; 
WiFiServer server(80);                    

IPAddress ip(192, 168, 0, 201);               // IP address of the server -> of the MCU 
IPAddress gateway(192,168,0,1);             // gateway of your network - wifi router 
IPAddress subnet(255,255,255,0);            // subnet mask of your network

// TODO: add support for a web/mobile app to send requests 

// TODO: add deep sleep mode? will that work? 

void setup() {
  Serial.begin(115200);                   // only for debug
  WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  WiFi.begin(ssid, pass);                 // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  //Serial.print("server is connected"); 
  server.begin();                         // starts the server

  // for debugging - can remove after testing 
  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // TODO: add functionality to listen to a web/mobile app
  // would only check if the client is available after we get a request from the app 

  // TODO: implement deep sleep functionality for the NodeMCU (if possible?) 
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      digitalWrite(ledPin, HIGH);  // to show the communication only 
      
      // want to send an interrupt to NodeMCU #1 here - assuming we have already gotten it from the app 
      Serial.println("we want to grind coffee now..."); 
      client.println("grind coffee"); 
      
      // the client should respond that it has received the request. otherwise, it will keep polling. 
      while(client.readStringUntil('\r') != "grinding") {   // as long as the response ISN'T that it's received the message (ie. grinding) then keep polling
        ;;  // basically keep polling here
        client.flush(); 
      }
      
      Serial.println("NodeMCU #1 has received our response"); 
      digitalWrite(ledPin, LOW);
      
      // TODO: implement deep sleep functionality 
      goToSleep();    // going to sleep here - will implement functionality later 
    }
    client.stop();                // terminates the connection with the client
  }
}

void goToSleep() { 
  while(1);   // infinite loop for debugging 
}
