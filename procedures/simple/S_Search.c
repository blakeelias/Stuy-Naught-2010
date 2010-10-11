//Code to search for panel...

#include "S_CheckPanel.c"

target[0] = tangentPoints[3] - myState[0];
target[1] = tangentPoints[4] - myState[1];
target[2] = tangentPoints[5] - myState[2];

SET_ATTITUDE_TARGET(target);

target[0] = getPanelSide() * 0.7;
target[1] = myState[1];
target[2] = myState[2];

SET_POSITION_TARGET(target);

