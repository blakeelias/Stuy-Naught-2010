// Globals required:
// int stage = 0
// float dir[3]

/* 
Collision test function that lets you specify a point to collide from, and a velocity to collide at
mState and oState are the myState and otherState args that you must pass on to this function for it to work.
velMag is a scalar value for the magnitude of velocity you want to collide (or attempt to collide) at

-Abhimanyu Ghosh, 10/19/10 @ 01:03 a.m. EST

*/


void CollideFromPoint(float * mState, float * oState, float * fromPoint, float velMag) {

if (stage == 0) {
ZRSetPositionTarget(fromPoint);
if (Vfunc(6, mState, fromPoint, NULL, 0) < 0.09) {
stage = 1;
}
}

if (stage == 1) {

Vfunc(9, fromPoint, oState, dir, 0);
Vfunc(4, dir, NULL, dir, velMag);
ZRSetVelocityTarget(dir);
}

}
