/*Daniel's code for repel testing

Description: 
After facing the other sphere, if the sphere's charge is 100%, it will zap the opponent.

Calls: FaceOtherSphere

Usage: Repelling
*/

void ZRUser(float * myState, float * otherState, float time) {
	FaceOtherSphere(myState, otherState);

	if ((getPercentChargeRemaining() == 100) && (maxChargeAchieved != 1)) { 
	maxChargeAchieved = 1;
	}

	if (maxChargeAchieved == 1) {
	ZRRepel();
	}

}
