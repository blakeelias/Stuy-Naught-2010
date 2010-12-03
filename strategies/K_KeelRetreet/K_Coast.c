#include "K_Macros.h"

//Coasts to a target, in absolute coordinates.
//Arguments: myState (of ZRUser), target, target velocity

void CoastToTarget(float* myPos, float* coastTarget, float magnitude)
{
 float temp[3];
 if (magnitude > 0.04) magnitude = 0.04;

 VSub(coastTarget, myPos, temp);

 if (VLen(temp) < (SQ(VLen(&myPos[3])) * 50.0 + 0.08))
 {
  ZRSetPositionTarget(coastTarget);
 }
 else
 {
  VUnit(temp);
  VMult(temp, magnitude, temp);

  if (VDist(temp, &myPos[3]) > 0.02)
   ZRSetVelocityTarget(temp);
 }
}

