//Code to move to panel...

if (iHavePanel())
{
 state = STATE_TOSTATION;
 break;
}

SET_POSITION_TARGET(&panelState[4]);

VSub(panelState, &panelState[4], target);
VUnit(target, target);

SET_ATTITUDE_TARGET(target);

