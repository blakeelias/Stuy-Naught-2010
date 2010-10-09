/* Description: code for repel tests using ZRPositionTarget
 */

void ZRUser(float * myState, float * otherState, float time) {
	float home[3] = {0,0.3,0};

	if (otherRepelling() == 1) {
		ZRSetPositionTarget(home);
		}

	printf("%i)\n", otherRepelling()); //prints repelling info
	}