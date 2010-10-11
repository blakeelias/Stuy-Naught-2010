//Code to move to panel...

if (iHavePanel())
{
 state = STATE_TOSTATION;
 break;
}

SET_POSITION_TARGET(&panelState[4]);

float panelLoc[3];

VSub(panelState, &panelState[4], panelLoc);
VUnit(panelLoc, panelLoc);

SET_ATTITUDE_TARGET(panelLoc);

