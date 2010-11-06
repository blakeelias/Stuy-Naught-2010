//Code to beeline towards the station...

getStationState(station);

VCopy(station, target);

target[1] += cosf(station[3]) * DOCK_DISTANCE;
target[2] += sinf(station[3]) * DOCK_DISTANCE;

CoastToTarget(myState, target);

target[0] = 0;
target[1] = cosf(station[3]);
target[2] = sinf(station[3]);

SET_ATTITUDE_TARGET(target);

