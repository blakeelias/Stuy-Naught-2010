/* History function from Rene and Mr. Brooks
 * 
 * int HistFunc(int which, float *myState, float *otherState, float *rest, int timeSlot)
 *
 *   if which == 0: store the current SPHERE properties into the requested timeSlot
 *
 *      Usage:  HistFunc(0, myState, otherState, NULL, G_time);
 *
 *   if which == 1: retrieve, into the arrays supplied, the stored SPHERE properties for the given timeSlot
 *
 *      for instance, to retrieve the current SPHERE properties (for the current timeSlot),
 *        allocate 3 arrays, and call:
 *      float me[12],other[12],restOfProperties[12];
 *      HistFunc(1, me, other, restOfProperties, G_time);
 *        and me[] will be filled with myState, other with otherState, and restOfProperties with the rest
 *
 *  see documentation below the code for what each property means.
*/

/*  copy function header:
int HistFunc(int which, float *myState, float *otherState, float *rest, int timeSlot)
{
*/
    int width = 36;
    float pos[3] = {0,0,0};
    int i,k;
    float otherPos[3];
    float toward[3];  // unit vector pointing from me to opponent
    float att[3];
    float angle;

    if (timeSlot < 0 || timeSlot > G_time)
        return 0;

    if (which == 0) {
        for (k=0; k<3; k++) {
        pos[k] = myState[k];
    }

    for (k=0; k<12; k++) {
        history[width*timeSlot+k] = myState[k];
        history[width*timeSlot+12+k] = otherState[k];
    }

    history[width*timeSlot+24] = iHavePanel();
    history[width*timeSlot+25] = otherHasPanel();
    history[width*timeSlot+26] = isPanelFound();
    history[width*timeSlot+27] = isPanelInSync();
    history[width*timeSlot+28] = isStationInSync();
    history[width*timeSlot+29] = getCurrentScore();
    history[width*timeSlot+30] = getOtherCurrentScore();
    history[width*timeSlot+31] = getPercentChargeRemaining();
    history[width*timeSlot+32] = getPercentFuelRemaining();
    history[width*timeSlot+33] = otherRepelling();
    history[width*timeSlot+34] = outsideBoundary(pos);

    // is the opponent within your cone of sight?
    Vfunc(7,otherState,NULL,otherPos,0); // get other's position
    Vfunc(9,pos,otherPos,toward,0);
    Vfunc(7,myState+6,NULL,att,0); // get my attitude
    angle = acos(Vfunc(8,att,toward,NULL,0))*180.0/3.14159265;
    if (angle <= 6)
        history[width*timeSlot+35] = 1;
    else
        history[width*timeSlot+35] = 0;
        
        

    return 1;
    }

    if (which == 1) { // retrieve
        for (i = timeSlot*width, k = 0; k < 12; ++i, ++k)
            myState[k] = history[i];
        for (i = timeSlot*width+12, k = 0; k < 12; ++i, ++k)
            otherState[k] = history[i];
        for (i = timeSlot*width+24, k = 0; k < 12; ++i, ++k)
            rest[k] = history[i];
        return 1;
    }
//}

/* 
    Returned values from HistFunc, when which == 1:

        myState:
0: Position x-coordinate(self)
1: Position y-coordinate(self)
2: Position z-coordinate(self)

3: Velocity x-coordinate(self)
4: Velocity y-coordinate(self)
5: Velocity z-coordinate(self)

6: Attitude x-coordinate(self)
7: Attitude y-coordinate(self)
8: Attitude z-coordinate(self)

9: Attitude Rate x-coordinate(self)
10: Attitude Rate y-coordinate(self)
11: Attitude Rate z-coordinate(self)

        otherState:
0: Position x-coordinate(opponent)
1: Position y-coordinate(opponent)
2: Position z-coordinate(opponent)

3: Velocity x-coordinate(opponent)
4: Velocity y-coordinate(opponent)
5: Velocity z-coordinate(opponent)

6: Attitude x-coordinate(opponent)
7: Attitude y-coordinate(opponent)
8: Attitude z-coordinate(opponent)

9: Attitude Rate x-coordinate(opponent)
10: Attitude Rate y-coordinate(opponent)
11: Attitude Rate z-coordinate(opponent)

        rest:
0: Do you have the solar panel (1 = yes, 0 = no)
1: Does your opponent have the solar panel (1 = yes, 0 = no)

2: Is the Panel within your cone of sight (1 = yes, 0 = no)
3: Is the Panel synced up to the SPHERE (1 = yes, 0 = no)
4: Is the Station synced up to the SPHERE (1 = yes, 0 = no)

5: Your Score
6: Opponent's Score

7: Charge remaining
8: Fuel Remaining
9: Are you being repelled (1 = yes, 0 = no)
10: Are you outside the Boundary (1 = yes, 0 = no)         
11: Is the opponent within your cone of sight? (1 = yes, 0 = no)

*/

