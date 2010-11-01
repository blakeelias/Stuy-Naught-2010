//Code to beeline towards the station...

#define targetX (getPanelSide() * 0.7)

target[0] = targetX;
target[1] = target[2] = 0;

CoastToTarget(myState, target);


