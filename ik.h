/* meArmIK - York Hackspace May 2014
 * Inverse Kinematics solver for three degrees of freedom
 * created for Phenoptix' meArm robot arm
 */
#ifndef IK_H_INCLUDED
#define IK_H_INCLUDED

extern float L1, L2, L3;

// Get polar coords from cartesian ones
void cart2polar(float a, float b, float& r, float& theta);

// Get angle from a triangle using cosine rule
bool cosangle(float opp, float adj1, float adj2, float& theta);

// Solve angles!
bool solve(float x, float y, float z, float& a0, float& a1, float& a2);

#endif // IK_H_INCLUDED
