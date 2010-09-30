/*
 * Inputs:
 *    Vec: An array of 3 floats (pointer)
 *         The vector you want to 'normalize'
 *    len: A float
 *         The length of the resultant vector
 *
 * Outputs:
 *    Original vector is modified
 *    no returns
 *
 * Description of behavior:
 *    Given a 3D vector of a certain length, this will be able to
 *    lengthen/shrink the vector to your specified length (len).
 *    
 * Uses:
 *    Calculate the velocity vector to pass to ZRSetVelocityTarget given an attitude and distance
 *    Normalize Attitude for ZRSetAttitudeTarget
 *
 * Example:
 *    Given your starting position as {0,.25,.25}, you can calculate the velocity vector to
 *    the center of the panel's initialization circle at 2cm/s.
 *
 *    float start[3] = {0,.25,.25};
 *    float end[3] = {.7,0,0};
 *    float vel[3] = {0,0,0};
 *    int i;
 *    for (i=0;i<3;i++) {
 *        vel[i] = end[i] - start[i];
 *    }
 *    VecNorm(vel,.02);
 *    ZRSetVelocityTarget(vel);
 * 
 */

void VecNorm(float * Vec, float len) {
	//create a local variable to hold the original length
	float dist = 0;
	//calculates the square of the length through sum of squares
	int k;
	for (k=0;k<3;k++) {
		dist = (dist + pow(Vec[k],2));
	}
	//finds the reletive length
	dist = sqrt(dist);
	dist = (dist/len);
	//shrinks/lengthens the vector accordingly
	for (k=0;k<3;k++) {
		Vec[k] = (Vec[k]/dist);
	}
}
