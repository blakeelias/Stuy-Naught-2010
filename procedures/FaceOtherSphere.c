/* Function: 
 *	void FaceOtherSphere(float * myState, float * otherState)
 *	
 * Description: 
 *	A function that uses ZRSetAttitudeTarget to face the other sphere
 *
 * Inputs: myState, otherState
 *
 * Outputs: None
 *
 * Usage: Repelling, Deflecting Repelling
 *	void ZRUser(float * myState, float * otherState, float time) {
 *		FaceOtherSphere(myState, otherState);
 *	}
*/

void FaceOtherSphere(float * myState, float * otherState) {
  float attTarget[3];
  Vfunc(2, otherState, myState, attTarget, 0); //take the difference
  ZRSetAttitudeTarget(attTarget);
}
