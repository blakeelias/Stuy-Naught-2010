void CoastToTarget(float* myPos, float* coastTarget, float magnitude)
{
 float temp[3];
 if (magnitude > 0.04) magnitude = 0.04;
 Vfunc(2, (coastTarget), (myPos), (temp), 0);
 if (mathVecMagnitude((temp), 3) < (mathSquare(mathVecMagnitude((&myPos[3]), 3)) * 50.0 + 0.08))
 {
  ZRSetPositionTarget(coastTarget);
 }
 else
 {
  mathVecNormalize((temp), 3);
  Vfunc(4, (temp), NULL, (temp), (magnitude));
  if (Vfunc(6, (temp), (&myPos[3]), NULL, 0) > 0.02)
   ZRSetVelocityTarget(temp);
 }
}
