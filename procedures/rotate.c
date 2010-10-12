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

void rotateTau() {
	// Rotates about the x-axis by applying a torque of 0.025 N*m (?)
	// Requires an int tauSet to be set to 1 and a float correctPos to be set to 1.0;
	
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