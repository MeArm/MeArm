#ifndef FK_H_INCLUDED
#define FK_H_INCLUDED

void polar2cart(float r, float theta, float& a, float& b);

void unsolve(float a0, float a1, float a2, float& x, float& y, float& z);

float distance(float x1, float y1, float z1, float x2, float y2, float z2);

#endif // FK_H_INCLUDED
