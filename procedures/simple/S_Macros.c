

//Macros for functions used to set the position and attitude
//target. Change these if we ever make better versions.
#define SET_POSITION_TARGET ZRSetPositionTarget
#define SET_ATTITUDE_TARGET ZRSetAttitudeTarget

//The target distance from the center of the panel init circle.
//The satellite, upon starting, will move to the closest point
//on the plane of the panel init circle that is this many
//meters away from the center of the circle.
#define SEARCH_DISTANCE         0.7

//Rotation speed when searching for the panel. The satellite
//controls its rotation by setting its attitude target to a
//point this many radians away from its current attitude.
#define SEARCH_ANGULAR_VELOCITY 0.1

//The number of meters in front of a docking target that the
//satellite will move to.
#define DOCK_DISTANCE           0.03

//The satellite will always be drifting away from its position.
//If the satellite is less than this number of meters away from
//its target position, it will tolerate the error.
#define ERROR_TOLERANCE         0.1

//Add more states as necessary
#define STATE_INIT        0
#define STATE_PREP        1
#define STATE_CHARGE      2
#define STATE_ZAP         3
#define STATE_SEARCHING   4
#define STATE_TOPANEL     5
#define STATE_TOSTATION   6



//Avoid touching anything beyond this point
#define SQ(a) ((a) * (a))
#define PI  3.141592653589793238462

//Vfunc defines...
#define VLen(a)              Vfunc(0, (a), NULL, NULL, 0)
#define VAdd(a, b, result)   Vfunc(1, (a), (b), (result), 0)
#define VSub(a, b, result)   Vfunc(2, (a), (b), (result), 0)
#define VUnit(a, result)     Vfunc(3, (a), NULL, (result), 0)
#define VMult(a, b, result)  Vfunc(4, (a), NULL, (result), (b))
#define VDot(a, b)           Vfunc(5, (a), (b), NULL, 0)
#define VDist(a, b)          Vfunc(6, (a), (b), NULL, 0)
#define VCopy(a, result)     Vfunc(7, (a), NULL, (result), 0)
#define VAngle(a, b)         Vfunc(8, (a), (b), NULL, 0)
#define VPoint(a, b, result) Vfunc(9, (a), (b), (result), 0)


