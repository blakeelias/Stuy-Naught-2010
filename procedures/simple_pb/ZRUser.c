/* This is the main code for ZRUser()
*/

// include defines.h

int timeOffset = 0;     // non-zero for ISS, 0 for simulation
int task_result;

G_time = time - timeOffset;
HistFunc(0,myState,otherState,NULL,G_time); // save properties

printf("time: %d, G_state: %d\n",G_time,G_state);

if (G_state == T_INIT)
    task_result = TaskInit();
else if (G_state == T_GOTO_PANEL_CIRCLE)
    task_result = TaskGoToPanelCircle();
else if (G_state == T_ACQUIRE_PANEL)
     task_result = TaskAcquirePanel();
else if (G_state == T_GOTO_STATION_CIRCLE)
    task_result = TaskGotoStationCircle();
else if (G_state == T_DOCK_TO_STATION)
    task_result = TaskDockToStation();

// if task is finished, then use task_result to choose the next task
if (task_result != TASK_UNFINISHED)
    G_state = task_result;


