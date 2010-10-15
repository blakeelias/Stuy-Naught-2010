/* int TaskInit()
 *
 * sets ProcVars[0]: result of getPanelSide()
*/

ProcVars[0] = getPanelSide();
printf("time: %d, T_Init() finished\n",G_time);
return T_GOTO_PANEL_CIRCLE;

