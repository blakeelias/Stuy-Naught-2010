

//Macros for functions used to set the position and attitude
//target. Change these if we ever make better versions.
#define SET_POSITION_TARGET ZRSetPositionTarget
#define SET_ATTITUDE_TARGET ZRSetAttitudeTarget

//Use of SEARCH_DISTANCE has been discontinued and will be
//removed soon.
#define SEARCH_DISTANCE         0.8

//Rotation speed when searching for the panel. The satellite
//controls its rotation by setting its attitude target to a
//point this many radians away from its current attitude.
#define SEARCH_ANGULAR_VELOCITY 0.15

//The number of meters in front of a docking target that the
//satellite will move to.
#define DOCK_DISTANCE           0.03

//The satellite will always be drifting away from its position.
//If the satellite is less than this number of meters away from
//its target position, it will tolerate the error.
#define ERROR_TOLERANCE         0.1

//How close is "close to my target" for CoastToTarget?
#define CLOSE                   0.1

//Magnitude of the set velocity with CoastToTarget
#define MAGNITUDE 0.03

//Add more states as necessary
#define STATE_INIT        0
#define STATE_PREP        1
#define STATE_SEARCHING   2
#define STATE_TOPANEL     3
#define STATE_TOSTATION   4



//Avoid touching anything beyond this point
#define SQ(a) mathSquare(a)

//Vfunc defines...
#define VLen(a)              mathVecMagnitude((a), 3)
#define VAdd(a, b, result)   mathVecAdd((result), (a), (b), 3)
#define VSub(a, b, result)   Vfunc(2, (a), (b), (result), 0)
#define VUnit(a)             mathVecNormalize((a), 3)
#define VMult(a, b, result)  Vfunc(4, (a), NULL, (result), (b))
#define VDot(a, b)           mathVecInner((a), (b), 3)
#define VDist(a, b)          Vfunc(6, (a), (b), NULL, 0)
#define VCopy(a, result)     memcpy((result), (a), 3 * sizeof(float))
#define VAngle(a, b)         Vfunc(8, (a), (b), NULL, 0)
#define VPoint(a, b, result) Vfunc(9, (a), (b), (result), 0)


