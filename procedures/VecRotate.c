//rotates a1 towards a2 at an angle of ang in radians. resulting vector in result
//ang must be < the angle between a1 and a2

float VecRotate(float *result, float *a1, float *a2, float ang) {
	
	float u[3];
	float c = cosf(ang);
	float s = sinf(ang);
	float rot[3];
	
	if (ang > Vfunc(8,a1,a2,NULL,0)) {
		return 0.0;
	}
	
	mathVecCross(u,a1,a2);
	mathVecNormalize(u,3);
	rot[0] = (a1[0](c + u[0] * u[0] * (1-c)) + a1[1](u[0] * u[1] * (1-c) - u[2] * s) + a1[2](u[0] * u[2] * (1-c) + u[1] * s));
	rot[1] = (a1[0](u[0] * u[1] * (1-c) + u[2] * s) + a1[1](c + u[1] * u[1] * (1-c)) + a1[2](u[1] * u[2] * (1-c) - u[0] * s));
	rot[2] = (a1[0](u[0] * u[2] * (1-c) - u[1] * s) + a1[1](u[1] * u[2] * (1-c) + u[0] * s) + a1[2](c + u[2] * u[2] * (1-c))); 
	
	if (Vfunc(8,rot,a1,NULL,0) < Vfunc(8,a1,a2,NULL,0) && Vfunc(8,rot,a2,NULL,0) < Vfunc(8,a1,a2,NULL,0)) {	
		c = cosf(-1*ang);
		s = sinf(-1*ang);
		rot[0] = (a1[0](c + u[0] * u[0] * (1-c)) + a1[1](u[0] * u[1] * (1-c) - u[2] * s) + a1[2](u[0] * u[2] * (1-c) + u[1] * s));
		rot[1] = (a1[0](u[0] * u[1] * (1-c) + u[2] * s) + a1[1](c + u[1] * u[1] * (1-c)) + a1[2](u[1] * u[2] * (1-c) - u[0] * s));
		rot[2] = (a1[0](u[0] * u[2] * (1-c) - u[1] * s) + a1[1](u[1] * u[2] * (1-c) + u[0] * s) + a1[2](c + u[2] * u[2] * (1-c)));
	}
	
	memcpy(result,rot,sizeof(float)*3);
	return 1.0;
}