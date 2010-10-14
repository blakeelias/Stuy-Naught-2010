//Code to find tangent lines...

baseAngle = atan2f(target[2], target[1]);
angleDiff = asinf(0.5 / sqrtf(SQ(target[1]) + SQ(target[2])));

a1 = baseAngle + angleDiff;
a2 = baseAngle - angleDiff;

tangentPoints[0] = 0;
tangentPoints[1] = cosf(a1);
tangentPoints[2] = sinf(a1);
tangentPoints[3] = 0;
tangentPoints[4] = cosf(a2);
tangentPoints[5] = sinf(a2);
