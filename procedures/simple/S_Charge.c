float target_pos[3] = {getPanelSide()*0.7,0,0};
float current_pos[3], target_att[3], to_opponent[3];
float sun[3] = {0,0,0};
float tolerance=.02;

if (getPercentChargeRemaining() >= 95) {
    state = STATE_ZAP;
} else {
    // calc vector from current position back toward sun
    VPoint(sun,myState,target_att);
    ZRSetPositionTarget(target_pos);
    ZRSetAttitudeTarget(target_att);
}
