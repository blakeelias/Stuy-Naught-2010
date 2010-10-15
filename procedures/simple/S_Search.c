//Code to search for panel...

#include "S_CheckPanel.c"

#define COORD myState
#include "S_Tangent.c"
#undef COORD

#include "S_Target.c"

tangentPoints[2] += scanTarget * 0.4;

if ((scanTarget == 1) && (tangentPoints[2] >= tangentPoints[1]))
 scanTarget = -1;
else if ((scanTarget == -1) && (tangentPoints[2] <= tangentPoints[0]))
 scanTarget = 1;

target[0] = getPanelSide() * 0.7;
target[1] = myState[1];
target[2] = myState[2];

SET_POSITION_TARGET(target);

