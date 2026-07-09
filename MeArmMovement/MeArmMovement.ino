// Controlling arm postions using start and stop in degrees
//TODO: Send commands from serial 
//TODO: Add Inverse Kinematics 
// by Hemal M. Chevli <hemal@black-electronics.com>
//Some code snippets taken from Sweep example in servo library
//MeArm v0.4 - Ben Gray

#include <Servo.h> 
#define DEBUG true

Servo base , upDown, fwdBack,theClaw ;  // servo names makes it easy for connections
int pos = 0;

void setup() 
{ 
  if(DEBUG)
    Serial.begin(9600);
  attachServos();
  start();
  iLiketoMoveItMoveIt();
  detachServos();
} 

void loop() 
{ 
} 

void iLiketoMoveItMoveIt(){
  //Think of it as adding frames to an animation
  start(); // Start position
  moveServo(fwdBack,70,130); // Servo Name, start angle, stop angle
  delay(500);                
  moveServo(upDown,100,10);
  moveServo(upDown,10,160);//The start should be same as end of the previous 
  //function of the corresponding servo, no jerking
  moveServo(fwdBack,130,70);
  moveServo(upDown,160,70); //Make sure you end at the start postion, 
  //otherwise the arm will jerk when program restarts
}

void moveServo(Servo servo,int start,int stop){
  if(start < stop){
    for(pos = start; pos < stop; pos += 1)  // goes from start degrees to stop degrees 
    {                                  // in steps of 1 degree 
      servo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    } 
  }
  else
  {     
    for(pos = start; pos>=stop; pos-=1)     // goes from start degrees to stop degrees 
    {                                
      servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position 
    }
  }

}

void attachServos(){
  base.attach(11);    // Attach base servo to 11
  upDown.attach(10);  // Attach servo responsible for updown movement to 10
  fwdBack.attach(9);  // Attach servo responsible for forward and backward movement to 9
  theClaw.attach(6);  // Attach the claw servo to 6
}

void detachServos(){
  //Use this when arm is going to be in the same postion for long time, it stops the jitters
  // example when you are developing code
  base.detach();  
  upDown.detach(); 
  fwdBack.detach();
  theClaw.detach();
}

void start(){ //Starting positions
  base.write(70);  //tweak these for which ever start position you like
  upDown.write(100);
  fwdBack.write(70);
  theClaw.write(90);
}

