/* Test zapping from center of panel circle.
 *
 * This controls both satellites.
 * The one with getPanelSide() == -1 will be PASSIVE and go to its respective panel circle center 
 *      and try to stay there.
 *
 * The one with getPanelSide() == 1 will be ACTIVE and charge to 100%  going to its
 *  panel center, and then target the PASSIVE one, and we'll see if there's some positional effect.
*/

// globals: int phase = 0

// include defines.h
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

float target_pos[3] = {0.7,0,0};
float current_pos[3], target_att[3], to_opponent[3];
float sun[3] = {0,0,0};
float tolerance=.02; // 2 cm

if (time == 0)
    phase = 0;

if (getPanelSide() == -1) {
    // =============================== PASSIVE =======================
    target_pos[0] = -0.7;
    ZRSetPositionTarget(target_pos);
    printf("time: %4.0f, (RED) distance away from panel center: %6.3f\n", time, VDist(myState,target_pos));
}
else {
    // ============================== ACTIVE ===========================
    //printf("time: %4.1f, phase: %d\n",time, phase);
    if (phase == 0) { // go to panel center charging
        if (VDist(myState,target_pos) < tolerance && getPercentChargeRemaining() >= 95) {
            phase = 1;
        } else {
            // calc vector from current position back toward sun
            VPoint(sun,myState,target_att);
            ZRSetPositionTarget(target_pos);
            ZRSetAttitudeTarget(target_att);
        }
    }
    else if (phase == 1) {  // completely charged, now turn to face the PASSIVE one
        ZRSetPositionTarget(target_pos);
        VPoint(myState,otherState,to_opponent);
        if (VAngle(to_opponent,myState+6) < 5 && getPercentChargeRemaining() > 0) {
printf("time: %4.0f, (BLUE): ZAPPING ++++++++++++++++++++\n",time);
            ZRRepel();
        }
        else {
            VPoint(myState,otherState,to_opponent);
printf("time: %4.0f, (BLUE): angle to opponent: %f\n",time,VAngle(to_opponent,myState+3));
            ZRSetAttitudeTarget(to_opponent);
        }
    }
}

