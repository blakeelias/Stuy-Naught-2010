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
