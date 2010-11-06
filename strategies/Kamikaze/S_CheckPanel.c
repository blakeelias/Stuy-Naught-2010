//Check if panel was found.

if (isPanelFound())
{
 getPanelState(panelState);


 panelState[4] = panelState[0];

 baseAngle = atan2f(panelState[2], panelState[1]);
 baseRadius = sqrtf(SQ(panelState[1]) + SQ(panelState[2])) - DOCK_DISTANCE;

 panelState[5] = cosf(baseAngle) * baseRadius;
 panelState[6] = sinf(baseAngle) * baseRadius;

 state = STATE_TOPANEL;
 break;
}

