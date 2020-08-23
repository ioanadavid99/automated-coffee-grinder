# automatized-coffee-grinder
**Why?** I love coffee. As an engineering student, you don't really have much say in the matter...  

My goal is to completely automatize a manual coffee grinder where a custom chassis will hold the coffee grinder while a motor, using 5:1 gears, will turn to grind the coffee. The grinder will be placed on an IoT scale so an Arduino can read the mass of the scale and stop grinding based on user input (eg. if the user has specified one cup of coffee, the grinder will stop after grinding enough for one cup). A web/mobile app will be used to control the grinder.

**Finished**
- 5:1 custom gears & custom chassis (AutoDesk Inventor)
- custom chassis (AutoDesk Inventor)
- kitchen scale integrated with Arduino (soldered wires, used open-source Arduino code) 

**In progress** 
- adding IoT functionality with the kitchen scale with NodeMCUs (incl. ESP32 modules) by writing code for Arduino 

**Scheduled** 
- developing a web app to interface with the kitchen scale and add user input 
- modify the chassis to use an Arduino to control the motor 
