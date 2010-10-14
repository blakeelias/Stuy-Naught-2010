/*
 * Simulation settings:
 *    Simulate as: SPH1
 *    Maximum Time: 20 seconds
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
 *    SPH1 = 0
 *    SPH2 = 0
 *
 * 
 */

int state = 0;
float history[7596];
float procvar[1000];
float G_time = 0;

void ZRUser(float * myState, float * otherState, float time) {
    float history_portion[36];
    int i;
    HistFunc(0, myState, otherState, NULL, time);
    HistFunc(1, history_portion, &history_portion[12], &history_portion[24], time);
    
    for(i = 0; i < 36; i++) {
        printf("%f", history_portion[i]);
        if (i-35) printf(",");
        else printf("\n");
    }
    
    if (state == 0) {
        float attitude[3] = {0, 1, 0};
        float panel_center_distance;
        float panel_center[3] = {.7, 0, 0};
        
        ZRSetPositionTarget(panel_center);
        ZRSetAttitudeTarget(attitude);
        
        panel_center_distance = Vfunc(6, myState, panel_center, NULL, 0);
        if (panel_center_distance < 0.01)
            state = 1;
    }
    if (state == 1) {
        float panel_center[3] = {.7, 0, 0};
        //float search[3] = {0, 0.01, 0};
        float search_attitude[3] = {0, 0, -1};
        ZRSetPositionTarget(panel_center);
        ZRSetAttitudeTarget(search_attitude);
        //ZRSetTorques(search);
        if (isPanelFound())
            state = 2;
    }
    if (state == 2) {
        float panel_center[3] = {.7, 0, 0};
        ZRSetPositionTarget(panel_center);
        if (isPanelFound()) {
            HistRetrieve(&procvar[200], time, 6, 3);
            ZRSetAttitudeTarget(&procvar[200]);
            state = 3;
        }
    }
    if (state == 3) {
        float attitude_rate;
        ZRSetAttitudeTarget(&procvar[200]);
        attitude_rate = Vfunc(0, &procvar[200], NULL, NULL, 0);
        if (isPanelFound() && attitude_rate < 0.01)
            state = 4;
    }
    if (state == 4) {
        float attitude[3] = {0, 1, 0};
        ZRSetAttitudeTarget(attitude);
        if (isPanelFound()) {
            float velocity[3] = {0, 0.01, 0};
            ZRSetVelocityTarget(velocity);
        }
        if (iHavePanel())
            state = 5;
    }
    if (state == 5) {
        if (iHavePanel()) {
            float station[3] = {-.7, 0, 0};
            float station_attitude[3] = {0, 0, 1};
            float station_distance;
            ZRSetPositionTarget(station);
            ZRSetAttitudeTarget(station_attitude);
            station_distance = Vfunc(6, myState, station, NULL, 0);
            if (station_distance < 0.01)
                state = 6;
        }
    }
    if (state == 6) {
        if (iHavePanel()) {
            float station_attitude[3] = {0, 0, 1};
            float station_position[3] = {-.7, 0, 0};
            ZRSetPositionTarget(station_position);
            ZRSetAttitudeTarget(station_attitude);
        }
    }
    
    //G_time += 1;
}
