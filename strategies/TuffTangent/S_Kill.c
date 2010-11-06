//Camps and zaps the opponent forever.

VCopy(otherState, target);
VUnit(target);

SET_ATTITUDE_TARGET(target);

VMult(target, 0.1, target);

CoastToTarget(myState, target);

if (VAngle(myState, otherState) < 6.0f)
 ZRRepel();

