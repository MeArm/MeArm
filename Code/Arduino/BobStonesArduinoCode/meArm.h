/* meArm library York Hack Space May 2014
 * A simple control library for Phenoptix' meArm
 * Usage:
 *   meArm arm;
 *   arm.begin(1, 10, 9, 6);
 *   arm.openGripper();
 *   arm.gotoPoint(-80, 100, 140);
 *   arm.closeGripper();
 *   arm.gotoPoint(70, 200, 10);
 *   arm.openGripper();
 */
#ifndef MEARM_H
#define MEARM_H

#include <Arduino.h>
#include <Servo.h>

const float pi=3.14159265359;

struct ServoInfo {
    int n_min, n_max;   // PWM 'soft' limits - should be just within range
    float gain;         // PWM per radian
    float zero;         // Theoretical PWM for zero angle
};

class meArm {
  public:
    //Full constructor uses calibration data, or can just give pins
    meArm(int sweepMinBase=145, int sweepMaxBase=49, float angleMinBase=-pi/4, float angleMaxBase=pi/4,
      int sweepMinShoulder=118, int sweepMaxShoulder=22, float angleMinShoulder=pi/4, float angleMaxShoulder=3*pi/4,
      int sweepMinElbow=144, int sweepMaxElbow=36, float angleMinElbow=pi/4, float angleMaxElbow=-pi/4,
      int sweepMinGripper=75, int sweepMaxGripper=115, float angleMinGripper=pi/2, float angleMaxGripper=0);
    //required before running
    void begin(int pinBase, int pinShoulder, int pinElbow, int pinGripper);
    //Travel smoothly from current point to another point
    void gotoPoint(float x, float y, float z);
    //Set servos to reach a certain point directly without caring how we get there 
    void goDirectlyTo(float x, float y, float z);
    //Grab something
    void openGripper();
    //Let go of something
    void closeGripper();
    //Check to see if possible
    bool isReachable(float x, float y, float z);
    //Current x, y and z
    float getX();
    float getY();
    float getZ();
  private:
    float _x, _y, _z;
    Servo _base, _shoulder, _elbow, _gripper;
    ServoInfo _svoBase, _svoShoulder, _svoElbow, _svoGripper;
    int _pinBase, _pinShoulder, _pinElbow, _pinGripper;
};

#endif
