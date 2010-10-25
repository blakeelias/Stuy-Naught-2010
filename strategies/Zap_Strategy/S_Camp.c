//Code to beeline towards the station...

target[0] = myState[0];
target[1] = myState[1];
target[2] = myState[2];

CoastToTarget(myState, target);
SET_ATTITUDE_TARGET(target);


