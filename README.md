# automatized-coffee-grinder
**Why?** I love coffee, so I wanted to do something with - you guessed it - coffee!   

My goal is to completely automatize a manual coffee grinder. That is, take a manual coffee grinder and make it electric. Then, just for fun, add some IoT functionality so I don't even have to be in the room in order to get it going (ie. while I'm finding the motivation to leave my bed, start the coffee grinder remotely).  

This will be done by using a custom chassis to hold the coffee grinder and motor, while custom gears provide enough torque to grind the coffee. The setup will be placed on an IoT-enabled scale so that the user can control the amount of coffee desired and start it remotely. The coffee grinder will stop itself once it's reached the desired amount ground (after a certain period of time) and will remind the user if the grinder needs to be replenished with coffee beans. 

**overall progress**
- [x] create custom gears for the motor shaft & coffee grinder shaft using AutoDesk Inventor 
- [x] create a custom chassis for the coffee grinder using AutoDesk Inventor 
  - [ ] fix the chassis so that the coffee grinder does not rotate with motor (ie. the body of the coffee grinder has to remain still while the shaft is moving so that the coffee can actually grind) 
- [x] get two NodeMCUs communicating wirelessly using Wi-Fi
- [x] interface an Arduino Uno with an HX711 amplifier to communicate with a kitchen scale 
- [x] interface Arduino Uno with NodeMCU as master/slave using I2C communication protocols 
  - [ ] add additional functionality for the scope of this project 
- [ ] interface two NodeMCUs as the client/server to add IoT functionality 
- [ ] develop a simple web/mobile app to communicate with NodeMCUs for user-friendly experience 
- [ ] interface the Arduino Uno/NodeMCU with the motor of the coffee grinder for full control 
- [ ] connect the coffee grinder + scale for the full user experience 

You can see a draft version of the chassis here:  
![image test](automatized-coffee-grinder/STL files/coffee-grinder.jpg)
