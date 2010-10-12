//Code to find tangent lines...

xDiff = myState[1];
yDiff = myState[2];
baseAngle = atanf(yDiff / xDiff);
angleDiff = asinf(0.5 / sqrtf(SQ(xDiff) + SQ(yDiff)));

a1 = baseAngle + angleDiff;
a2 = baseAngle - angleDiff;

tangentPoints[0] = 0;
tangentPoints[1] = cosf(a1);
tangentPoints[2] = sinf(a1);
tangentPoints[3] = 0;
tangentPoints[4] = cosf(a2);
tangentPoints[5] = sinf(a2);
