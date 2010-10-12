/*Daniel's code for repel testing, which has now been edited a lot :P

Description: The sphere charges, sets its attitude to face the other sphere. When it has faced the other sphere, it will repel.

Calls: FaceOtherSphere

Usage: Repelling

Repelling each other:

Repelling each other at the same time does indeed do nothing or close to nothing (both spheres lose charge, but they move a small amount: .02 in each direction. I believe this is because of natural drift, though).

Although in the simulator, apparently when the same code is run by both spheres (Race > Used this code for both sides), if we comment out the first and third line:

//if (getPercentChargeRemaining() == 100){
FaceOtherSphere(myState, otherState);
//}	

one of the spheres has 3% more charge, and it does make a significant difference: one sphere is pushed roughly .33 in the Y-direction.



Strange note from OtherSphereVisible.c: if we use Vfunc(9) instead of Vfunc(2) (this is abbreviated), then the sphere will repel once rotate, face the other sphere, and then do nothing.

Another strange note: 	
	if (getPercentChargeRemaining() == 100) {
		FaceOtherSphere(myState, otherState);
	}
causes the sphere to rotate everytime it doesn't have 100% charge, and then rotate back.

*/

void ZRUser(float * myState, float * otherState, float time) {

	if (getPercentChargeRemaining() == 100) {
		FaceOtherSphere(myState, otherState);
	}

	if (OtherSphereVisible(myState, otherState) == 1){
		ZRRepel();
	}
}
