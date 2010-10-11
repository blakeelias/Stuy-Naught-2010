//Code to move towards panel initialization circle...

#include "S_CheckPanel.c"

float targetX = getPanelSide() * 0.7;

if (fabs(myState[0] - targetX) < .02)
 state = STATE_SEARCHING;

target[0] = targetX;
target[1] = myState[1];
target[2] = myState[2];

SET_POSITION_TARGET(target);

//Need to figure out the math to get the tangent line to the
//panel initialization circle...
