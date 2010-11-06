//Point in the direction of tangentPoints[2]

target[0] = 0;
target[1] = cosf(tangentPoints[2]);
target[2] = sinf(tangentPoints[2]);

SET_ATTITUDE_TARGET(target);

