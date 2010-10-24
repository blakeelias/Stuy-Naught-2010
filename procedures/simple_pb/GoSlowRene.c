/* float GoSlowRene(int which, float *myState, float *target_pos, float withFuel)
 *
 * Tries to get to target_pos using only withFuel amount of fuel.  Uses
 *  ZRSetVelocityTarget()
 *
 * if which == 2: returns an estimate of the amount of fuel (range: 0 - 1)
 *      needed to get to the target_pos if using ZRSetPositionTarget().
 *
 * if which == 0: initiates the process, using target_pos and withFuel
 *      target_pos[3] is where you want to get to.
 *      withFuel (range: 0 - 1) is the amount of fuel to use to get all the way
 *          to target_pos
 *
 *      returns 0 if the function needs to be called again (with which = 1) to
 *      continue the trajectory.
 *      returns 1 if at target_pos and close to 0 velocity
 *
 * if which == 1: then continue the process, target_pos and withFuel are ignored.
 *      returns 0 if the function needs to be called again (with which = 1) to
 *      continue the trajectory.
 *      returns 1 if at target_pos and close to 0 velocity
 *
 * The defines: MAX_POSITION_ERROR (in meters) and MAX_VELOCITY_ERROR (in meters/sec)
 *      define what it is to be at the target and with low enough velocity
 *
*/

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


#define P_START 20  // start of our section of the ProcVars area

#define MAX_POSITION_ERROR  (0.01)  // in meters
#define MAX_VELOCITY_ERROR  (0.005)  // in meters/sec

#define ACCELERATION        (0.007)         // m/sec^2  (empirically calculated)
#define DECELERATION        (0.0035)        // m/sec^2  (empirically calculated)
#define FUEL_TO_VEL_RATIO   (0.132/0.053)    // how much fuel (in %) used for speed change of 1m/sec

float coast_vel, distance_to_start_slowing, to_target, target_pos2[3], current_vel;

if (which == 0 || which == 2)
    VCopy(target_pos,ProcVars+P_START+3);  // store target

to_target = VDist(myState,ProcVars+P_START+3);  // distance to target

if (which == 2) {  // calculate fuel necessary if ZRSetPositionTarget() would do the work
    // assume that we're at rest.
    float fuel_consumed;
    fuel_consumed = 2 * FUEL_TO_VEL_RATIO * sqrt(2*ACCELERATION*to_target/3);
    return fuel_consumed;
}

if (which == 0) {
printf("Starting at %d, fuel at: %5.1f\n", G_time, getPercentFuelRemaining());
    // are we done before we begin?
    to_target = VDist(myState,target_pos);
    current_vel = VLen(myState+3);
    if (to_target <= MAX_POSITION_ERROR && current_vel <= MAX_VELOCITY_ERROR)
        return 1;
    
    // calculate the coasting velocity using: 2 * coast_vel * FUEL_TO_VEL_RATIO = withFuel
    coast_vel = withFuel / (2 * FUEL_TO_VEL_RATIO);

    // calculate the distance from the target where we must start slowing
    distance_to_start_slowing = (coast_vel * coast_vel)/(2 * DECELERATION);
printf("coast_vel: %6.3f distance_to_start_slowing: %5.2f\n",coast_vel,distance_to_start_slowing);
    
    // store calculated values
    ProcVars[P_START+1] = coast_vel;
    ProcVars[P_START+2] = distance_to_start_slowing;
    VCopy(target_pos,ProcVars+P_START+3);

    if (to_target <= distance_to_start_slowing) {
        ProcVars[P_START] = 2;   // phase = 2: slowing
        ZRSetPositionTarget(target_pos);
printf("Finished at: %d, Fuel at: %5.1f\n", getPercentFuelRemaining());
        return 0;
    }
    else {
// assuming we're starting from a stationary position
float coast_vel2 = coast_vel * coast_vel;
float coast_dist = to_target - coast_vel2/(2 * ACCELERATION) - coast_vel2/(2 * DECELERATION);
float eta = coast_vel/ACCELERATION + coast_vel/DECELERATION + coast_dist/coast_vel;
printf("prediction: ETA %4.0f seconds from now, fuel consumed: %5.2f\n",eta,withFuel);

        ProcVars[P_START] = 1;  // phase = 1: accelerating or coasting
    }
}

if (ProcVars[P_START] == 1) {
    // phase 1: accelerating or coasting
    // restore values from ProcVars
    coast_vel = ProcVars[P_START+1];
    distance_to_start_slowing = ProcVars[P_START+2];
    VCopy(ProcVars+P_START+3,target_pos2);

    to_target = VDist(myState,target_pos2);
    if (to_target <=  distance_to_start_slowing)
        ProcVars[P_START] = 2;
    else {
        float toward_target[3], requested_velocity[3];
        VPoint(myState,target_pos2,toward_target);
        VMult(toward_target,coast_vel,requested_velocity);
        ZRSetVelocityTarget(requested_velocity);
printf("time: %d Phase 1, to_target: %5.2f\n", G_time, to_target);
        return 0;
    }
} 
if (ProcVars[P_START] == 2) {
    VCopy(ProcVars+P_START+3,target_pos2);
    to_target = VDist(myState,target_pos2);
    current_vel = VLen(myState+3);

printf("time: %d Phase 2, to_target: %6.3f  velocity: %6.3f\n",G_time, to_target, current_vel);
    if (to_target <= MAX_POSITION_ERROR && current_vel <= MAX_VELOCITY_ERROR) {
        ProcVars[P_START] = 3;
printf("final fuel at: %5.2f\n",getPercentFuelRemaining());
        return 1;
    }
    else {
        ZRSetPositionTarget(target_pos2);
        return 0;
    }
  
}

printf("time: %d. Done\n", G_time);

    

