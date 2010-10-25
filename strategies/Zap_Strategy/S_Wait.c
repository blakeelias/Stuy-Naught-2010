//Code to wait for the opponent to get into their panel's plane

#define otherTargetX (getPanelSide() * -0.7)

VPoint(myState,otherState,to_opponent);



if(fabs(otherState[0] - otherTargetX > .13)){
	state = STATE_SEARCHING;
	break;
}
else {
	ZRSetAttitudeTarget(to_opponent);	
	if(fabs(otherState[0] - otherTargetX) < .005){
		state = STATE_ZAP;
		break;
	}
}
	
