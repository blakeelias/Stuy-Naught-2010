ZRSetPositionTarget(target_pos);
VPoint(myState,otherState,to_opponent);
if (VAngle(to_opponent,myState+6) < 5 && getPercentChargeRemaining() > 0) {
    printf("time: %4.0f, (BLUE): ZAPPING ++++++++++++++++++++\n",time);
    ZRRepel();
}
else {
    if (getPercentChargeRemaining() < 1) {
        state = STATE_SEARCHING;
        break;
    }
    VPoint(myState,otherState,to_opponent);
    printf("time: %4.0f, (BLUE): angle to opponent: %f\n",time,VAngle(to_opponent,myState+3));
    ZRSetAttitudeTarget(to_opponent);
}
