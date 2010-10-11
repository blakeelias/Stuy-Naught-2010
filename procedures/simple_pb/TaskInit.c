/* int TaskInit()
 *
 * sets ProcVars[0]: result of getPanelSide()
*/

// return values from Task functions:
#define TASK_FINISHED   1
#define TASK_UNFINISHED 0

ProcVars[0] = getPanelSide();
printf("time: %d, T_Init() finished\n",G_time);
return TASK_FINISHED;

