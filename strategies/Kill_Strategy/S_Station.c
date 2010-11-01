//Code to beeline towards the station...

if (s2 - s1 == 0 && s2 > 0){
state = STATE_CAMP;
break;
}
else {
s1 = s2;
s2 = getOtherCurrentScore();
getStationState(station);

VCopy(station, target_att);

target_att[1] += cosf(station[3]) * DOCK_DISTANCE;
target_att[2] += sinf(station[3]) * DOCK_DISTANCE;

CoastToTarget(myState, target_att);

target_att[0] = 0;
target_att[1] = cosf(station[3]);
target_att[2] = sinf(station[3]);

SET_ATTITUDE_TARGET(target_att);
}
