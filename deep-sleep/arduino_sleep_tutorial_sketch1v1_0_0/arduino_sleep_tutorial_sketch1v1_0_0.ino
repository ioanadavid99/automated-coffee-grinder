/**
 * Author:Ab Kurk
 * version: 1.0
 * date: 24/01/2018
 * Description: 
 * This sketch is part of the beginners guide to putting your Arduino to sleep
 * tutorial. It is to demonstrate how to put your arduino into deep sleep and
 * how to wake it up.
 * Link To Tutorial http://www.thearduinomakerman.info/blog/2018/1/24/guide-to-arduino-sleep-mode
 */

/*
 * adapted by Ioana David for her personal project 
 * last modified: Sept 13, 2020
 * full credits for original code given to author listed above  
 * 
 * changes:
 * -added digitalPinToInterrupt 
 * -changed the interrupt mode
 * -changed some text for the serial monitor 
 * -changed function names to be consistent 
 * -changed the value of the LEDs during the execution of the code 
 */

#include <avr/sleep.h>//this AVR library contains the methods that controls the sleep modes

void setup() {
  Serial.begin(115200);             //Start Serial Comunication
  pinMode(LED_BUILTIN,OUTPUT);      //We use the led on pin 13 to indecate when Arduino is A sleep
  pinMode(interruptPin,INPUT_PULLUP);//Set pin d2 to input using the buildin pullup resistor
  digitalWrite(LED_BUILTIN,HIGH);   //turning LED on
}

void loop() {
 delay(2500);         // waiting for 2.5s before going to sleep
 goingToSleep();
}

void goingToSleep(){
  digitalWrite(LED_BUILTIN, LOW);        // added for debugging purposes - the LED should be low when it's "sleeping" and high otherwise 
  sleep_enable();                         //Enabling sleep mode
  attachInterrupt(digitalPinToInterrupt(2), wakeUp, LOW);        //attaching a interrupt to pin d2
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);    //Setting the sleep mode, in our case full sleep
  //digitalWrite(LED_BUILTIN,LOW);          //turning LED off
  delay(1000);                            //wait a second to allow the led to be turned off before going to sleep
  sleep_cpu();                            //activating sleep mode
  Serial.println("just woke up!");        //next line of code executed after the interrupt 
  //digitalWrite(LED_BUILTIN,HIGH);         //turning LED on
}

void wakeUp(){
  Serial.println("interrupt issued");       //Print message to serial monitor
  sleep_disable();                         //Disable sleep mode
  digitalWrite(LED_BUILTIN, HIGH);         // we know it's woken up when the LED is turned on 
  detachInterrupt(digitalPinToInterrupt(2));//Removes the interrupt from pin 2      // i believe this means that it no longer operates as a loop? just does the thing once and gets out of there afterwards
}
