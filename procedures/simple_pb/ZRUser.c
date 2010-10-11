/* This is the main code for ZRUser()
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

int timeOffset = 0;     // non-zero for ISS, 0 for simulation
int i, task_result;

G_time = time - timeOffset;
HistFunc(0,myState,otherState,NULL,G_time); // save properties

// main loop
for (i = 0; i < 2; ++i) {
printf("time: %d, G_state: %d\n",G_time,G_state);
    if (G_state == T_INIT)
        task_result = TaskInit();
    else if (G_state == T_GOTO_PANEL_CIRCLE)
        task_result = TaskGoToPanelCircle();
    else if (G_state == T_POINT_TOWARD_PANEL_AND_STOP)
        task_result = TaskPointTowardPanelAndStop();
    else if (G_state == T_ACQUIRE_PANEL)
        task_result = TaskAcquirePanel();
    else if (G_state == T_GOTO_STATION_CIRCLE)
        task_result = TaskGotoStationCircle();
    else if (G_state == T_DOCK_TO_STATION)
        task_result = TaskDockToStation();

    // if task is unfinished, then we're done for this second.
    if (task_result == TASK_UNFINISHED)
        break;

    // if task is finished, then figure out new state and go again
    if (G_state == T_INIT)
        G_state = T_GOTO_PANEL_CIRCLE;
    else if (G_state == T_GOTO_PANEL_CIRCLE)
        G_state = T_POINT_TOWARD_PANEL_AND_STOP;
    else if (G_state == T_POINT_TOWARD_PANEL_AND_STOP)
        G_state = T_ACQUIRE_PANEL;
    else if (G_state == T_ACQUIRE_PANEL)
        G_state = T_GOTO_STATION_CIRCLE;
    else if (G_state == T_GOTO_STATION_CIRCLE)
        G_state = T_DOCK_TO_STATION;
}

