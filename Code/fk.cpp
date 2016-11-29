/* Forward kinetics, Nick Moriarty May 2014
This code is provided under the terms of the MIT license.

The MIT License (MIT)

Copyright (c) 2014 Nick Moriarty

Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights 
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in 
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
 */
#include "math.h"
#include "fk.h"
#include "ik.h"

void polar2cart(float r, float theta, float& a, float& b)
{
    a = r * cos(theta);
    b = r * sin(theta);
}

void unsolve(float a0, float a1, float a2, float& x, float& y, float& z)
{
    // Calculate u,v coords for arm
    float u01, v01, u12, v12;
    polar2cart(L1, a1, u01, v01);
    polar2cart(L2, a2, u12, v12);

    // Add vectors
    float u, v;
    u = u01 + u12 + L3;
    v = v01 + v12;

    // Calculate in 3D space - note x/y reversal!
    polar2cart(u, a0, y, x);
    z = v;
}

float distance(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float dx = x2-x1;
    float dy = y2-y1;
    float dz = z2-z1;

    return dx*dx + dy*dy + dz*dz;
}
