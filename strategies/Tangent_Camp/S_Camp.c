//Camping out state

target_pos[0] = getPanelSide() * 0.1;
target_pos[1] = 0;
target_pos[2] = 0;

target_att[0] = getPanelSide();
target_att[1] = 0;
target_att[2] = 0;

CoastToTarget(myState, target_pos);
ZRSetAttitudeTarget(target_att);
