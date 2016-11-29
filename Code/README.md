meArm
=====

Inverse kinematics control library for Phenoptix meArm and Arduino.

The meArm has four mini servos - one for the gripper, and one each to rotate the base, shoulder joint and elbow joint.  But it's not terribly convenient to be specifying things in terms of servo angles when you're much more interested in where you would like to place the gripper, in normal Cartesian (x, y, z) coordinates.

This library solves the angles required to send to the servos in order to meet a given position, allowing for much simpler coding.

Coordinates are measured in mm from the base rotation centre.  Initial 'home' position is at (0, 100, 50), i.e. 100mm forward of the base and 50mm off the ground.

Various other versions of this library exist:
* [Arduino with Adafruit PWM driver board](https://github.com/RorschachUK/meArm_Adafruit)
* [Nokia Screen Driver from Adafruit](https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library)

Things to note are that you can adjust the screen contrast with the variable CON (line 26) and the set up of the servos between lines 98 and 121.
