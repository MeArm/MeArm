/* meArm IK test - York Hackspace May 2014
 * Test applying Nick Moriarty's Inverse Kinematics solver
 * to Phenoptix' meArm robot arm, to walk a specified path.
 *
 * Pins:
 * Arduino    Base   Shoulder  Elbow    Gripper
 *    GND    Brown     Brown   Brown     Brown
 *     5V      Red       Red     Red       Red
 *     11    Yellow
 *     10             Yellow
 *      9                     Yellow
 *      6                               Yellow
 */
#include "meArm.h"
#include <Servo.h>

int basePin = 11;
int shoulderPin = 10;
int elbowPin = 9;
int gripperPin = 6;

meArm arm;

void setup() {
  arm.begin(basePin, shoulderPin, elbowPin, gripperPin);
}

void loop() {
  //Clap - so it's obvious we're at this part of the routine
  arm.openGripper();
  arm.closeGripper();
  arm.openGripper();
  arm.closeGripper();
  arm.openGripper();
  delay(500);
  //Go up and left to grab something
  arm.gotoPoint(-80,100,140); 
  arm.closeGripper();
  //Go down, forward and right to drop it
  arm.gotoPoint(70,200,10);
  arm.openGripper();
  //Back to start position
  arm.gotoPoint(0,100,50);
  delay(2000);
}
