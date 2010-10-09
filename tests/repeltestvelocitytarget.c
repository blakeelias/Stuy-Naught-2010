/* Description: code for repel tests using ZRVelocityTarget
 */

void ZRUser(float * myState, float * otherState, float time) {
	float vnaught[3] = {0,-0.5,0};
	
	if (otherRepelling() == 1) {
		ZRSetVelocityTarget(vnaught);
		}
	
	printf("%i)\n", otherRepelling()); //prints repelling info
}

