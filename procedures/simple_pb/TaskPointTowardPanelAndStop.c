/* int TaskPointTowardPanelAndStop(int is_first_time)
 *
 * rotate to point to Panel, then stop
*/

// return values from Task functions:
#define TASK_FINISHED   1
#define TASK_UNFINISHED 0

// Task numbers for G_state
#define T_INIT                          0
#define T_GOTO_PANEL_CIRCLE             1
#define T_POINT_TOWARD_PANEL_AND_STOP   2
#define T_ACQUIRE_PANEL                 3
#define T_GOTO_STATION_CIRCLE           4
#define T_DOCK_TO_STATION               5

#define INDEX_PHASE 10    // ProcVars position: 1 == rotation phase, 2 = stopping
#define ROTATING 1
#define STOPPING 2
#define INDEX_TARGET_ATT    11  //  ProcVars position where panel's target att is stored
#define INDEX_PANEL_STATE   14  // ProcVars position of 4 floats returned by getPanelState()

#define YES 1
#define NO  0

float pulse_att[3] = {0,0,1}; // fire a rotation pulse toward this attitude
float myState[12], otherState[12], rest[12], current_att[3], previous_att[3], target_att[3];
float angle_diff;

// if this is the first time this function is called, then start the rotation
if (is_first_time == YES) {

    // don't rotate at all if we happen to be facing the panel
    if (isPanelFound() == 1) {
        printf("time: %d, Luckily pointing to panel without rotation. TaskPointTowardPanelAndStop finished\n",G_time);
        return TASK_UNFINISHED;
    }
    
    // we came here pointing to +-Y-axis.  Ask to point to +Z-axis.  Give one pulse.
    ZRSetAttitudeTarget(pulse_att);
    ProcVars[INDEX_PHASE] = ROTATING;
    printf("starting to rotate\n");
    return TASK_FINISHED;
}
else {  // rotation has started
    // get previous attitude
    HistFunc(1,myState,otherState,rest,G_time-1);
    Vfunc(7,myState+6,NULL,previous_att,0);

    // get current attitude
    HistFunc(1,myState,otherState,rest,G_time);
    Vfunc(7,myState+6,NULL,current_att,0);

    // calc angle traveled
    angle_diff = Vfunc(8,previous_att,current_att,NULL,0);

    printf("degrees rotated: %4.1f\n",angle_diff);

    if (ProcVars[INDEX_PHASE] == ROTATING) {
        if (isPanelFound() == 1) {
            // FOUND!, store this attitude into ProcVars
            Vfunc(7,current_att,NULL,ProcVars+INDEX_TARGET_ATT,0);

            // get the Panel's state, and store into ProcVars
            getPanelState(ProcVars+INDEX_PANEL_STATE);

            // change phase
            ProcVars[INDEX_PHASE] = STOPPING;

            // start reverse rotation to stop
            ZRSetAttitudeTarget(ProcVars+INDEX_TARGET_ATT);

            // wait at least one second
            return TASK_UNFINISHED;
        }
        else {  // Rotating, but not yet found: do nothing (that I can think of now)
            return TASK_UNFINISHED;
        }
    }
    else {  // STOPPING: we'll have code here in case we need to control the stopping
            // but for now, we'll just say we're done, and the stopping will be
            // done by the next Task
        return TASK_FINISHED;
    }
}
return TASK_FINISHED;

