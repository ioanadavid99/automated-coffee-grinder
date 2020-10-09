/*
 * Author:        Ioana David
 * Last modified: Oct 08 2020
 * Purpose:       This code will run on NodeMCU #1. NodeMCU #1 will use this code to issue an interrupt to an Arduino. NodeMCU #2 will send an interrupt to NodeMCU #1 
 *                whenever NodeMCU #2 wants coffee to grind. This will be achieved wirelessly.
 */

// TODO: add credit for the wifi stuff 

#include <SPI.h>
#include <ESP8266WiFi.h>

byte ledPin = 2;    // using this to know that communication is taking place 
// removed SSID and password for security reasons 
char ssid[] = "";
char pass[] = ""; 
unsigned long askTimer = 0;

IPAddress server(192, 168, 0, 201); ;       // the fix IP address of the server
WiFiClient client;

void setup() {
  Serial.begin(115200); 
  // TODO: determine if syntax is valid (ie. can call D1, or is there a specific # to write?) 
  pinMode(D1, OUTPUT);    // set up pin D1 to produce a signal to wake up the Arduino 
  Wifi.begin(ssid, pass); 
  while(Wifi.status() != WL_CONNECTED) { 
    Serial.println("connecting..."); 
    delay(500);   // half a second 
  }

  // don't need the stuff below - helpful for debugging 
  Serial.print("client is connected"); 
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
  // wait for NodeMCU #2 to send a signal here...
  client.connect(server, 80);
  // here - need to wait for an interrupt from the nodemcu #2
  // TODO: determine the appropriate function to achieve the above 
  // can also call an ISR to wake the Arduino up after receiving the interrupt from NodeMCU #2 

  // interrupt the Arduino. get it to grind coffee 
  // TODO: make this an ISR? 
  digitalWrite(D1, HIGH);
  Serial.println("NodeMCU is putting the Arduino to sleep...");   // for debugging 
  delay(3000);            // used for debugging purposes - this is just to verify that the Arduino received the signal 
  digitalWrite(D1, LOW);
  Serial.println("NodeMCU is waking the Arduino up...");          // for debugging 
  delay(3000);            // again, also used for debugging 

  while(1);               // hang here for now, for debugging purposes 

}
