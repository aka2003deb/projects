/*PART 2:In the second part of the project we are focused on the
implementation of an advance robotic arm control system without using
any potentiometer rather we will use serial communication-the user will
be able to give the input in the serial monitor itself. The code for achieving
this is shown below:*/

#include<Servo.h>
int angle1; 
int angle2; 
int angle3;
int angle4; 
Servo servo[4];
const byte servoPin[4]={2,3,4,5};

void setup(){
Serial.begin(9600); 
for(int i=0;i<4;i++){
servo[i].attach(servoPin[i]);
servo[i].write(90); delay(1000);
}
} 

void loop(){
Serial.println("Set the degree of motion for 1st motor:");
while (Serial.available() == 0){ } 
angle1 =Serial.parseInt();
Serial.println("Set the degree of motion for 2nd motor:");
while (Serial.available() == 0){ }
angle2 = Serial.parseInt();
Serial.println("Set the degree of motion for 3rd motor:");
while (Serial.available() == 0){ } angle3 =
Serial.parseInt();
Serial.println("Set the degree of motion for 4th motor:");
while (Serial.available() == 0){ } 
angle4 =Serial.parseInt();
servo[0].write(angle1);
servo[1].write(angle2);
servo[2].write(angle3);
servo[3].write(angle4); 
while(Serial.available() == 0){ }
} 
