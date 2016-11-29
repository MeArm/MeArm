/* meArm Wii Classic game pad - York Hackspace May 2014
 * Using inverse kinematics with Wii Classic game controller
 * First stick moves gripper forwards, backwards, left and right
 * Second stick moves gripper up and down (and left and right again).
 * Shoulder buttons or A & B buttons open and close the gripper.
 * The home button returns to starting point.
 * 
 * Uses meArm library by York Hack Space from https://github.com/yorkhackspace/meArm
 * Uses ClassicController library from https://github.com/wayneandlayne/Video-Game-Shield
 *
 * Connect the Wii Classic gamepad via a breakout such as
 * http://www.phenoptix.com/collections/breakout-board/products/wiichuck-a-wii-nunchuck-break-out-board-by-seeed-studio
 *
 * Pins:
 * Arduino    WiiChuck   Base   Shoulder  Elbow    Gripper
 *    GND         -     Brown     Brown   Brown     Brown
 *     5V         +       Red       Red     Red       Red
 *     A4         d
 *     A5         c
 *     11              Yellow
 *     10                        Yellow
 *      9                                Yellow
 *      6                                          Yellow
 */
#include "meArm.h"
#include <Servo.h>
#include <ClassicController.h>

int basePin = 11;
int shoulderPin = 10;
int elbowPin = 9;
int gripperPin = 6;

meArm arm;
ClassicController cc;

void setup() {
  arm.begin(basePin, shoulderPin, elbowPin, gripperPin);
  cc.begin(WII_PLAYER_1);
  cc.joy_left_set_scaled_min_max(0, 99, 0, 99);
  cc.joy_right_set_scaled_min_max(0, 99, 0, 99);
}

void loop() {
  cc.update();

  float dx = 0;
  float dy = 0;
  float dz = 0;
  float dg = 0;
  if (cc.joy_left_left() || cc.joy_right_left())
    dx = -5.0;
  else if (cc.joy_left_right() || cc.joy_right_right())
    dx = 5.0;
  if (cc.joy_left_up())
    dy = 5.0;
  else if (cc.joy_left_down())
    dy = -5.0;
  if (cc.joy_right_up())
    dz = 5.0;
  else if (cc.joy_right_down())
    dz = -5.0;
  if (cc.button_b() || cc.shoulder_left() > 16)
    arm.openGripper();
  else if (cc.button_a() || cc.shoulder_right() > 16)
    arm.closeGripper();
  if (cc.button_home()) {
    arm.gotoPoint(0, 100, 50);
  } 
  if (!(dx == 0 && dy == 0 && dz == 0))
    arm.goDirectlyTo(arm.getX() + dx, arm.getY() + dy, arm.getZ() + dz);
  
  delay(50);
}
