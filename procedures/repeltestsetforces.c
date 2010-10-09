/* Description: code for repel tests using ZRSetForces
 */

void ZRUser(float * myState, float * otherState, float time) {
	float maxforce[3] = {0.0,-0.04,0.0};
	
	if (otherRepelling() == 1) {
		ZRSetForces(maxforce);
		}
	
	printf("%i)\n", otherRepelling()); //prints repelling info
}