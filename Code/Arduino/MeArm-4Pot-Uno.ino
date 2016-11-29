// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 
// Used Michal's code but x4 to control the MeArm v0.3 - Ben Gray

#include <Servo.h> 
 
Servo myservo0, myservo1, myservo2, myservo3 ;  // create servo object to control a servo 
 
int potpin0 = 0;  // analog pin used to connect the potentiometer
int potpin1 = 1;  // analog pin used to connect the potentiometer
int potpin2 = 2;  // analog pin used to connect the potentiometer
int potpin3 = 3;  // analog pin used to connect the potentiometer
int val0;    // variable to read the value from the analog pin 
int val1;    // variable to read the value from the analog pin 
int val2;    // variable to read the value from the analog pin 
int val3;    // variable to read the value from the analog pin 
 
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
  val0 = analogRead(potpin0);            // reads the value of the potentiometer (value between 0 and 1023) 
  val0 = map(val0, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myservo0.write(val0);                 // sets the servo position according to the scaled value 
  Serial.println(val0);
  delay(15);                           // waits for the servo to get there
  val1 = analogRead(potpin1);            // reads the value of the potentiometer (value between 0 and 1023) 
  val1 = map(val1, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myservo1.write(val1); 
  Serial.println(val1);  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
  val2 = analogRead(potpin2);            // reads the value of the potentiometer (value between 0 and 1023) 
  val2 = map(val2, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myservo2.write(val2);                  // sets the servo position according to the scaled value 
  Serial.println(val2);
  delay(15);                           // waits for the servo to get there  
  val3 = analogRead(potpin3);            // reads the value of the potentiometer (value between 0 and 1023) 
  val3 = map(val3, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myservo3.write(val3);                  // sets the servo position according to the scaled value 
  Serial.println(val3);
  delay(15);                           // waits for the servo to get there  
} 
