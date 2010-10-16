

//Macros for functions used to set the position and attitude
//target. Change these if we ever make better versions.
#define SET_POSITION_TARGET ZRSetPositionTarget
#define SET_ATTITUDE_TARGET ZRSetAttitudeTarget

//Target distance from center of panel init circle
#define SEARCH_DISTANCE         0.7
//Rotation speed when searching for panel
#define SEARCH_ANGULAR_VELOCITY 0.2

//Add more states as necessary
#define STATE_INIT        0
#define STATE_PREP        1
#define STATE_SEARCHING   2
#define STATE_TOPANEL     3
#define STATE_TOSTATION   4



//Don't touch anything beyond this point
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


