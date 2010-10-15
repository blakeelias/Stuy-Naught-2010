/* int TaskAcquirePanel(int is_first_call)
 *
 * Phase 0: (when is_first_call == 1): set up the private ProcVars area (set Phase = 1)
 *
 * Phase 1: we're turning (with out-of-plane feedback control), looking for the panel.
 *    When we find it, we copy the panel's position and angle into ProcVars.
 *    Then we calculate a target position approx. 5 cm in front of the panel and 
 *    an orientation pointing toward the panel (panel staging area), 
 *    and set a course for that -> Phase 2
 *
 * Phase 2: we're going toward panel staging area. When we reach it with correct 
 *    orientation, -> Phase 3
 *
 * Phase 3: set a velocity of 1.2 cm/sec (a little less than the max allowed) toward
 *    the panel, and check whether we've acquired it.  Once acquired, we exit with
 *    new task ID
/*

// #include defines.h

#define P_AREA          10          // start of our private ProcVar elements
#define P_PHASE         (0+P_AREA)  // our current phase (1)
#define P_PANEL_POS     (1+P_AREA)  // panel position and angle (3)
#define P_PANEL_ANGLE   (4+P_AREA)  // panel angle in the YZ plane
#define P_STAGING_POS   (5+P_AREA)  // panel staging area position (3)
#define P_STAGING_ATT   (8+P_AREA)  // panel staging area orientation (3)

#define AngleForward	30

float hist_frame[H_FRAME], myState[12], otherState[12], rest[H_FRAME-24];
float temp[3], target_att[3], current_att[3], current_pos[3], panelState[4];
float current_theta, target_theta;
float position_tolerance = .02;  // 2 cm tolerance for being at the staging area (just a guess)

if (is_first_call)
    ProcVars[P_PHASE] = 1;

HistFunc(1,myState,otherState,rest,G_time);

if (ProcVars[P_PHASE] == 1) {

// -------------------- Turning, looking for the panel ---------------------
    // calculate the angle in the YZ-plane that we'll ask the system
    //   to target
    VCopy(myState+6,current_att);
    current_theta = atan2(current_att[2],current_att[1]);  // we're head this way
    if (current_theta < 0)
        current_theta = current_theta + 2*PI;
    target_theta = current_theta + Deg2Rad(AngleForward);

    // now calculate the vector along that angle, and make the request
    temp[0] = -5.0*current_att[0]; // out-of-plane correction
    temp[1] = cos(target_theta);
    temp[2] = sin(target_theta);
    VUnit(temp,target_att); // make into a unit vector
    ZRSetAttitudeTarget(target_att);

    // from here on is new code, not yet tested/debugged:

    if (!isPanelFound())
        return TASK_UNFINISHED;

    // OK, we've just found the panel.  Store its position...
    getPanelState(panelState);
    VCopy(panelState,ProcVars+P_PANEL_POS);
    ProcVars[P_PANEL_ANGLE] = panelState[3];

    // calculate the orientation of the staging position and store
    ProcVars[0+P_STAGING_ATT] = 0;
    ProcVars[1+P_STAGING_ATT] = cos(ProcVars[P_PANEL_ANGLE]);
    ProcVars[2+P_STAGING_ATT] = sin(ProcVars[P_PANEL_ANGLE]);

    // calculate the staging position, which is 5 cm in front of the panel
    // = panel position + -1 * 0.05 * staging orientation, then store
    VMult(ProcVars+P_STAGING_ATT, -0.05, temp);
    VAdd(ProcVars+P_PANEL_POS, temp, ProcVars+P_STAGING_POS);

    // request the new position and orientation
    ZRSetPositionTarget(ProcVars+P_STAGING_POS);
    ZRSetAttitudeTarget(ProcVars+P_STAGING_ATT);

    ProcVars[P_PHASE] = 2;
    return TASK_UNFINISHED;

}
else if (ProcVars[P_PHASE] == 2) {
    //  ----------------------------------------------------
    //      proceeding to the staging area, check if we're there, and also, if by chance,
    //   we've acquired the panel

    if (iHavePanel())
        return T_GOTO_STATION_CIRCLE;

    // are we at the staging area, and do we have the panel in cone, and are we in sync with the panel?
    VCopy(myState,current_pos);
    if (VDist(current_pos,ProcVars+P_STAGING_POS) <= position_tolerance && isPanelFound() && isPanelInSync()) {
        ProcVars[P_PHASE] = 3;
        return TASK_UNFINISHED;
    }

    // again: request the staging position and orientation
    ZRSetPositionTarget(ProcVars+P_STAGING_POS);
    ZRSetAttitudeTarget(ProcVars+P_STAGING_ATT);
    return TASK_UNFINISHED;

}
else if (ProcVars[P_PHASE] == 3) {
    // -------------------------------------------
    //  starting from the staging area, set the velocity toward to the panel at 1.2 cm/sec and hope for the best

    // got panel?
    if (iHavePanel())
        return T_GOTO_STATION_CIRCLE;

    // nope, set velocity toward panel at 1.2 cm/sec
    VCopy(myState,current_pos);                     // get the current position
    VPoint(current_pos,ProcVars+P_PANEL_POS,temp);  // get the unit vector pointing from here toward panel
    VMult(temp,0.012,target_att);                   // multiply that by 0.012 (1.2 cm/sec)
    ZRSetVelocityTarget(target_att);
    return TASK_UNFINISHED;
}

    
    
    
