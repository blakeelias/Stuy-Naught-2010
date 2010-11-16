#include "S_Macros.c"

//Coasts to a target, in absolute coordinates.

void CoastToTarget(float* myPos, float* coastTarget, float magnitude)
{
 float temp[3];

 VSub(coastTarget, myPos, temp);

 if (VLen(temp) < CLOSE)
 {
  SET_POSITION_TARGET(coastTarget);
 }
 else
 {
  VUnit(temp);
  VMult(temp, magnitude, temp);

  ZRSetVelocityTarget(temp);
 }
}

