/*Daniel's code for repel testing

Description: 
After facing the other sphere, if the sphere's charge is 100%, it will zap the opponent.

This does only work for certain initially set positions (if the sphere is away from the sun, it will never reach 100%, right?), which we will test.

Calls: FaceOtherSphere

Usage: Repelling
*/

void ZRUser(float * myState, float * otherState, float time) {
	FaceOtherSphere(myState, otherState);

	if (getPercentChargeRemaining() == 100) {
	ZRRepel();
	}

}
