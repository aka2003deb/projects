/*PART 1:In the first part of the project we are focused on the
implementation of a robotic arm control system using potentiometer.
The code for achieving this is shown below:*/

#include<Servo.h>
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
int angle1=map(analogRead(A0),0,1023,0,180);
int angle2=map(analogRead(A1),0,1023,0,180); 
int angle3=map(analogRead(A2),0,1023,0,180); 
int angle4=map(analogRead(A3),0,1023,0,180);
servo[0].write(angle1);
servo[1].write(angle2);
servo[2].write(angle3);
servo[3].write(angle4);
} 
