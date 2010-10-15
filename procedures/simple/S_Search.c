//Code to search for panel...

#include "S_CheckPanel.c"
#include "S_Tangent.c"

target[0] = 0;
target[1] = cosf(tangentPoints[2]);
target[2] = sinf(tangentPoints[2]);

SET_ATTITUDE_TARGET(target);

tangentPoints[2] += scanTarget * 0.2;

if ((scanTarget == 1) && (tangentPoints[2] >= tangentPoints[1]))
 scanTarget = -1;
else if ((scanTarget == -1) && (tangentPoints[2] <= tangentPoints[0]))
 scanTarget = 1;

if (fabs(VAngle(&myState[6], target)) < 6.0)
 scanTarget = 1 - scanTarget;

target[0] = getPanelSide() * 0.7;
target[1] = myState[1];
target[2] = myState[2];

SET_POSITION_TARGET(target);

