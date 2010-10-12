//Code to find tangent lines...

float xDiff = myState[1];
float yDiff = myState[2];
float baseAngle = atanf(yDiff / xDiff);
float angleDiff = asinf(0.5 / sqrtf(SQ(xDiff) + SQ(yDiff)));

float a1 = baseAngle + angleDiff;
float a2 = baseAngle - angleDiff;

tangentPoints[0] = 0;
tangentPoints[1] = cosf(a1);
tangentPoints[2] = sinf(a1);
tangentPoints[3] = 0;
tangentPoints[4] = cosf(a2);
tangentPoints[5] = sinf(a2);
