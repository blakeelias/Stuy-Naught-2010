//Point in the direction of tangentPoints[2]

target_att[0] = 0;
target_att[1] = cosf(tangentPoints[2]);
target_att[2] = sinf(tangentPoints[2]);

SET_ATTITUDE_TARGET(target_att);

