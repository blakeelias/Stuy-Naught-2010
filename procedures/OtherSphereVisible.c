/* Function:
	int OtherSphereVisible(float * myState, float * otherState) 

   Description:
	Returns 1 if the other sphere is in sight.

   Inputs: myState, otherState

   Outputs: 1 if the other sphere is in sight.

   Usage: Repelling, Deflecting Repelling

   Strange note: Apparently, using Vfunc(9, otherState, myState, attTarget, 0);
		 instead of Vfunc(2, otherState, myState, attTarget, 0);
		 messes things up. For specific behavior, refer to RepelTest.c
*/

int i;
float attTarget[3];
float myAtt[3];
float angle;
Vfunc(2, otherState, myState, attTarget, 0); //take the difference

for (i = 0; i < 3; i++){
myAtt[i] = myState[i + 6];
}

angle = Vfunc(8, attTarget, myAtt, NULL, 0);

if (fabs(angle) < 6.0){
return 1;
}

