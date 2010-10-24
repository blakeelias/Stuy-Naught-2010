//The first argument is the same myState provided by ZRUser().
//Don't give this function &myState[6] or something like that.
//Second argument needs to be a unit vector.

#define VRotate(vector, angle, target, result) Vfunc(10, (vector), (target), (result), (angle))
#define VAng(a1, a2)                           Vfunc(8, (a1), (a2), NULL, 0)

#define COASTING_VELOCITY 15


void CoastToAttitude(float* myState, float* attitudeTarget)
{
 if (VAng(&myState[6], attitudeTarget) < COASTING_VELOCITY)
  ZRSetAttitudeTarget(attitudeTarget);
 else
 {
  float intermediate[3];
  VRotate(&myState[6], COASTING_VELOCITY, attitudeTarget, intermediate);
  ZRSetAttitudeTarget(intermediate);
 }
}

