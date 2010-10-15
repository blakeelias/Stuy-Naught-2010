//Code to find tangent lines...

baseAngle = atan2f(target[2], target[1]);
angleDiff = asinf(0.5 / sqrtf(SQ(target[1]) + SQ(target[2])));

tangentPoints[0] = baseAngle - angleDiff;
tangentPoints[1] = baseAngle + angleDiff;
tangentPoints[2] = tangentPoints[0];
