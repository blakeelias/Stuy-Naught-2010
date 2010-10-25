//Code to beeline towards the station...

target[0] = getPanelSide()*0.1;
target[1] = target[2] = 0;

CoastToTarget(myState, target);

if (VAngle(myState+6, otherState) < 40) {
    VPoint(myState, otherState, target);
    SET_ATTITUDE_TARGET(target);
    ZRRepel();
    DEBUG(("should be zapping\n"));
}
else {
    target[0] = getPanelSide();
    target[1] = target[2] = 0;
    SET_ATTITUDE_TARGET(target);
}


