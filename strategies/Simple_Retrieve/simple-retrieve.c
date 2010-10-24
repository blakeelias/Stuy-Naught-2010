/**
 * Code Size: 114%
 * Simulate with game variables, exits with status 20 / opponent 40
 * Around 20% fuel left, 88 seconds elapsed
 * 
 * http://zerorobotics.mit.edu/ide/vis/21959
 * http://zerorobotics.mit.edu/ide/vis/21963
 */

int state;
float procvar[10] = 0;

void ZRUser(float *myState, float *otherState, float time)
{
#define position procvar
#define attitude (procvar+3)
#define panel_location (procvar+6)
 
float distance;
     
    DEBUG(("time: %3.0f, state: %d, pos: (%5.2f, %5.2f, %5.2f), ",
           time, state, myState[0], myState[1], myState[2]));
    DEBUG(("att: (%5.2f, %5.2f, %5.2f), panel: %d, ",
           myState[6], myState[7], myState[8], isPanelInSync()));
     
    if (state == 0) {
        attitude[0] = 0;
        attitude[1] = 1;
        attitude[2] = 0;
 
        position[0] = .7*getPanelSide();
        position[1] = 0;
        position[2] = 0;
 
        ZRSetPositionTarget(position);
        ZRSetAttitudeTarget(attitude);
         
        distance = Vfunc(6, myState, position, NULL, 0);
        if (distance < 0.01)
            state = 1;
    }
    if (state == 1) {
        RotateTarget(myState, position);
        if (isPanelFound()) {
            getPanelState(position);
            ZRSetPositionTarget(position);
            Vfunc(9, myState, position, attitude, 0);
            ZRSetAttitudeTarget(attitude);
            state = 2;
        }
    }
    if (state == 2) {
        ZRSetAttitudeTarget(attitude);
        ZRSetPositionTarget(position);
        if (iHavePanel())
            state = 3;
    }
    if (state == 3) {
        if (iHavePanel()) {
            position[0] = -.7*getPanelSide();
            position[1] = 0;
            position[2] = 0;
 
            attitude[0] = 0;
            attitude[1] = 0;
            attitude[2] = 1*getPanelSide();
 
            ZRSetPositionTarget(position);
            ZRSetAttitudeTarget(attitude);
        }
    }
}

 
void RotateTarget(float * myState, float * pos)
{
 #define VLen(a) Vfunc(0, (a), NULL, NULL, 0)
#define VAdd(a, b, result) Vfunc(1, (a), (b), (result), 0)
#define VSub(a, b, result) Vfunc(2, (a), (b), (result), 0)
#define VUnit(a, result) Vfunc(3, (a), NULL, (result), 0)
#define VMult(a, b, result) Vfunc(4, (a), NULL, (result), (b))
#define VDot(a, b) Vfunc(5, (a), (b), NULL, 0)
#define VDist(a, b) Vfunc(6, (a), (b), NULL, 0)
#define VCopy(a, result) Vfunc(7, (a), NULL, (result), 0)
#define VAngle(a, b) Vfunc(8, (a), (b), NULL, 0)
#define VPoint(a, b, result) Vfunc(9, (a), (b), (result), 0)
 
#define PI 3.14159265
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
 
float Vfunc(int which, float * v1, float * v2, float * vresult, float scalar)
{
    int i;
     
    if (which == 0) // returns |v1|
        return sqrt(Vfunc(5,v1,v1,NULL,0));
 
    if (which == 1) { // vresult = V1 + v2
        for (i = 0; i < 3; ++i)
            vresult[i] = v1[i] + v2[i];
        return 0;
    }
 
    if (which == 2) { // vresult = v1 - v2
        for (i = 0; i < 3; ++i)
            vresult[i] = v1[i] - v2[i];
        return 0;
    }
 
    if (which == 3) { // vresult = v1 / |v1|; if |v1| == 0, returns 0, else 1
        float s = Vfunc(0,v1,NULL,NULL,0);
        if (s == 0.0)
            return 0.0;
        Vfunc(4,v1,NULL,vresult,1.0/s);
        return 1.0;
    }
 
    if (which == 4) { // vresult = scalar * v1
        for (i = 0; i < 3; ++i)
            vresult[i] = scalar * v1[i];
        return 0;
    }
 
    if (which == 5) { // returns dot product: v1 * v2
        float s2 = 0;
        for (i = 0; i < 3; ++i)
            s2 += v1[i] * v2[i];
        return s2;
    }
 
    if (which == 6) { // returns distance between v1 and v2
        float v3[3];
        Vfunc(2,v1,v2,v3,0);  // v3 = v1 - v2
        return Vfunc(0,v3,NULL,NULL,0);
    }
 
    if (which == 7) { // copies v1 to vresult
        for (i = 0; i < 3; ++i)
            vresult[i] = v1[i];
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
}
