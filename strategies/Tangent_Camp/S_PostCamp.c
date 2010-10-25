target[0] = getPanelSide()*0.7;
target[1] = target[2] = 0;

SET_POSITION_TARGET(target);

target[0] = getPanelSide();
SET_ATTITUDE_TARGET(target);

ZRRepel();

DEBUG(("should be zapping\n"));
