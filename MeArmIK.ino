// MeArm Inverse Kinematics Sketch. WIP by Benjamin Gray
// Currently working in plane, shown in code as XY but is really XZ
// Is a little skew as the start angle needs adjusting
// Then the code just needs replicating in the XY axis
// Start point and references below
// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 
// then with info from http://www.learnaboutrobots.com/inverseKinematics.htm
// and also https://www.circuitsathome.com/mcu/robotic-arm-inverse-kinematics-on-arduino

#include <Servo.h>
#include <Arduino.h>


/* Arm Measurements */
#define bicep 81 // bicep length in mm
#define forearm 81 // forearm length in mm
#define base 60// base height in mm
 
Servo myservo0, myservo1, myservo2, myservo3;  // create servo object to control a servo 
 
int potpin0 = 0;  // analog pin used to connect the potentiometer
int potpin1 = 1;  // analog pin used to connect the potentiometer
int potpin2 = 2;  // analog pin used to connect the potentiometer
int potpin3 = 3;  // analog pin used to connect the potentiometer
//float val0;    // value to set servo for bicep 
//float val3;    // value to set servo for forearm

int val1;    // variable to read the value from the analog pin 
int val2;    // variable to read the value from the analog pin 
int x;    // variable to read the value from the analog pin
int y;    // variable to read the value from the analog pin

#define ftl(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))  //float to long conversion


/* some stuff to help later on */
float for_sq = forearm*forearm;
float bic_sq = bicep*bicep;
/* these are used in the equations more than the actual lengths */
 
void setup() 
{ 
  Serial.begin(9600);
  myservo0.attach(11);  // attaches the servo on pin 11 to the servo object
  myservo1.attach(10);  // attaches the servo on pin 10 to the servo object
  myservo2.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo3.attach(6);  // attaches the servo on pin 6 to the servo object
} 
 
void loop() 
{ 
  /*Starting by reading x and y from potpins we'll use these to calculate the position of the servos*/
  
  x = analogRead(potpin0);        // read potpin0 and set to x
  x = map(x, 0, 1023, 20-base, 310-base);   // scale pot value between the min and max values of x on the arm
  delay(15);   // reads the value of the potentiometer (value between 0 and 1023) 
  y = analogRead(potpin3);            // reads the value of the potentiometer (value between 0 and 1023) 
  y = map(y, 0, 1023, 24, 180);   // scale pot value between the min and max values of x on the arm
  delay(15); 
   
 int b = sqrt ((x * x) + (y * y));
 //Serial.write(b);
 float q1 = atan2( x, y );
 //Serial.print(q1,4);
 float q2 = acos((bic_sq - for_sq + (b * b))/(2 * bicep * b));
 //Serial.print(q2,4);
 float abi = q1 + q2;
 //Serial.print(abi,4);
 float afo = acos((bic_sq + for_sq - (b * b))/(2 * bicep * forearm));
 Serial.print(abi*57.3,4);
 Serial.print(afo*57.3,4);
  

  myservo0.write(180-(ftl(abi*57.3)));                 // sets the servo position according to the scaled value 
  myservo3.write(ftl(afo*57.3));                  // sets the servo position according to the scaled value 
  delay(15);
  
  delay(15);                           // waits for the servo to get there
  val1 = analogRead(potpin1);            // reads the value of the potentiometer (value between 0 and 1023) 
  val1 = map(val1, 0, 1023, 40, 90);     // scale it to use it with the gripper (40 and 90 degrees) 
  myservo1.write(val1);   // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
  val2 = analogRead(potpin2);            // reads the value of the potentiometer (value between 0 and 1023) 
  val2 = map(val2, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myservo2.write(val2);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there  
} 
