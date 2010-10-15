// GENERAL DEFINES 

// return value from Task functions:
#define TASK_UNFINISHED 0

// Task numbers
#define T_INIT                          1
#define T_GOTO_PANEL_CIRCLE             2
#define T_ACQUIRE_PANEL                 3
#define T_GOTO_STATION_CIRCLE           4
#define T_DOCK_TO_STATION               5

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

// Angle functions
#define PI 3.14159265
#define Deg2Rad(Deg)	(Deg*PI/180.0)
#define Rad2Deg(Rad)	(Rad*180.0/PI)

// HistFunc constants
#define H_FRAME         37

#define H_MYSTATE       0
#define H_OTHERSTATE    12

#define H_IHAVEPANEL    24
#define H_OTHERHASPANEL 25
#define H_ISPANELFOUND  26
#define H_ISPANELINSYNC 27
#define H_ISSTATIONINSYNC   28
#define H_CURRENTSCORE  29
#define H_OTHERCURRENTSCORE     30
#define H_PERCENTCHARGEREMAINING    31
#define H_PERCENTFUELREMAINING  32
#define H_OTHERREPELLING    33
#define H_OUTSIDEBOUNDARY   34
#define H_OPPONENTINCONE    35
#define H_GSTATE            36

