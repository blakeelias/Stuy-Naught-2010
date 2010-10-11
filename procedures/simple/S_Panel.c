//Code to move to panel...

if (iHavePanel())
{
 state = STATE_TOSTATION;
 break;
}

SET_POSITION_TARGET(panelState);

//Insert math that points the satellite outwards...
