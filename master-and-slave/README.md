# master & slave  
**current work**  
The purpose of this directory is for code to interface an NodeMCU (master) with an Arduino Uno (slave) using I2C communication protocols. Currently the code being used is open-sourced; however, it will be modified in order for the NodeMCU to send commands to the Arduino Uno and to listen to the data being retrieved.  

**future work**  
I will be using two NodeMCUs to interface with each other as a client/server in order to develop this communication using IoT. The goal is to be able to interface with a kitchen scale wirelessly, possibly through simple web/mobile apps as opposed to using the Arduino IDE. 

**schedule** 
- [x] get the Arduino & NodeMCU communicating with one another 
- [ ] get the NodeMCU to give the Arduino instructions 
- [ ] get the Arduino to send them back to the NodeMCU 
- [ ] get a second NodeMCU set up as a server and interface with the first NodeMCU (client) 
- [ ] put it together with the kitchen scale for a custom IoT project
- [ ] create a simple web/mobile app to control the scale 
