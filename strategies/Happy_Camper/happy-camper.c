
int state = 0;
float procvar[4] = 0;

void RotateTarget(float * myState, float * pos) {
    #define VLen(a)              Vfunc(0, (a), NULL, NULL, 0)
    #define VAdd(a, b, result)   Vfunc(1, (a), (b), (result), 0)
    #define VSub(a, b, result)   Vfunc(2, (a), (b), (result), 0)
    #define VUnit(a, result)     Vfunc(3, (a), NULL, (result), 0)
    #define VMult(a, b, result)  Vfunc(4, (a), NULL, (result), (b))
    #define VDot(a, b)           Vfunc(5, (a), (b), NULL, 0)
    #define VDist(a, b)          Vfunc(6, (a), (b), NULL, 0)
    #define VCopy(a, result)     Vfunc(7, (a), NULL, (result), 0)
    #define VAngle(a, b)         Vfunc(8, (a), (b), NULL, 0)
    #define VPoint(a, b, result) Vfunc(9, (a), (b), (result), 0)

    #define PI 3.14159265
    #define Deg2Rad(Deg)	(Deg*PI/180.0)
    #define Rad2Deg(Rad)	(Rad*180.0/PI)

    // do ZRSetAttitudeTarget(current_att + AngleForward)
    #define AngleForward	30

    float temp[3], target_att[3], current_att[3];
    float current_theta, target_theta;

    ZRSetPositionTarget(pos);

    VCopy(myState+6,current_att);
    current_theta = atan2(current_att[2],current_att[1]);
    if (current_theta < 0)
        current_theta = current_theta + 2*PI;
    target_theta = current_theta + Deg2Rad(AngleForward);

    temp[0] = -5.0*current_att[0];
    temp[1] = cos(target_theta);
    temp[2] = sin(target_theta);
    VUnit(temp,target_att);

    //printf("time: %2.0f, current_att: (%5.2f, %5.2f, %5.2f), target: (%5.2f, %5.2f, %5.2f), to_target: %5.1f",
    //procvar[0],current_att[0],current_att[1],current_att[2],target_att[0],target_att[1],target_att[2],
    //VAngle(current_att,target_att));
    //printf(" rates: (%5.2f, %5.2f, %5.2f)\n", myState[9],myState[10],myState[11]);
    //printf( " out-of-plane: %5.2f\n",asin(current_att[0])*180/3.14159);

    ZRSetAttitudeTarget(target_att);
}

void ZRUser(float * myState, float * otherState, float time) {
    printf("time: %3.0f, state: %d, pos: (%5.2f, %5.2f, %5.2f), ",
           time, state, myState[0], myState[1], myState[2]);
    printf("att: (%5.2f, %5.2f, %5.2f), panel: %d, ",
           myState[6], myState[7], myState[8], isPanelInSync());
    
    if (state == 0) {
        float attitude[3] = {0, 1, 0};
        float panel_center_distance;
        float panel_center[3] = {.7*getPanelSide(), 0, 0};
        
        ZRSetPositionTarget(panel_center);
        ZRSetAttitudeTarget(attitude);
        
        panel_center_distance = Vfunc(6, myState, panel_center, NULL, 0);
        if (panel_center_distance < 0.01)
            state = 1;
    }
    if (state == 1) {
        float panel_center[3] = {.7*getPanelSide(), 0, 0};
        RotateTarget(myState, panel_center);
        if (isPanelFound())
            state = 2;
    }
    if (state == 2) {
        float panel_center[3] = {.7*getPanelSide(), 0, 0};
        float panel_location[4];
        ZRSetPositionTarget(panel_center);
        if (isPanelFound()) {
            getPanelState(panel_location);
            procvar[0] = panel_location[0];
            procvar[1] = panel_location[1];
            procvar[2] = panel_location[2];
            Vfunc(9, myState, procvar, procvar, 0);
            ZRSetAttitudeTarget(procvar+1);
            state = 3;
        }
    }
    if (state == 3) {
        float attitude_rate;
        ZRSetAttitudeTarget(procvar);
        attitude_rate = Vfunc(0, myState+9, NULL, NULL, 0);
        printf("att_rate: %3.5f\n", attitude_rate);
        if (isPanelFound())
            procvar[3]++;
        else procvar[3] = 0;
        if (procvar[3] > 10)
            state = 4;
    }
    if (state == 4) {
        ZRSetAttitudeTarget(procvar);
        if (isPanelFound()) {
            float velocity[3];
            Vfunc(4, procvar, NULL, velocity, .01);
            ZRSetVelocityTarget(velocity);
        }
        if (iHavePanel())
            state = 5;
    }
    if (state == 5){
      procvar[1] = -.2 * getPanelSide();
      procvar[2] = 0;
      procvar[3] = 0;
      ZRSetPosition(procvar + 1);
      procvar[1] -= myState[0];
      procvar[2] = myState[1];
      procvar[3] = myState[2];
      if (Vfunc(0,procvar[1],NULL,NULL,0) < .01)
	state = 6;
    }
    if (state == 6){
      procvar[1] = getPanelSide();
      procvar[2] = 0;
      procvar[3] = 0;
      ZRSetAttitudeTarget(procvar[1]);
      //should change state if:
      //  done charging
      //  opponent breaks plane
}
