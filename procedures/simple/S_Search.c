//Code to search for panel...

#include "S_CheckPanel.c"

target[0] = 0;
target[1] = tangentPoints[scanTarget + 1];
target[2] = tangentPoints[scanTarget + 2];

SET_ATTITUDE_TARGET(target);

if (fabs(VAngle(&myState[6], target)) < 9.0)
 scanTarget = 3 - scanTarget;

target[0] = getPanelSide() * 0.7;
target[1] = myState[1];
target[2] = myState[2];

SET_POSITION_TARGET(target);

