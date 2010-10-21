if (getPercentChargeRemaining() >= 95) {
    state = STATE_ZAP;
} else {
    // calc vector from current position back toward sun
    VPoint(sun,myState,target_att);
    ZRSetPositionTarget(target_pos);
    ZRSetAttitudeTarget(target_att);
}
