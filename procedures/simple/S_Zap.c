float target_pos[3] = {0.7,0,0};
float current_pos[3], target_att[3], to_opponent[3];
float sun[3] = {0,0,0};
float tolerance=.02; // 2 cm

if (time == 0)
    phase = 0;

    // ============================== ACTIVE ===========================
    //printf("time: %4.1f, phase: %d\n",time, phase);
    if (phase == 0) { // go to panel center charging
        if (VDist(myState,target_pos) < tolerance && getPercentChargeRemaining() >= 95) {
            phase = 1;
        } else {
            // calc vector from current position back toward sun
            VPoint(sun,myState,target_att);
            ZRSetPositionTarget(target_pos);
            ZRSetAttitudeTarget(target_att);
        }
    }
    else if (phase == 1) { // completely charged, now turn to face the PASSIVE one
        ZRSetPositionTarget(target_pos);
        VPoint(myState,otherState,to_opponent);
        if (VAngle(to_opponent,myState+6) < 5 && getPercentChargeRemaining() > 0) {
printf("time: %4.0f, (BLUE): ZAPPING ++++++++++++++++++++\n",time);
            ZRRepel();
        }
        else {
            VPoint(myState,otherState,to_opponent);
printf("time: %4.0f, (BLUE): angle to opponent: %f\n",time,VAngle(to_opponent,myState+3));
            ZRSetAttitudeTarget(to_opponent);
    }
}




