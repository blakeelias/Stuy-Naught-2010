//Code to wait for the opponent to get into their panel's plane

#define otherTargetX (getPanelSide() * -0.7)

VPoint(myState,otherState,to_opponent);

ZRSetAttitudeTarget(to_opponent);

if(otherState[0] == otherTargetX){
	state = STATE_ZAP;
	break;
}
	