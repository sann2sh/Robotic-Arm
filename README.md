Wireless Robotic Arm

This repo contains code for an wireless Robotic Arm with 5 degree of freedom.  

The robotic arm comprises five servo motors, namely one for rotation, two for arm movement, one
for gripper rotation, and one for gripping action.The servos used are MG995R for base rotation,
arm movement and gripper rotation whereas SG90 is used for gripping action.  

The controller, designed to resemble a standard PS4 controller, is equipped with two joystick
modules, two 10k potentiometers, two toggle switches, and four push buttons. These components
provide analog and digital input data to an Arduino Nano microcontroller, which reads the input
values and transmits it to the arm through NRF24L01.  

Communication between the robotic arm and the controller is established using NRF24L01 radio
modules, enabling wireless control of the arm's movements.  
