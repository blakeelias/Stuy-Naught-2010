//Code to find tangent lines...

baseAngle = atan2f(-COORD[2], -COORD[1]);
angleDiff = asinf(0.5 / sqrtf(SQ(COORD[1]) + SQ(COORD[2])));

tangentPoints[0] = baseAngle - angleDiff;
tangentPoints[1] = baseAngle + angleDiff;

