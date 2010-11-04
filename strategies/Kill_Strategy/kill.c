#include <math.h>
#include <string.h>
#include "ZR_API.h"
#include "ZRGame.h"
#include "math_matrix.h"
#include "spheres_constants.h"
static int counter;
static float vOtherPrev[3];
static float procvar[10];
static float vOther[3];
static int state;
static float Vfunc(int which, float * v1, float * v2, float * vresult, float scalar);
static void RotateTarget(float * myState, float * pos);
 
//User01: blakeelias Team: Stuy-Naught Project: kill-strategy
void ZRUser01(float *myState, float *otherState, float time)
{
#define position procvar
#define attitude (procvar+3)
#define panel_location (procvar+6)
  
memcpy(vOtherPrev, vOther, sizeof(float)*3); //original value copied to previous value
  
memcpy(vOther, otherState+3, sizeof(float)*3); // this is set to the current value
  
DEBUG(("%i \n", state));
  
if (state == 1) { //Zapping
    // Get between the opponent and the sun
    memcpy(position, otherState, sizeof(float)*3);
    mathVecNormalize(position, 3);
    Vfunc(4, position, NULL, position, 0.1);
 
    ZRSetPositionTarget(position);
     
    // Face the opponent
    Vfunc(9, myState, otherState, attitude, 0);
    ZRSetAttitudeTarget(attitude);
     
    // Zap once we see them
    if (fabs (Vfunc(8, myState+6, attitude, NULL, 0)) < 6.0) {
        ZRRepel();
        }
     
    // Wait for them to run out of fuel (constant velocity)
    if ((Vfunc(6, vOther, vOtherPrev, NULL, 0)) == 0.0)
        counter++;
    else
        counter = 0;
          
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
           
        if (Vfunc(6, myState, position, NULL, 0) < 0.01)
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
    position[0] = position[1] = position[2] = 0;
    ZRSetVelocityTarget(position);
    }
}
void ZRInit01()
{
  counter = (int) 0;
  memset(vOtherPrev,0,sizeof(float)*3);
  memset(procvar,0,sizeof(float)*10);
  memset(vOther,0,sizeof(float)*3);
  state = (int) 1;
 
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
