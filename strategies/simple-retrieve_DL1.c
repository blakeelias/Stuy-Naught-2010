 /*
 * Simulation settings:
 *    Simulate as: SPH1
 *    Maximum Time: 210 seconds
 *    Game Variables: generate from game
 *    Positioning: set from game variables
 *
 * Result codes:
 *    SPH1 = 20
 *    SPH2 = 40
 *
 * Other results:
 *    Total time elapsed: 114 seconds
 *    Fuel remaining: 18%
 */
/*
int state = 0;
float [100];

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
    #define Deg2Rad(Deg)    (Deg*PI/180.0)
    #define Rad2Deg(Rad)    (Rad*180.0/PI)

    // do ZRSetAttitudeTarget(current_att + AngleForward)
    #define AngleForward    30

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
 */   
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

    #define Deg2Rad(Deg)    (Deg*PI/180.0)
    #define Rad2Deg(Rad)    (Rad*180.0/PI)
    

    
        float panel_center[3];
    	float panel_center_distance;
        float panel_location[4];
    	float attitude[3];
        float attitude_rate;
        float station[3];
        float station_attitude[3];
        float station_position[3];
        float station_distance;
    procvar[0] = time;
 	
   // printf("time: %3.0f, state: %d, pos: (%5.2f, %5.2f, %5.2f), ",
           //time, state, myState[0], myState[1], myState[2]);
    //printf("att: (%5.2f, %5.2f, %5.2f), panel: %d, ",
           //myState[6], myState[7], myState[8], isPanelInSync());
    
    
    if (state == 0) {
        /*float attitude[3] = {0, 1, 0};*/
        attitude[0] = 0;
        attitude[1] = 1*getPanelState();
        attitude[2] = 0;

        /*float panel_center[3] = {.7*getPanelSide(), 0, 0};*/
        panel_center[0] = .7*getPanelSide();
        panel_center[1] = 0;
        panel_center[2] = 0;
    	
        /*if ( time < 12 ) {
        float temp[3] = {.7*getPanelSide(), 0, 0};   //DL change face panel init center for 15 sec
        Vfunc(9,myState, temp, attitude,0);
             }*/   //rjected -- uses too much fuel
            
        ZRSetPositionTarget(panel_center);
        ZRSetAttitudeTarget(attitude);     
                
        panel_center_distance = Vfunc(6, myState, panel_center, NULL, 0);
        if (panel_center_distance < 0.05)  // original value .01, tried .05
            state = 1;
       /*   
    if (isPanelFound()) {
        printf("panel found early at %5.2f\n", time);
            state = 2;       // DL change
            }*/
    }
    if (state == 1) {
        /*float panel_center[3] = {.7*getPanelSide(), 0, 0};*/
        panel_center[0] = .7*getPanelSide();
        panel_center[1] = 0;
        panel_center[2] = 0;

        RotateTarget(myState, panel_center);
        if (isPanelFound())
            state = 2;
    }
    if (state == 2) {
        /*float panel_center[3] = {.7*getPanelSide(), 0, 0};*/
        panel_center[0] = .7*getPanelSide();
        panel_center[1] = 0;
        panel_center[2] = 0;

        ZRSetPositionTarget(panel_center);
        if (isPanelFound()) {
            getPanelState(panel_location);
            procvar[20] = panel_location[0];
            procvar[21] = panel_location[1];
            procvar[22] = panel_location[2];
            VCopy(procvar+20,procvar+23); // DL store position data
            Vfunc(9, myState, procvar+20, procvar+20, 0);
            ZRSetAttitudeTarget(procvar+20);
            state = 3;
        }
    }
    if (state == 3) {
        ZRSetAttitudeTarget(procvar+20);
        attitude_rate = Vfunc(0, myState+9, NULL, NULL, 0);
        //printf("att_rate: %3.5f\n", attitude_rate);
        if (isPanelFound())
            procvar[30]++;
        else procvar[30] = 0;
        if (procvar[30] > 10)
            state = 4;
    }
    if (state == 4) {
        ZRSetAttitudeTarget(procvar+20);
        if (isPanelFound()) {
          //  float velocity[3];
          //  Vfunc(4, procvar+20, NULL, velocity, .01);
           // ZRSetVelocityTarget(velocity);
           ZRSetPositionTarget(procvar+23);  //DL change
        }
        if (iHavePanel())
            state = 5;
    }
    if (state == 5) {
        if (iHavePanel()) {
            /*float station[3] = {-.7*getPanelSide(), 0, 0};*/
            station[0] = -.7*getPanelSide();
            station[1] = 0;
            station[2] = 0;

            /*float station_attitude[3] = {0, 0, 1*getPanelSide()};*/
            station_attitude[0] = 0;
            station_attitude[1] = 0;
            station_attitude[2] = 1*getPanelSide();

            ZRSetPositionTarget(station);
            ZRSetAttitudeTarget(station_attitude);
            station_distance = Vfunc(6, myState, station, NULL, 0);
            if (station_distance < 0.01)
                state = 6;
        }
    }
    if (state == 6) {
        if (iHavePanel()) {
            /*float station_attitude[3] = {0, 0, 1*getPanelSide()};*/
            station_attitude[0] = 0;
            station_attitude[1] = 0;
            station_attitude[2] = 1*getPanelSide();

            /*float station_position[3] = {-.7*getPanelSide(), 0, 0};*/
            station_position[0] = -.7*getPanelSide();
            station_position[1] = 0;
            station_position[2] = 0;

            ZRSetPositionTarget(station_position);
            ZRSetAttitudeTarget(station_attitude);
        }
    }
    
   // if (time == 0) printf("time,state,X position, panel found, in sync ,docked, fuel\n");
   // printf("%3.0f, %d, %5.3f, %d, %d, %d, %5.3f\n",  time, state, myState[0],isPanelFound(),isPanelInSync(),iHavePanel(),getPercentFuelRemaining());
	
