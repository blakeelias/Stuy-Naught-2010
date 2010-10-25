//Code to search for panel...

#include "S_CheckPanel.c"

#define COORD myState
#include "S_Tangent.c"
#undef COORD

#include "S_Target.c"

if(fabs(otherState[0] - otherTargetX < .05)){
	state = STATE_WAIT;
	break;
}

tangentPoints[2] += scanTarget * SEARCH_ANGULAR_VELOCITY;

if ((scanTarget == 1) && (tangentPoints[2] >= tangentPoints[1]))
 scanTarget = -1;
else if ((scanTarget == -1) && (tangentPoints[2] <= tangentPoints[0]))
 scanTarget = 1;

target_pos[0] = getPanelSide() * 0.7;
target_pos[1] = myState[1];
target_pos[2] = myState[2];

SET_POSITION_TARGET(target_pos);

