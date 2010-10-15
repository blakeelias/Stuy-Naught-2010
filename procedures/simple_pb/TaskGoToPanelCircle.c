/* int TaskGoToPanelCircle()
 *
 * Travel from birthplace to center of panel circle and stop.
 * and rotate to point toward +Y axis.
*/

// include defines.h

float target_pos[3] = {0,0,0};
float target_att[3] = {0,0,0};

// how close to the target when finished
float pos_tolerance = .01;
float myState[12],otherState[12],rest[12],current_pos[3], current_att[3];
float current_dist, angle_from_desired;

// set the target position
target_pos[0] = ProcVars[0] * 0.7;  // ProcVars[0] was set by TaskInit()

// set target attitude
target_att[1] = ProcVars[0];

// calculate the distance from the target
HistFunc(1,myState,otherState,rest,G_time);
Vfunc(7,myState,NULL,current_pos,0);
current_dist = Vfunc(6,current_pos,target_pos,NULL,0);

// calculate the angle difference to desired angle
Vfunc(7,myState+6,NULL,current_att,0);
angle_from_desired = Vfunc(8,current_att,target_att,NULL,0);

printf("distance to panel circle: %f, degrees to go: %f\n",current_dist,angle_from_desired);
if (current_dist <= pos_tolerance) {
    printf("time: %d, TaskGoToPanelCircle finished. Fuel: %5.2f, Charge: %5.2f\n",
        G_time,getPercentFuelRemaining(),getPercentChargeRemaining());
    return T_ACQUIRE_PANEL;
}
else {
    ZRSetPositionTarget(target_pos);
    ZRSetAttitudeTarget(target_att);
    return TASK_UNFINISHED;
}

