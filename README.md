meArm
=====

Inverse kinematics control library for Phenoptix meArm and Arduino.

The meArm has four mini servos - one for the gripper, and one each to rotate the base, shoulder joint and elbow joint.  But it's not terribly convenient to be specifying things in terms of servo angles when you're much more interested in where you would like to place the gripper, in normal Cartesian (x, y, z) coordinates.

This library solves the angles required to send to the servos in order to meet a given position, allowing for much simpler coding.

Coordinates are measured in mm from the base rotation centre.  Initial 'home' position is at (0, 100, 50), i.e. 100mm forward of the base and 50mm off the ground.

Various other versions of this library exist:
* [Arduino with Adafruit PWM driver board](https://github.com/RorschachUK/meArm_Adafruit)
* [Raspberry Pi with Adafruit PWM driver board](https://github.com/RorschachUK/meArmPi)
* [Beaglebone Black](https://github.com/RorschachUK/meArmBBB)

[![meArm moving with Inverse Kinematics](http://img.youtube.com/vi/HbxhVs3UmuE/0.jpg)](http://www.youtube.com/watch?v=HbxhVs3UmuE)

Usage
-----

```
#include "meArm.h"
#include <Servo.h>

meArm arm;

void setup() {
  arm.begin(11, 10, 9, 6);
  arm.openGripper();
}

void loop() {
  //Go up and left to grab something
  arm.gotoPoint(-80,100,140); 
  arm.closeGripper();
  //Go down, forward and right to drop it
  arm.gotoPoint(70,200,10);
  arm.openGripper();
  //Back to start position
  arm.gotoPoint(0,100,50);
}
```

Three usage examples are included:
* IKTest follows a pre-programmed path defined in Cartesian coordinates
* JoystickIK uses two analogue thumb sticks to guide the gripper in Cartesian space
* meArm_Wii_Classic uses a Wii Classic gamepad connected over I2C to guide the gripper

Installation
------------
Clone this repository to your local machine, and place it in your Arduino libraries folder as 'meArm'.

Class methods of meArm object
-----------------------------
* void begin(int pinBase, int pinShoulder, int pinElbow, int pinGripper) - The four PWM-capable pins used to drive the servos.  Begin must be called in setup() before any other calls to the meArm instance are made.
* void openGripper() - opens the gripper, letting go of anything it was holding
* void closeGripper() - closes the gripper, perhaps grabbing and holding something as it does so
* void gotoPoint(float x, float y, float z) - move in a straight line from the current point to the requested position
* void goDirectlyTo(float x, float y, float z) - set the servo angles to immediately go to the requested point without caring what path the arm swings through to get there - faster but less predictable than gotoPoint
* bool isReachable() - returns true if the point can theoretically be reached by the arm
* float getX() - current x coordinate
* float getY() - current y coordinate
* float getZ() - current z coordinate
