//Code to move to panel...

if (iHavePanel())
{
 state = STATE_ZAP;
 scanTarget = 0;
 break;
}

SET_POSITION_TARGET(&panelState[4]);

VCopy(panelState, target);
target[0] = 0;
VUnit(target, target);

SET_ATTITUDE_TARGET(target);

