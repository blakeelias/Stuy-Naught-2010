






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
int scanTarget = 1;


void ZRUser(float* myState, float* otherState, float time)
{
 float target[3];
 float station[4];

 float baseAngle;
 float angleDiff;
 float baseRadius;

 float a1, a2;

 switch (state)
 {
  case 0:

//Code to initialize the sphere, then search for the panel...

state = 1;
   break;
  case 1:

//Code to move towards panel initialization circle...


//Check if panel was found.

if (isPanelFound())
{
 getPanelState(panelState);


 panelState[4] = panelState[0];

 baseAngle = atan2f(panelState[2], panelState[1]);
 baseRadius = sqrtf(((panelState[1]) * (panelState[1])) + ((panelState[2]) * (panelState[2]))) - 0.03;

 panelState[5] = cosf(baseAngle) * baseRadius;
 panelState[6] = sinf(baseAngle) * baseRadius;

 state = 3;
 break;
}




if (fabs(myState[0] - (getPanelSide() * 0.7)) < 0.1)
 state = 2;

baseAngle = atan2f(myState[2], myState[1]);

target[0] = (getPanelSide() * 0.7);
target[1] = cosf(baseAngle) * 0.7;
target[2] = sinf(baseAngle) * 0.7;

ZRSetPositionTarget(target);



//Code to find tangent lines...

baseAngle = atan2f(-target[2], -target[1]);
angleDiff = asinf(0.5 / sqrtf(((target[1]) * (target[1])) + ((target[2]) * (target[2]))));

tangentPoints[0] = baseAngle - angleDiff;
tangentPoints[1] = baseAngle + angleDiff;




tangentPoints[2] = tangentPoints[0];


//Point in the direction of tangentPoints[2]

target[0] = 0;
target[1] = cosf(tangentPoints[2]);
target[2] = sinf(tangentPoints[2]);

ZRSetAttitudeTarget(target);


   break;
  case 2:

//Code to search for panel...


//Check if panel was found.

if (isPanelFound())
{
 getPanelState(panelState);


 panelState[4] = panelState[0];

 baseAngle = atan2f(panelState[2], panelState[1]);
 baseRadius = sqrtf(((panelState[1]) * (panelState[1])) + ((panelState[2]) * (panelState[2]))) - 0.03;

 panelState[5] = cosf(baseAngle) * baseRadius;
 panelState[6] = sinf(baseAngle) * baseRadius;

 state = 3;
 break;
}




//Code to find tangent lines...

baseAngle = atan2f(-myState[2], -myState[1]);
angleDiff = asinf(0.5 / sqrtf(((myState[1]) * (myState[1])) + ((myState[2]) * (myState[2]))));

tangentPoints[0] = baseAngle - angleDiff;
tangentPoints[1] = baseAngle + angleDiff;




//Point in the direction of tangentPoints[2]

target[0] = 0;
target[1] = cosf(tangentPoints[2]);
target[2] = sinf(tangentPoints[2]);

ZRSetAttitudeTarget(target);


tangentPoints[2] += scanTarget * 0.1;

if ((scanTarget == 1) && (tangentPoints[2] >= tangentPoints[1]))
 scanTarget = -1;
else if ((scanTarget == -1) && (tangentPoints[2] <= tangentPoints[0]))
 scanTarget = 1;

target[0] = getPanelSide() * 0.7;
target[1] = myState[1];
target[2] = myState[2];

ZRSetPositionTarget(target);

   break;
  case 3:

//Code to move to panel...

if (iHavePanel())
{
 state = 4;
 scanTarget = 0;
 break;
}

ZRSetPositionTarget(&panelState[4]);

Vfunc(7, (panelState), NULL, ( target), 0);
target[0] = 0;
Vfunc(3, (target), NULL, ( target), 0);

ZRSetAttitudeTarget(target);

   break;
  case 4:

//Code to go camping towards the center

DEBUG(("currently camping\n"));


target[0] = target[1] = target[2] = 0;

ZRSetPositionTarget(target);

if (Vfunc(6,myState,target,NULL,0) < .1){
	state = 5;
break;
}
   break;
  case 5:


int j;
for (j = 0; j < 3; j++)
	target[j] = otherState[j] - myState[j];
target = Vfunc(3,target,NULL,target,0);
ZRSetAttitudeTarget(target);


if (Vfunc(8, (myState+6), ( otherState), NULL, 0) < 12) {
    ZRRepel();
}

if (Vfunc(6, myState, otherState, NULL, 0) < 1){
	ZRSetPositionTarget(otherState);
}

DEBUG(("should be zapping\n"));
   break;
 }
}
