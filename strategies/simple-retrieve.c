/*
 * Simulation settings:
 *    Simulate as: SPH1
 *    Maximum Time: 210 seconds
 *    Game Variables:
 *        initangle: 0
 *        panelangle: 0
 *        panelradius: 0.3
 *        havepanel: 0
 *    Positioning:
 *        SPH1: X=0, Y=0.3484, Z=0
 *        SPH2: X=0,   Y=-0.3484, Z=0
 *
 * Result codes:
 *    SPH1 = 20 (I won)
 *    SPH2 = 40 (Other sat won)
 *
 * Total time: 94.0 seconds
 * Fuel used: 67% (33% remaining)
 *
 * Description of behavior:
 *    SPHERE 1 (blue) starts in the satellite initialization circle, moves
 *    to solar panel initialization circle, and immediately sees the panel
 *    (relies on initial panel position).  Moves forward, docks to panel,
 *    travels to station and docks panel to the station.
 * 
 */

int state = 0;

void ZRUser(float * myState, float * otherState, float time) {
    printf("%d\n", state);
    
    if (state == 0) {
        float attitude[3] = {0, 1, 0};
        float panel_distance;
        float panel_center[3] = {.7, 0, 0};
        
        ZRSetPositionTarget(panel_center);
        ZRSetAttitudeTarget(attitude);
        
        panel_distance = Vfunc(6, myState, panel_center, NULL, 0);
        if (panel_distance < 0.01)
            state = 2;
    }
    //TODO: rotate around the circle to find the panel; in this case,
    //panel angle is 0 so we automatically see it after the attitude change
    if (state == 1);
    if (state == 2) {
        float attitude[3] = {0, 1, 0};
        ZRSetAttitudeTarget(attitude);
        if (isPanelFound()) {
            float velocity[3] = {0, 0.01, 0};
            ZRSetVelocityTarget(velocity);
        }
        if (iHavePanel())
            state = 3;
    }
    if (state == 3) {
        if (iHavePanel()) {
            float stop[3] = {0, 0, 0};
            float velocity_difference;
            ZRSetVelocityTarget(stop);
            velocity_difference = Vfunc(6, &myState[3], stop, NULL, 0);
            if (velocity_difference < 0.02)
                state = 4;
        }
    }
    if (state == 4) {
        if (iHavePanel()) {
            float station[3] = {-.7, 0, 0};
            float station_attitude[3] = {0, 0, 1};
            float station_distance;
            ZRSetPositionTarget(station);
            ZRSetAttitudeTarget(station_attitude);
            station_distance = Vfunc(6, myState, station, NULL, 0);
            if (station_distance < 0.01)
                state = 5;
        }
    }
    if (state == 5) {
        if (iHavePanel()) {
            float station_attitude[3] = {0, 0, 1};
            float station_position[3] = {-.7, 0, 0};
            ZRSetPositionTarget(station_position);
            ZRSetAttitudeTarget(station_attitude);
        }
    }
}
