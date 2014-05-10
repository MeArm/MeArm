meArm
=====

Inverse kinematics control library for Phenoptix meArm and Arduino.

The meArm has four mini servos - one for the gripper, and one each to rotate the base, shoulder joint and elbow joint.  But it's not terribly convenient to be specifying things in terms of servo angles when you're much more interested in where you would like to place the gripper, in normal Cartesian (x, y, z) coordinates.

This library solves the angles required to send to the servos in order to meet a given position, allowing for much simpler coding.

Two usage examples are included:
* IKTest follows a pre-programmed path defined in Cartesian coordinates
* JoystickIK uses two analogue thumb sticks to guide the gripper in Cartesian space

Clone this repository to your local machine, and place it in your Arduino libraries folder as 'meArm'.
