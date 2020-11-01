/*
 * Author:        Ioana David
 * Last modified: OCT. 12 2020 
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
 #define  DOUT                3    // this probably has to change - this is where the interrupt will be issued 
 #define  INTERRUPT_PIN       2     // pin 2 is used to issue the interrupt - see what other pin you can use 
 // TODO: will have to change the value for CLK probably 
 #define  CLK                 2    // this will also probably have to change, keeping it for now 
 #define  CALIBRATION_FACTOR  242   // this is the calibration factor determined from tests using the author's code; can be changed later if necessary 

 // other definitions 
 #define  BASE_WEIGHT     273   // weight in grams of the coffee grinder WITHOUT any coffee 

// error codes here for reading the weight of the coffee grinder 
 #define  SUCCESS         0
 #define  ERR_LOW_COFFEE  1
 #define  ERR_NO_COFFEE   2
 #define  ERR_UNKNOWN     3

 HX711 scale; 
 int scaleStatus;     // this is the status of the scale. global var - treating it like a status register in an MCU. 
  
void setup() {
  Serial.begin(115200);   // the baud rate for the serial monitor for easier debugging 

  // setting up the scale functionalities 

  scale.begin(DOUT, CLK); // TODO: determine what pins you have available to use for this function 
  scale.set_scale(CALIBRATION_FACTOR); 
  scale.tare(); 

  // other configuration thingies below 

  // for debugging 
  pinMode(LED_BUILTIN, OUTPUT); 
}

void loop() {

  // go to deep sleep immediately
  // if you get an interrupt, wake up, and weigh the scale
  // if it is low, WARN the user that there may not be enough coffee for the amount that they want to grind
  // wait for their response. if none is received within a certain amount of time, go back to deep sleep 
  // else, send the command to the motor to grind for X seconds to achieve desired amount of ground coffee 
  // it grinds. then it goes back to sleep. tada!

  digitalWrite(LED_BUILTIN, HIGH); 
  Serial.println("arduino: going to sleep"); 
  goingToSleep();   // this function just makes sure it goes to sleep. then it basically calls other ISRs when it wakes up. it *doesn't* have to be implemented as ISRs (ie. the code could all be functions) but i wanted to test out using ISRs for deep sleep versus just normal functions 
} 

/*
 * Purpose:     puts the Arduino in deep sleep mode unless interrupted otherwise 
 * Parameters:  none
 * Return:      none 
 */
void goingToSleep(void) { 
  Serial.println("going to sleep... Zzz"); 
  digitalWrite(LED_BUILTIN, LOW);       // for debugging 
   
  // from the tutorial:
  sleep_enable(); 
  attachInterrupt(digitalPinToInterrupt(2), wakeUp, HIGH);   // setting an interrupt for the NodeMCU 
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
  sleep_cpu();  // this enables sleep mode again 
  Serial.println("just woke up! :D");     // debugging 
}

/*
 * Purpose:     wakes the Arduino up to get the reading from the scale 
 * Parameters:  none
 * Return:      none   
 */
void wakeUp(void) { 
  sleep_disable(); 
  digitalWrite(LED_BUILTIN, HIGH);                    // for debugging 
  Serial.println("arduino: waking up"); 
  //detachInterrupt(digitalPinToInterrupt(2));          // tbh still not too sure what this does?? removes the interrupt from pin2... might not operate as a loop in this case 

  checkWeight();    // get the scale to do its thing 
  if(scaleStatus == SUCCESS) { 
    grindCoffee(1);  // TODO: need to get the serving num from the nodemcu here 
  }

  else{ 
    triggerFault();       // functionality for edge cases has not yet been determined -- just triggering a fault or something like that 
  }
 
} 

/*
 * Purpose:     checks the scale and updates the status register as appropriate  
 * Parameters:  none
 * Return:      none 
 */ 
void checkWeight(void){ 
    // TODO: power up the scale -- verify 
  scale.power_up();     // saves the life of the battery-powered scale :-) 
  
  // the most basic thing to do: get the scale to perform a reading 
  // serial monitor for debugging right now 
  Serial.print("reading from the scale: ");
  Serial.print(scale.get_units(), 1); 
  Serial.print("g"); 
  Serial.println(); 

  int weight = scale.get_units(); 

  // error codes to store in scaleStatus (like a status register) 
  if (weight = BASE_WEIGHT) { 
    scaleStatus = ERR_NO_COFFEE; 
  }
  else if(weight <= (BASE_WEIGHT + 5)) { 
    scaleStatus = ERR_LOW_COFFEE; 
  }
  else if(weight < BASE_WEIGHT) { 
    scaleStatus = ERR_UNKNOWN; 
  }
  else { 
    scaleStatus = SUCCESS; 
  }

  // TODO: power down the scale -- verify 
  scale.power_down();   
}

// TODO: finish function that tells the motor to grind
/*
 * Purpose:     tells the motor attached to the Arduino to grind coffee for a desired serving 
 * Parameters:  servingNum: the serving number (eg. one cup, two cups) 
 * Return:      none 
 */ 
void grindCoffee(int servingNum) {    // could also get the serving num from inside the function to make it more like an ISR? 
  while(1);   // just for debugging 
}

/*
 * Purpose:     functionality for dealing with edge cases 
 * Parameters:  none
 * Return:      none 
 */ 
void triggerFault(void) { 
  while(1);   // just stay here for now... will figure out additional functionality in the future 
}
