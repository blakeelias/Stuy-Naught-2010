//The first argument is the same myState provided by ZRUser().
//Don't give this function &myState[6] or something like that.
//Second argument needs to be a unit vector.

#define VRotate(vector, angle, target, result) Vfunc(10, (vector), (target), (result), (angle))
#define VCopy(a, result)                       Vfunc(7, (a), NULL, (result), 0)
#define VAngle(a, b)                           Vfunc(8, (a), (b), NULL, 0)

#define COASTING_VELOCITY 20.0

void CoastToAttitude(float* myState, float* attitudeTarget)
{
 float intermediate[3];
 if (VAngle(&myState[6], attitudeTarget) < (COASTING_VELOCITY * 1.5))
  VCopy(attitudeTarget, intermediate);
 else
  VRotate(&myState[6], COASTING_VELOCITY, attitudeTarget, intermediate);
 ZRSetAttitudeTarget(intermediate);
}

