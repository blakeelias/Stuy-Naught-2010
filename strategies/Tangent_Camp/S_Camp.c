//Code to go camping towards the center

DEBUG(("currently camping\n"));
if (VAngle(myState+6, otherState) < 12) {
    state = STATE_POSTCAMP;
}
target[0] = getPanelSide()*0.1;
target[1] = target[2] = 0;

SET_POSITION_TARGET(target);

target[0] = getPanelSide();
SET_ATTITUDE_TARGET(target);
