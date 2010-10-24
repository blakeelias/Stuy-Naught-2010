//Code to move to panel...

if (iHavePanel())
{
 state = STATE_CAMP;
 scanTarget = 0;
 break;
}

SET_POSITION_TARGET(&panelState[4]);

VCopy(panelState, target_pos);
target_pos[0] = 0;
VUnit(target_pos, target_pos);

SET_ATTITUDE_TARGET(target_pos);

