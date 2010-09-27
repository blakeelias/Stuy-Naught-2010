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
 *        SPH1: X=0.7, Y=0, Z=0
 *        SPH2: X=0,   Y=0, Z=0
 *
 * Result codes:
 *    SPH1 = 20 (I won)
 *    SPH2 = 40 (Other sat won)
 *
 * Total time: 165 seconds
 *
 * Description of behavior:
 *    SPHERE 1 (blue) starts in the center of panel initialization circle
 *    (relies on initial positioning), turns towards solar panel (relies on
 *    initial panel position in Game Variables).  Moves forward, docks to panel,
 *    travels to station and docks panel to the station.
 *
 *    During trip from panel circle to the station, a near collision with the
 *    other SPHERE results in it moving away, using up its fuel.
 * 
 */

void ZRUser(float myState[12], float otherState[12], float time) {
    if (time < 150) {
        //TODO: move to center of panel initialization circle, instead of
        //assuming that position from the start
        float attitude[3] = {0, 1, 0};
        ZRSetAttitudeTarget(attitude);
        //TODO: rotate around the circle to find the panel; in this case,
        //panel angle is 0 so we automatically see it after the attitude change
        if (isPanelFound() && time > 20) {
            float velocity[3] = {0, 0.01, 0};
            ZRSetVelocityTarget(velocity);
        }
        if (iHavePanel() && time > 70 && time < 75) {
            float stop[3] = {0, 0, 0};
            ZRSetVelocityTarget(stop);
        }
        if (iHavePanel() && time > 75 && time < 150) {
            float station[3] = {-.7, 0, 0};
            ZRSetPositionTarget(station);
        }
    }
    if (iHavePanel() && time == 150) {
        float searchStation[3] = {0, 0.1, 0};
        ZRSetTorques(searchStation);
    }
    if (isStationInSync() && time > 150) {
        float stop[3] = {0, 0, 0};
        ZRSetTorques(stop);
        float velocity[3] = {0, 0, .01};
        ZRSetVelocityTarget(velocity);
    }
}
