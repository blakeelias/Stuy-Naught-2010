

//Macros for functions used to set the position and attitude
//target. Change these if we ever make better versions.



//The target distance from the center of the panel init circle.
//The satellite, upon starting, will move to the closest point
//on the plane of the panel init circle that is this many
//meters away from the center of the circle.


//Rotation speed when searching for the panel. The satellite
//controls its rotation by setting its attitude target to a
//point this many radians away from its current attitude.


//The number of meters in front of a docking target that the
//satellite will move to.


//The satellite will always be drifting away from its position.
//If the satellite is less than this number of meters away from
//its target position, it will tolerate the error.


//How close is "close to my target"?


//Magnitude of the set velocity with CoastToTarget


//Add more states as necessary
//Avoid touching anything beyond this point



//Vfunc defines...
int state = 0;
float panelState[7]; //Last 3 elements is position target
float tangentPoints[3]; //Angles: Tan1, Tan2, current angle
float target_pos[3];
float target_att[3];
int scanTarget = 1;

void ZRUser(float* myState, float* otherState, float time)
{
 float station[4];

 float baseAngle;
 float angleDiff;
 float baseRadius;

 float to_opponent[3];
 float sun[3] = {0,0,0};

 float tolerance=.02;

 float a1, a2;

 DEBUG(("time: %4.0f, state: %d\n", time, state));
 switch (state)
 {
  case 0:
//Code to initialize the sphere, then search for the panel...

state = 1;
   break;
  case 1:
//Code to move towards panel initialization circle...



if (fabs(myState[0] - (getPanelSide() * 0.7)) < 0.1)
 state = 2;

baseAngle = atan2f(myState[2], myState[1]);

target_pos[0] = (getPanelSide() * 0.7);
target_pos[1] = cosf(baseAngle) * 0.7;
target_pos[2] = sinf(baseAngle) * 0.7;

ZRSetPositionTarget(target_pos);

Vfunc(9, (sun), (myState), (target_att), 0);

ZRSetAttitudeTarget(target_att);


//Code to find tangent lines...

baseAngle = atan2f(-target_pos[2], -target_pos[1]);
angleDiff = asinf(0.5 / sqrtf(mathSquare(target_pos[1]) + mathSquare(target_pos[2])));

tangentPoints[0] = baseAngle - angleDiff;
tangentPoints[1] = baseAngle + angleDiff;



tangentPoints[2] = tangentPoints[0];
   break;
  case 2:
if (getPercentChargeRemaining() >= 95) {
    state = 3;
    break;
} else {
    // calc vector from current position back toward sun
    Vfunc(9, (sun), (myState), (target_att), 0);
    ZRSetPositionTarget(target_pos);
    ZRSetAttitudeTarget(target_att);
}
   break;
  case 3:
//Code to wait for the opponent to get into their panel's plane



Vfunc(9, (myState), (otherState), (to_opponent), 0);

ZRSetAttitudeTarget(to_opponent);

if(fabs(otherState[0] - (getPanelSide() * -0.7)) < tolerance){
 state = 4;
 break;
}
   break;
 case 4:
ZRSetPositionTarget(target_pos);
Vfunc(9, (myState), (otherState), (to_opponent), 0);
if (Vfunc(8, (to_opponent), (myState+6), NULL, 0) < 5 && getPercentChargeRemaining() > 0) {
    DEBUG(("time: %4.0f, (BLUE): ZAPPING ++++++++++++++++++++\n",time));
    ZRRepel();
}
else {
    if (getPercentChargeRemaining() < 1) {
        state = 5;
        break;
    }
    Vfunc(9, (myState), (otherState), (to_opponent), 0);
    DEBUG(("time: %4.0f, (BLUE): angle to opponent: %f\n",time,Vfunc(8, (to_opponent), (myState+3), NULL, 0)));
    ZRSetAttitudeTarget(to_opponent);
}
   break;
  case 5:
//Code to search for panel...

//Check if panel was found.

if (isPanelFound())
{
 getPanelState(panelState);


 panelState[4] = panelState[0];

 baseAngle = atan2f(panelState[2], panelState[1]);
 baseRadius = sqrtf(mathSquare(panelState[1]) + mathSquare(panelState[2])) - 0.03;

 panelState[5] = cosf(baseAngle) * baseRadius;
 panelState[6] = sinf(baseAngle) * baseRadius;

 state = 6;
 break;
}


//Code to find tangent lines...

baseAngle = atan2f(-myState[2], -myState[1]);
angleDiff = asinf(0.5 / sqrtf(mathSquare(myState[1]) + mathSquare(myState[2])));

tangentPoints[0] = baseAngle - angleDiff;
tangentPoints[1] = baseAngle + angleDiff;


//Point in the direction of tangentPoints[2]

target_att[0] = 0;
target_att[1] = cosf(tangentPoints[2]);
target_att[2] = sinf(tangentPoints[2]);

ZRSetAttitudeTarget(target_att);

tangentPoints[2] += scanTarget * 0.1;

if ((scanTarget == 1) && (tangentPoints[2] >= tangentPoints[1]))
 scanTarget = -1;
else if ((scanTarget == -1) && (tangentPoints[2] <= tangentPoints[0]))
 scanTarget = 1;

target_pos[0] = getPanelSide() * 0.7;
target_pos[1] = myState[1];
target_pos[2] = myState[2];

ZRSetPositionTarget(target_pos);
   break;
  case 6:
//Code to move to panel...

if (iHavePanel())
{
 state = 7;
 scanTarget = 0;
 break;
}

ZRSetPositionTarget(&panelState[4]);

Vfunc(7, (panelState), NULL, (target_pos), 0);
target_pos[0] = 0;
Vfunc(3, (target_pos), NULL, (target_pos), 0);

ZRSetAttitudeTarget(target_pos);
   break;
  case 7:
//Code to beeline towards the station...

getStationState(station);

Vfunc(7, (station), NULL, (target_att), 0);

target_att[1] += cosf(station[3]) * 0.03;
target_att[2] += sinf(station[3]) * 0.03;

CoastToTarget(myState, target_att);

target_att[0] = 0;
target_att[1] = cosf(station[3]);
target_att[2] = sinf(station[3]);

ZRSetAttitudeTarget(target_att);
   break;
 }
}
