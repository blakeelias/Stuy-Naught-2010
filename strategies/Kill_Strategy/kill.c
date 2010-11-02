#include <math.h>
#include <string.h>
#include "ZR_API.h"
#include "ZRGame.h"
#include "math_matrix.h"
#include "spheres_constants.h"
static int state;
static float campPos[3];
static float procvar[10];
static int counter;
static float vOther[3];
static float vOtherPrev[3];
static float Vfunc(int which, float * v1, float * v2, float * vresult, float scalar);
static void CoastToAttitude(float* myState, float* attitudeTarget);
static void RotateTarget(float * myState, float * pos);
 
//User01: blakeelias Team: Stuy-Naught Project: kill-strategy
void ZRUser01(float *myState, float *otherState, float time)
{
#define position procvar
#define attitude (procvar+3)
#define panel_location (procvar+6)
 
float distance;
 
float to_opponent[3];
 
float stop[3];
 
stop[0] = 0;
stop[1] = 0;
stop[2] = 0;
 
campPos[0] = -.1 * getPanelSide();
campPos[1] = 0;
campPos[2] = 0;
 
memcpy(vOtherPrev, vOther, sizeof(float)*3); //original value copied to previous value
 
memcpy(vOther, otherState+3, sizeof(float)*3); // this is set to the current value
 
DEBUG(("%i \n", state));
 
if (state == 0) { //Getting to Position
    ZRSetPositionTarget(campPos);
    Vfunc(9, myState, otherState, to_opponent, 0);
    CoastToAttitude(myState, to_opponent);
     
    distance = Vfunc(6, myState, campPos, NULL, 0);
     
    if (distance < 0.01) {
        state++;
        }
    }
 
if (state == 1) { //Zapping
    ZRSetPositionTarget(campPos);
 
    Vfunc(9, myState, otherState, to_opponent, 0);
    ZRSetAttitudeTarget(to_opponent);
         
    if (fabs (Vfunc(8, myState+6, to_opponent, NULL, 0)) < 6.0) {
        ZRRepel();
        }
     
    if ((Vfunc(6, vOther, vOtherPrev, NULL, 0)) == 0.0) {
        counter++;
        }
         
    DEBUG(("Counter = %i \n", counter));
 
    if (counter >= 15) {
        state++;
        }
    }
 
if (state == 2) { //moving to panel circle
        attitude[0] = 0;
        attitude[1] = 1*getPanelSide();
        attitude[2] = 0;
  
        position[0] = .7*getPanelSide();
        position[1] = 0;
        position[2] = 0;
  
        ZRSetPositionTarget(position);
        ZRSetAttitudeTarget(attitude);
          
        distance = Vfunc(6, myState, position, NULL, 0);
        if (distance < 0.01)
            state++;
    }
     
if (state == 3) { // finding panel
    RotateTarget(myState, position);
        if (isPanelFound()) {
        getPanelState(position);
            ZRSetPositionTarget(position);
            Vfunc(9, myState, position, attitude, 0);
            ZRSetAttitudeTarget(attitude);
            state++;
            }
        }
         
if (state == 4) { //get the panel
        ZRSetAttitudeTarget(attitude);
        ZRSetPositionTarget(position);
        if (iHavePanel())
            state++;
    }
 
if (state == 5) {
    ZRSetVelocityTarget(stop);
    }
}
void ZRInit01()
{
  state = (int) 0;
  memset(campPos,0,sizeof(float)*3);
  memset(procvar,0,sizeof(float)*10);
  counter = (int) 0;
  memset(vOther,0,sizeof(float)*3);
  memset(vOtherPrev,0,sizeof(float)*3);
 
}
//User-defined procedures
 
static float Vfunc(int which, float * v1, float * v2, float * vresult, float scalar)
{
 int i;
float vtemp[3];
 
if (which == 2) { // vresult = v1 - v2
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
return mathVecMagnitude(v3,3);
}
 
if (which == 8) { // angle between two vectors
float dot = Vfunc(5,v1,v2,NULL,0)/(mathVecMagnitude(v1,3)*mathVecMagnitude(v2,3));
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
float c;
float s;
float rot[3];
int k;
mathVecNormalize(v1,3);
mathVecNormalize(v2,3);
 
if (scalar > Vfunc(8,v1,v2,NULL,0)) {
return 1;
}
 
c = cosf(ang);
s = sinf(ang);
mathVecCross(u,v1,v2);
mathVecNormalize(u,3);
 
for(k=0;k<2;k++) {
if ((k == 1) && (fabs(Vfunc(8,rot,v1,NULL,0)) > fabs(Vfunc(8,v1,v2,NULL,0)) || fabs(Vfunc(8,rot,v2,NULL,0)) > fabs(Vfunc(8,v1,v2,NULL,0)))) {
c = cosf(-1*ang);
s = sinf(-1*ang);
}
rot[0] = (v1[0]*(c + u[0] * u[0] * (1-c)) + v1[1]*(u[0] * u[1] * (1-c) - u[2] * s) + v1[2]*(u[0] * u[2] * (1-c) + u[1] * s));
rot[1] = (v1[0]*(u[0] * u[1] * (1-c) + u[2] * s) + v1[1]*(c + u[1] * u[1] * (1-c)) + v1[2]*(u[1] * u[2] * (1-c) - u[0] * s));
rot[2] = (v1[0]*(u[0] * u[2] * (1-c) - u[1] * s) + v1[1]*(u[1] * u[2] * (1-c) + u[0] * s) + v1[2]*(c + u[2] * u[2] * (1-c)));
}
 
memcpy(vresult,rot,sizeof(float)*3);
return 0;
}
}
 
static void CoastToAttitude(float* myState, float* attitudeTarget)
{
#define VRotate(vector, angle, target, result) Vfunc(10, (vector), (target), (result), (angle))
#define VAng(a1, a2) Vfunc(8, (a1), (a2), NULL, 0)
   
#define COASTING_VELOCITY 15
   
 if (VAng(&myState[6], attitudeTarget) < COASTING_VELOCITY) {
  ZRSetAttitudeTarget(attitudeTarget);
  }
 else
 {
  float intermediate[3];
  VRotate(&myState[6], COASTING_VELOCITY, attitudeTarget, intermediate);
  ZRSetAttitudeTarget(intermediate);
 }
}
 
static void RotateTarget(float * myState, float * pos)
{
#define VLen(a) mathVecMagnitude((a), 3)
#define VAdd(a, b, result) mathVecAdd(result, (a), (b), 3) 
#define VSub(a, b, result) Vfunc(2, (a), (b), (result), 0)
#define VUnit(a, result) Vfunc(3, (a), NULL, (result), 0)
#define VMult(a, b, result) Vfunc(4, (a), NULL, (result), (b))
#define VDot(a, b) Vfunc(5, (a), (b), NULL, 0)
#define VDist(a, b) Vfunc(6, (a), (b), NULL, 0)
#define VCopy(a, result) memcpy((result), (a), sizeof(float)*3)
#define VAngle(a, b) Vfunc(8, (a), (b), NULL, 0)
#define VPoint(a, b, result) Vfunc(9, (a), (b), (result), 0)
#define Deg2Rad(Deg) (Deg*PI/180.0)
#define Rad2Deg(Rad) (Rad*180.0/PI)
  
    // do ZRSetAttitudeTarget(current_att + AngleForward)
#define AngleForward 30
  
    float temp[3], target_att[3], current_att[3];
    float current_theta, target_theta;
  
    ZRSetPositionTarget(pos);
  
    VCopy(myState+6,current_att);
    current_theta = atan2(current_att[2],current_att[1]);
    if (current_theta < 0)
        current_theta = current_theta + 2*PI;
    target_theta = current_theta + Deg2Rad(AngleForward);
  
    temp[0] = -5.0*current_att[0];
    temp[1] = cos(target_theta);
    temp[2] = sin(target_theta);
    VUnit(temp,target_att);
  
    //printf("time: %2.0f, current_att: (%5.2f, %5.2f, %5.2f), target: (%5.2f, %5.2f, %5.2f), to_target: %5.1f",
    //procvar[0],current_att[0],current_att[1],current_att[2],target_att[0],target_att[1],target_att[2],
    //VAngle(current_att,target_att));
    //printf(" rates: (%5.2f, %5.2f, %5.2f)\n", myState[9],myState[10],myState[11]);
    //printf( " out-of-plane: %5.2f\n",asin(current_att[0])*180/3.14159);
  
    ZRSetAttitudeTarget(target_att);
}