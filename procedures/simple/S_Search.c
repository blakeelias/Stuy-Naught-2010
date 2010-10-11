//Code to search for panel...

SET_ATTITUDE_TARGET(&tangentPoints[3]);

if (isPanelFound())
{
 getPanelState(panelState);

 state = STATE_TOPANEL;
 break;
}
