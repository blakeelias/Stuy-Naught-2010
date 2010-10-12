// Rotation Procedure 
// Assumes that we are starting at center of the pannel initialization circle.
// I have tested two possible techniques to achieving a near-constant rotate 
// rate. They will be explained in comments below

// Abhimanyu Ghosh - 10/12/10 @ 12:59 A.M.


void rotate_closedLoop(int param_t) {

// Rotates by parametrically assigning the y and z components of the attitude vector. The x attitude component obviously
// remains 0;
// Observed and unexpected behavior: Appears that although I assign attitude targets with y and z components only, the sphere 
// also rotates about the y component (therefore creating a non-zero x attitude component)... 
// Nevertheless, leaning towards this method as more reliable and foolproof...

float PI = 4 * atan(1);
float rotation_rate_k = 10.05; // higher k-value = faster (?) rotation...
float set_x = 0;
float set_y = cos(rotation_rate_k * param_t * PI / 180);
float set_z = -sin(rotation_rate_k * param_t * PI / 180);
float set[3] = {set_x, set_y, set_z};
printf("%d, %f, %f, %f, %f \n", param_t, PI, set[0], set[1], set[2]);
ZRSetAttitudeTarget(set);
}

void alignToPlusY() {
	// Performs initial alignment to +Y axis prior to rotateTau()
	// Requires a "stage" global variable initialized to 0;
	// In my case, this came before stage 3, hence the assignment to the number 3;
	
	float attTarget[3] = {0.0, 1.0, 0.0};
	ZRSetAttitudeTarget(attTarget);
	if (Vfunc(8, att1Target, myState+6, NULL, 0) < 0.75) {
		stage = 3; // Ties in to stage global variable effective / used in ZRUser().
	}
}

void rotateTau() {
	// Rotates about the x-axis by applying a torque of 0.025 N*m (?)
	// Requires an int tauSet to be set to 1 and a float correctPos to be set to 1.0;
	// Somewhat more unstable... depends on the previous performance of an attitude alignment being within a given bound
	// Sometimes the above mentioned alignment exceeds given time limits..
	// If alignment goes smoothly however, this function seems to work pretty well... but that's a big "if".
	
	float tau[3] = {0.0, 0.025, 0.0};
	if (correctPos < 2) {
		ZRSetPositionTarget(a);
		correctPos += 1.0;
	}
	if (tauSet == 1) {
		ZRSetTorques(tau);
		tauSet = 0;
	}
}