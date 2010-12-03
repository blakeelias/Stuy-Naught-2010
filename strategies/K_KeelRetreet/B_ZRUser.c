#define position procvar
#define attitude (procvar+3)
#define panel_location (procvar+6)
#define ZRSetPositionTarget(a) CoastToTarget(myState, (a), 0.04)
  
memcpy(vOtherPrev, vOther, sizeof(float)*3); //original value copied to previous value
  
memcpy(vOther, otherState+3, sizeof(float)*3); // this is set to the current value

// Wait for them to run out of fuel (constant velocity)
if ((Vfunc(6, vOther, vOtherPrev, NULL, 0)) == 0.0)  // <= 0.001
    counter++;
else
    counter = 0;
  
DEBUG(("time: %3.0f, SPH%d: state %i\n", time, getPanelSide() == 1 ? 1 : 2, state));

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
    
          
    //DEBUG(("Counter = %i \n", counter));
  
    if (counter >= 15 || time > 100)
        state = 2;
    else if (getPercentFuelRemaining() < 20)
        state = 3;
    }
  
if (state == 2) { //Moving to panel circle, they're dead
    if (isPanelFound())
        state = 5;
    else {
        attitude[0] = 0;
        attitude[1] = 1*getPanelSide();
        attitude[2] = 0;
   
        position[0] = .7*getPanelSide();
        position[1] = 0;
        position[2] = 0;
   
        ZRSetPositionTarget(position);
        ZRSetAttitudeTarget(attitude);
           
        if (Vfunc(6, myState, position, NULL, 0) < 0.03)
            state = 4;
    }
}
 
if (state == 3) { // Retreating to panel, they are alive
    if (isPanelFound())
        state = 5;
    else {
        position[0] = .7*getPanelSide();
        position[1] = 0;
        position[2] = 0;
        ZRSetPositionTarget(position);
    }
 
    if (Vfunc(6, position, myState, NULL, 0) < 0.03)
        state = 4;
}
 
if (state == 4) { //Finding panel
    RotateTarget(myState, position);
        if (isPanelFound())
            state = 5;
    }
          
if (state == 5) { //Get the panel
        getPanelState(position);
        attitude[0] = 0.7*getPanelSide();
        attitude[1] = attitude[2] = 0;
        Vfunc(9, attitude, position, attitude, 0);
        ZRSetAttitudeTarget(attitude);
        ZRSetPositionTarget(position);
        if (iHavePanel())
            state++;
        }
  
if (state == 6) { //Stop
    if (counter < 15)
        state = 1;
    position[0] = position[1] = position[2] = 0;
    ZRSetVelocityTarget(position);
        }
