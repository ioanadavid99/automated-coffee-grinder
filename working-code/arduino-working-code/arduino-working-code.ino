/*
 * Author:        Ioana David
 * Last modified: Sept. 21st, 2020
 * Purpose:       Beginning to put different components of the project together. See GitHub for a detailed explanation of the process. This code will be downloaded to an Arduino Uno. 
 * 
 * Credits:
 * Nathan Seidle for the tutorial on using an HX711 amplifier to interface with an Arduino and a kitchen scale.
 * Ab Kurk for the tutorial on putting the Arduino in deep sleep mode. 
 * 
 */

 #include "HX711.h"
 #include "avr/sleep.h"

 // pin constants - will have to change 
 #define  DOUT   3    // this probably has to change - this is where the interrupt will be issued 
 // pin 2 is used to issue the interrupt - see what other pin you can use 
 #define  CLK    2    // this will also probably have to change, keeping it for now 
 #define  CALIBRATION_FACTOR  242   // this is the calibration factor determined from tests using the author's code; can be changed later if necessary 

 HX711 scale; 
  
void setup() {
  Serial.begin(115200);   // the baud rate for the serial monitor for easier debugging 

  // setting up the scale functionalities 
  scale.begin(DOUT, CLK); // TODO: determine what pins you have available to use for this function 
  scale.set_scale(CALIBRATION_FACTOR); 
  scale.tare(); 

  // other configuration thingies below 
}

void loop() {
  // go to deep sleep immediately
  // if you get an interrupt, wake up, and weigh the scale
  // if it is low, WARN the user that there may not be enough coffee for the amount that they want to grind
  // wait for their response. if none is received within a certain amount of time, go back to deep sleep 
  // else, send the command to the motor to grind for X seconds to achieve desired amount of ground coffee 
  // it grinds. then it goes back to sleep. tada!

  goingToSleep();
} 

/*
 * Purpose:     puts the Arduino in deep sleep mode unless interrupted otherwise 
 * Parameters:  none
 */
void goingToSleep(void) { 
  Serial.println("going to sleep... Zzz"); 
  // not sure if this will work - different library, unfamiliar with it 
  LowPower.deepSleep();       // apparently puts the Arduino in deep sleep mode - using a different library so not sure 
  // alternatively (from the tutorial):
  sleep_enable(); 
  attachInterrupt(digitalPinToInterrupt(2), wakeUp, LOW);   // setting an interrupt for the NodeMCU 
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
  sleep_cpu(); 
  Serial.println("just woke up! :D"); 
}

void wakeUp(void) { 
  sleep_disable(); 
  detachInterrupt(digitalPinToInterrupt(2));          // tbh still not too sure what this does?? 
  // the most basic thing to do: get the scale to perform a reading 
  Serial.print("reading from the scale: ");
  Serial.print(scale.get_units(), 1); 
  Serial.print("g"); 
  Serial.println(); 
}
