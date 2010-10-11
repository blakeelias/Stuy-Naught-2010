/*
 * Function: float Vfunc(int which, float *v1, float *v2, float *vresult, float scalar)
 *   A Jack-of-all-trades vector function.
 *   Input variables:
 *     which: chooses the vector function to compute
 *     v1,v2: input vectors:  float v1[3], v2[3]
 *     vresult: output vector, float vresult[3]
 *     scalar: input scalar
 *
 *  Note: some arguments are ignored for some functions, and so can be given the value NULL
 * 
 *  Assume, for documentation below, the following variables are already declared:
 *      float a1[3], a2[3], a3[3], s;
 *
 *  Functions:
 *    Length of vector: 
 *       which == 0: returns |v1| (= length of v1)
 *       s = Vfunc(0,a1,NULL,NULL,0); // returns length(a1)
 *
 *    Adding vectors:
 *       which == 1: vresult = v1 + v2
 *       Vfunc(1,a1,a2,a3,0);  // a3 = a1 + a2
 *
 *    Subtracting vectors:
 *       which == 2: vresult = v1 - v2
 *       Vfunc(2,a1,a2,a3,0);  // a3 = a1 - a2
 *
 *    Unit vector:
 *       which == 3: vresult = unit vector in direction of v1
 *       if s = Vfunc(3,a1,NULL,a3,0); // a3 = a1 / |a1|
 *       Note: returns 0.0 if |a1| == 0, then sets a3 to the zero vector
 *             returns 1.0 under normal circumstances
 *
 *    Scalar times vector:
 *       which == 4: vresult = s * v1
 *        Vfunc(4,a1,NULL,a3,s);  // a3 = s * a1
 *
 *    Dot product:
 *       which == 5: returns v1 * v2
 *       s = Vfunc(5,a1,a2,a3,0);  // returns dot product of a1 and a2
 *
 *    Distance between two vectors (as positions):
 *       which == 6: returns |v1-v2|
 *       s = Vfunc(6,a1,a2,NULL,0);  // s = length(a1-a2)
 *
 *    Copy a vector:
 *       which == 7: copies v1 to vresult:
 *       Vfunc(7,a1,NULL,a3,0);  // copies vector a1 to a3
 *       Note: for instance, this can copy the velocities in myState (starting at myState[3]) to
 *       vresult using Vfunc(7,myState+3,NULL,vresult,0);
 *
 *    Angle between 2 vectors (in degrees, not radians):
 *       which == 8: returns angle between v1 and v2
 *       float angle = Vfunc(8,a1,a2,NULL,0);
 *
 *    Unit vector pointing from v1 to v2:
 *       which == 9: vresult is the unit vector pointing from position v1 toward position v2
 *       Vfunc(9,a1,a2,a3,0);   // a3 will be the unit vector
*/

/* Copy function header:

float Vfunc(int which, float *v1, float *v2, float *vresult, float scalar)

{

*/

	int i;
	
	if (which == 0) // returns |v1|
		return sqrt(Vfunc(5,v1,v1,NULL,0));

	if (which == 1) { // vresult = V1 + v2
		for (i = 0; i < 3; ++i)
			vresult[i] = v1[i] + v2[i];
		return 0;
	}

	if (which == 2) { // vresult = v1 - v2
		for (i = 0; i < 3; ++i)
			vresult[i] = v1[i] - v2[i];
		return 0;
	}

	if (which == 3) { // vresult = v1 / |v1|; if |v1| == 0, returns 0, else 1
		float s = Vfunc(0,v1,NULL,NULL,0);
		if (s == 0.0)
			return 0.0;
		Vfunc(4,v1,NULL,vresult,1.0/s);
		return 1.0;
	}

	if (which == 4) { // vresult = scalar * v1
		for (i = 0; i < 3; ++i)
			vresult[i] = scalar * v1[i];
		return 0;
	}

	if (which == 5) { // returns dot product: v1 * v2
		float s2 = 0;
		for (i = 0; i < 3; ++i)
			s2 += v1[i] * v2[i];
		return s2;
	}

	if (which == 6) { // returns distance between v1 and v2
		float v3[3];
		Vfunc(2,v1,v2,v3,0);  // v3 = v1 - v2
		return Vfunc(0,v3,NULL,NULL,0);
	}

	if (which == 7) { // copies v1 to vresult
		for (i = 0; i < 3; ++i)
			vresult[i] = v1[i];
		return 0;
	}

	if (which == 8) { // angle between two vectors
	    float dot = Vfunc(5,v1,v2,NULL,0)/(Vfunc(0,v1,NULL,NULL,0)*Vfunc(0,v2,NULL,NULL,0));
	    return acos(dot)*180.0/3.14159265;
	}

	if (which == 9) { // unit vector pointing from v1 toward v2
	    float v9[3];
	    Vfunc(2,v2,v1,v9,0);
	    return Vfunc(3,v9,NULL,vresult,0);
	}
	
//}

