//Code to move towards panel initialization circle...

#include "S_CheckPanel.c"

#define targetX (getPanelSide() * 0.7)

if (fabs(myState[0] - targetX) < .02)
 state = STATE_SEARCHING;

baseAngle = atan2f(myState[2], myState[1]);

target[0] = targetX;
target[1] = cosf(baseAngle) * 0.7;
target[2] = sinf(baseAngle) * 0.7;

SET_POSITION_TARGET(target);
#undef targetX

