/*
 * Author:        Ioana David
 * Last modified: Sept 13 2020
 * Purpose:       Uses a NodeMCU to issue an interrupt to an Arduino. Will be used for more complex purposes; currently in development. 
 */

void setup() {
  Serial.begin(115200);   // want to communicate with the serial monitor so we can see things 
  pinMode(D1, OUTPUT);    // setting this pin as an output - it will be the one issuing the interrupt 
}

void loop() {
  Serial.println("NodeMCU is letting the Arduino sleep...");   
  digitalWrite(D1, HIGH); // want to keep the pin high (for now) - when it is low, it will issue the interrupts 
  delay(3000);            // delay by 3s
  Serial.println("NodeMCU is waking up the Arduino..."); 
  digitalWrite(D1, LOW);  // make it low so it issues the interrupt 
  delay(1000);            // give it time for the Arduino to process
  while(1);               // hang in an infinite loop for the time being - debugging purposes 
}
