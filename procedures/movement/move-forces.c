/*
 * Tests movement using ZRSetForces, from initial location to the panel
 * (as opposed to using ZRSetPositionTarget, trying to be more efficient)
 * 
 * Assumes default game setup
 */

// Global variables
int state = 0;
float force[3] = 0;
float target[3] = 0;

void ZRUser(float *myState, float *otherState, float time) {
  #define VDist(a, b)          Vfunc(6, (a), (b), NULL, 0)

  printf("time: %3.0f,  position: (%5.3f, %5.3f, %5.3f),  fuel: %3.2f,  target dist: %5.3f\n",
	 time, myState[0], myState[1], myState[2], getPercentFuelRemaining(), VDist(target, myState));

  if (state < 7) {
    force[0] = 0.5;
    target[0] = 0.7;
    target[1] = 0.3484;
    ZRSetForces(force);
    state++;
  }
  if (state >= 7 && state < 14) {
    if (VDist(target, myState) < 0.25) {
      force[0] = -0.5;
      ZRSetForces(force);
      state++;
    }
  }
  if (state == 14) {
    force[0] = -.06;
    state++;
  }
  if (state >= 15) {
    ZRSetPositionTarget(target);
  }
}
