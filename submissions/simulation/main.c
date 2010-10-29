#include <math.h>
#include <string.h>
#include "ZR_API.h"
#include "ZRGame.h"
#include "math_matrix.h"
#include "spheres_constants.h"
static int state;
static float panelState[7];
static float tangentPoints[3];
static int scanTarget;
static float target_pos[3];
static float target_att[3];
static void CoastToTarget(float* myPos, float* coastTarget);
static float Vfunc(int which, float * v1, float * v2, float * vresult, float scalar);
 
//User01: blakeelias Team: Stuy-Naught Project: Final-Simulation
void ZRUser01(float *myState, float *otherState, float time)
{
float target[3];
 float station[4];
 
 float baseAngle;
 float angleDiff;
 float baseRadius;
 
 float to_opponent[3];
 float sun[3] = {0,0,0};
 
 float tolerance=.02;
 
 float a1, a2;
 float s1 = 0;
 float s2 = 0; //s1 = score 1 second ago. s2 = current score
 
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
 
 
 
if(fabs(otherState[0] - (getPanelSide() * -0.7)) > .10){
 state = 5;
 break;
}
else {
 ZRSetAttitudeTarget(to_opponent);
 if(fabs(otherState[0] - (getPanelSide() * -0.7)) < .005){
  state = 4;
  break;
 }
}
   break;
 case 4:
ZRSetPositionTarget(target_pos);
Vfunc(9, (myState), (otherState), (to_opponent), 0);
if (Vfunc(8, (to_opponent), (myState+6), NULL, 0) < 5 && getPercentChargeRemaining() > 0 && fabs(otherState[0]) > .68 && fabs(otherState[0]) < .81) {
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
 
if(fabs(otherState[0] - (getPanelSide() * -0.7)) < .05 && getPercentChargeRemaining() > 0){
 state = 3;
 break;
}
 
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
 
if (s2 - s1 == 0 && s2 > 0){
state = 8;
break;
}
else {
s1 = s2;
s2 = getOtherCurrentScore();
getStationState(station);
 
Vfunc(7, (station), NULL, (target_att), 0);
 
target_att[1] += cosf(station[3]) * 0.03;
target_att[2] += sinf(station[3]) * 0.03;
 
CoastToTarget(myState, target_att);
 
target_att[0] = 0;
target_att[1] = cosf(station[3]);
target_att[2] = sinf(station[3]);
 
ZRSetAttitudeTarget(target_att);
}
   break;
  case 8:
//Code to beeline towards the station...
 
 
 
target[0] = (getPanelSide() * 0.7);
target[1] = 0;
target[2] = 0;
 
CoastToTarget(myState, target);
   break;
 }
}
void ZRInit01()
{
  state = (int) 0.0;
  memset(panelState,0,sizeof(float)*7);
  memset(tangentPoints,0,sizeof(float)*3);
  scanTarget = (int) 1;
  memset(target_pos,0,sizeof(float)*3);
  memset(target_att,0,sizeof(float)*3);
 
}
//User-defined procedures
 
static void CoastToTarget(float* myPos, float* coastTarget)
{
 
 float temp[3];
 
 Vfunc(2, (coastTarget), (myPos), (temp), 0);
 
 if (Vfunc(0, (temp), NULL, NULL, 0) < 0.1)
 {
  ZRSetPositionTarget(coastTarget);
 }
 else
 {
  Vfunc(3, (temp), NULL, (temp), 0);
  Vfunc(4, (temp), NULL, (temp), (0.02));
 
  ZRSetVelocityTarget(temp);
 }
}
 
static float Vfunc(int which, float * v1, float * v2, float * vresult, float scalar)
{
 
#define prvect(msg,p) printf("%s (%f,%f,%f)\n",msg,p[0],p[1],p[2])
 
int i;
 
if (which == 0) // returns |v1|
return mathVecMagnitude(v1, 3);
 
if (which == 1) { // vresult = V1 + v2
mathVecAdd(vresult,v1,v2,3);
return 0;
}
 
if (which == 2) { // vresult = v1 - v2
float vtemp[3];
Vfunc(4,v2,NULL,vtemp,-1);
mathVecAdd(vresult,v1,vtemp,3);
return 0;
}
 
if (which == 3) { // vresult = v1 / |v1|; if |v1| == 0, returns 0, else 1
memcpy(vresult, v1, sizeof(float)*3);
mathVecNormalize(vresult,3);
return 0;
}
 
if (which == 4) { // vresult = scalar * v1
for (i = 0; i < 3; ++i)
vresult[i] = scalar * v1[i];
return 0;
}
 
if (which == 5) { // returns dot product: v1 * v2
return mathVecInner(v1,v2,3);
}
 
if (which == 6) { // returns distance between v1 and v2
float v3[3];
Vfunc(2,v1,v2,v3,0); // v3 = v1 - v2
return Vfunc(0,v3,NULL,NULL,0);
}
 
if (which == 7) { // copies v1 to vresult
memcpy(vresult, v1, sizeof(float)*3);
return 0;
}
 
if (which == 8) { // angle between two vectors
float dot = Vfunc(5,v1,v2,NULL,0)/(Vfunc(0,v1,NULL,NULL,0)*Vfunc(0,v2,NULL,NULL,0));
return acos(dot)*180.0/3.14159265;
}
 
if (which == 9) { // unit vector pointing from v1 toward v2
float v9[3];
Vfunc(2,v2,v1,v9,0);
return Vfunc(3,v9,NULL,vresult,0);
}
 
if (which == 10) { // rotated vector v1 towards v2 at scalar degrees
float ang = scalar*3.14159265/180;
float u[3];
float c = cosf(ang);
float s = sinf(ang);
float rot[3];
mathVecNormalize(v1,3);
mathVecNormalize(v2,3);
 
if (scalar > Vfunc(8,v1,v2,NULL,0)) {
return 1;
}
 
mathVecCross(u,v1,v2);
mathVecNormalize(u,3);
rot[0] = (v1[0]*(c + u[0] * u[0] * (1-c)) + v1[1]*(u[0] * u[1] * (1-c) - u[2] * s) + v1[2]*(u[0] * u[2] * (1-c) + u[1] * s));
rot[1] = (v1[0]*(u[0] * u[1] * (1-c) + u[2] * s) + v1[1]*(c + u[1] * u[1] * (1-c)) + v1[2]*(u[1] * u[2] * (1-c) - u[0] * s));
rot[2] = (v1[0]*(u[0] * u[2] * (1-c) - u[1] * s) + v1[1]*(u[1] * u[2] * (1-c) + u[0] * s) + v1[2]*(c + u[2] * u[2] * (1-c)));
 
if (Vfunc(8,rot,v1,NULL,0) < Vfunc(8,v1,v2,NULL,0) && Vfunc(8,rot,v2,NULL,0) < Vfunc(8,v1,v2,NULL,0)) {
c = cosf(-1*ang);
s = sinf(-1*ang);
rot[0] = (v1[0]*(c + u[0] * u[0] * (1-c)) + v1[1]*(u[0] * u[1] * (1-c) - u[2] * s) + v1[2]*(u[0] * u[2] * (1-c) + u[1] * s));
rot[1] = (v1[0]*(u[0] * u[1] * (1-c) + u[2] * s) + v1[1]*(c + u[1] * u[1] * (1-c)) + v1[2]*(u[1] * u[2] * (1-c) - u[0] * s));
rot[2] = (v1[0]*(u[0] * u[2] * (1-c) - u[1] * s) + v1[1]*(u[1] * u[2] * (1-c) + u[0] * s) + v1[2]*(c + u[2] * u[2] * (1-c)));
}
 
memcpy(vresult,rot,sizeof(float)*3);
return 0;
}
}
