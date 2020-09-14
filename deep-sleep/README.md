# deep-sleep
This folder contains code testing the deep sleep functionality. The goal is to be able to issue an interrupt from the NodeMCU to wake the Arduino. Since we are not using the Arduino 99.9% of the time (and we are also using battery power), this will help in preserving battery life.  

The goal, in the future, is to be able to have a second NodeMCU which will communicate over Wi-Fi. It will work something like this:  

**NodeMCU #2** ---> issues interrupt over Wi-Fi: "i want to grind coffee" ---> **NodeMCU #1** ---> issues interrupt over wire: "i want to grind coffee" ---> **Arduino** ---> turns the motor on to grind coffee (among other features)
