/*
 * Author:        Ioana David
 * Last modified: Oct 08 2020
 * Purpose:       This code will run on NodeMCU #1. NodeMCU #1 will use this code to issue an interrupt to an Arduino. NodeMCU #2 will send an interrupt to NodeMCU #1 
 *                whenever NodeMCU #2 wants coffee to grind. This will be achieved wirelessly.
 */

// TODO: add credit for the wifi stuff 

#include <SPI.h>
#include <ESP8266WiFi.h>

#define D1  5 // hopefully this works 

byte ledPin = 2;    // using this to know that communication is taking place 
// removed SSID and password for security reasons 
char ssid[] = "";
char pass[] = ""; 
unsigned long askTimer = 0;

IPAddress server(192, 168, 0, 201); ;       // the fix IP address of the server
WiFiClient client;

void setup() {
  Serial.begin(115200); 
  // TODO: determine if syntax is valid (ie. can call D1, or is there a specific # to write?) - this is pin 5, if this doesn't work 
  pinMode(D1, OUTPUT);    // set up pin D1 to produce a signal to wake up the Arduino 
  /*
  // just debugging right now 
  Wifi.begin(ssid, pass); 
  while(Wifi.status() != WL_CONNECTED) { 
    Serial.println("connecting..."); 
    delay(500);   // half a second 
  }
  // don't need the stuff below - helpful for debugging. will comment out later 
  Serial.print("client is connected"); 
  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());
  */ 
  pinMode(ledPin, OUTPUT);
  //digitalWrite(D1, LOW); // start with the Arduino in sleep mode 
}

void loop() {
  // wait for NodeMCU #2 to send a signal here...
  client.connect(server, 80);
  // here - need to wait for an interrupt from the Nodemcu #2

  // polling to hear from the server 
  Serial.println("polling to hear from the server"); 
  while(client.readStringUntil('\r') != "grind coffee"){ 
    client.flush();   // just stay here and keep polling 
  }

  digitalWrite(ledPin, HIGH);   // debugging feature 
  // got the response. time to tell the Arduino
  Serial.println("time to grind..."); 

  // letting NodeMCU #2 know we received the message 
  client.println("grinding");     
  
  // TODO: make this an ISR? 
  // interrupt the Arduino. get it to grind coffee 
  Serial.println("waking the Arduino up..."); 
  digitalWrite(D1, HIGH);
  Serial.println("NodeMCU is waking the Arduino up...");   // for debugging 
  // TODO: wait for a response from the Arduino that it has woken up. otherwise, keep polling 
  delay(3000);            // used for debugging purposes - this is just to verify that the Arduino received the signal 

  // don't need the below - Arduino will automatically go to sleep 
  /*  
  digitalWrite(D1, HIGH); // TODO: do we even need to signal to put it to sleep? just needs to go high when we want to wake it up
  Serial.println("NodeMCU is putting the Arduino in sleep...");          // for debugging 
  delay(3000);            // again, also used for debugging 
  */ 
  
  // TODO: get a signal from the Arduino that we are done grinding 
  Serial.println("done grinding!");   // printing to the serial monitor 
  client.println("done grinding");    // also for debugging 

  digitalWrite(ledPin, LOW);      // also for debugging 
  while(1);               // hang here for now, for debugging purposes 
}

// smol test script to verify that interrupts are working as expected 
/*
  while(true) { 
    Serial.println("nodemcu: going to sleep"); 
    digitalWrite(D1, LOW); 
    digitalWrite(ledPin, LOW); 
    delay(5000);    // just delay for a bit here 
    Serial.println("nodemcu: waking up");
    digitalWrite(D1, HIGH); 
    digitalWrite(ledPin, HIGH); 
    delay(5000);   
  } 
  */ 
