# automatized-coffee-grinder
My goal is to completely automatize a manual coffee grinder where a custom chassis will hold the coffee grinder while a motor, using 5:1 gears, will turn to grind the coffee. The grinder will be placed on an IoT scale so an Arduino can read the mass of the scale and stop grinding based on user input (eg. if the user has specified one cup of coffee, the grinder will stop after grinding enough for one cup). A web/mobile app will be used to control the grinder.

I have used **AutoDesk Inventor** to design a custom chassis and custom 5:1 gears in order for the motor to have enough torque to grind the coffee.  
Currently, I have configured a kitchen scale to work with an **Arduino** to read mass using open-source code. I am working on implementing IoT capabilities with two **NodeMCUs (incl. ESP32 modules)**.  
In the future, I plan on **developing a web/mobile app** to communicate with the scale.  
I am also planning on improving the chassis so that the Arduino can also communicate with the motor and control it based on user input.

**Finished**
- 5:1 custom gears 
- custom chassis 
- kitchen scale integrated with Arduino

**In progress** 
- adding IoT functionality with the kitchen scale 

**Scheduled** 
- developing a web app to interface with the kitchen scale and add user input 
- modify the chassis to use an Arduino to control the motor 
