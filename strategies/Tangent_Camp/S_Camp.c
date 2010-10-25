//Code to beeline towards the station...

target[0] = getPanelSide()*0.1;
target[1] = target[2] = 0;

CoastToTarget(myState, target);

target[0] = getPanelSide();

SET_ATTITUDE_TARGET(target);

