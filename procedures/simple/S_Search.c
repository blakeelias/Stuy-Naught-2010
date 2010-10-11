//Code to search for panel...

#include "S_CheckPanel.c"

SET_ATTITUDE_TARGET(&tangentPoints[3]);

target[0] = getPanelSide() * 0.7;
target[1] = myState[1];
target[2] = myState[2];

SET_POSITION_TARGET(target);

