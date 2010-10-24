

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

//Coasts to a target, in absolute coordinates.

void CoastToTarget(float* myPos, float* coastTarget)
{
 float temp[3];

 Vfunc(2, (coastTarget), (myPos), (temp), 0);

 if (mathVecMagnitude((temp), 3) < 0.1)
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
