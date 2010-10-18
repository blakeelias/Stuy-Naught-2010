/* Calculate velocity and fuel sequences for two straight trajectories:
 * 1) from birthplace to center of panel circle
 * 2) from there to center of other panel circle
*/

// global: float start_pos[3]
// global: float end_pos[3]
// global: int phase

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

float dist1, dist2;
float tolerance = 0.02;

if (time == 0) {
    phase = 0;
    VCopy(myState,start_pos);
    end_pos[0] = 0.7;
    end_pos[1] = 0;
    end_pos[2] = 0;
}

dist1 = VDist(start_pos,end_pos);
dist2 = VDist(myState,end_pos);


if (phase == 0 && dist2 > tolerance) {
    printf("time: %4.0f, To own panel:, dist to target: %5.2f, %% to target: %5.1f, velocity: %5.2f, fuel: %5.1f\n", 
        time,dist2,dist2*100/dist1,VLen(myState+3),getPercentFuelRemaining());
}
else if (phase == 0 && dist2 <= tolerance) {
    phase = 1;
    end_pos[0] = -0.7;
    VCopy(myState,start_pos);
    printf("time: %4.0f, To other panel:, dist to target: %5.2f, %% to target: %5.1f, velocity: %5.2f, fuel: %5.1f\n", 
        time,dist2,dist2*100/dist1,VLen(myState+3),getPercentFuelRemaining());
}
else if (phase == 1 && dist2 > tolerance) {
    printf("time: %4.0f, To other panel:, dist to target: %5.2f, %% to target: %5.1f, velocity: %5.2f, fuel: %5.1f\n", 
        time,dist2,dist2*100/dist1,VLen(myState+3),getPercentFuelRemaining());
}
else if (phase == 1 && dist2 <= tolerance)
    printf("done.\n");

ZRSetPositionTarget(end_pos);

