//Code to beeline towards the station...

getStationState(station);

VCopy(station, target);

target[1] += cosf(station[3]) * 0.4;
target[2] += sinf(station[3]) * 0.4;

SET_POSITION_TARGET(target);

target[0] = 0;
target[1] = -cosf(station[3]);
target[2] = -sinf(station[3]);

SET_ATTITUDE_TARGET(target);

