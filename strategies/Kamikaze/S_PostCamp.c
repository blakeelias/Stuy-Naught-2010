
int j;
for (j = 0; j < 3; j++)
	target[j] = otherState[j] - myState[j];
target = Vfunc(3,target,NULL,target,0);
SET_ATTITUDE_TARGET(target);


if (VAngle(myState+6, otherState) < 12) {
    ZRRepel();
}

if (Vfunc(6, myState, otherState, NULL, 0) < 1){
	SET_POSITION_TARGET(otherState);
}

DEBUG(("should be zapping\n"));
