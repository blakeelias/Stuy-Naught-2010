/*
 * Simulation Settings:
 *     Simulate as: SPH1
 *     Maximum time: 30 seconds
 *     Position (randomly set from game):
 *         SPH1: X=0, Y=0.15569456, Z=0.31167573
 *         SPH2: X=0, Y=-0.15569456, Z=-0.31167573
 *
 * Output:
    0.348400
    0.696800
    0.696800
    0.696800
    0.696800
    0.696800
    0.696800
    0.696800
    0.696800
    0.696800
    0.696800
    0.696800
    0.696800
    0.696800
    0.696800
    0.696800
 *
 * Behavior:
 *     The two SPHERES start out close to each other, then jump to their points
 *     on the initialization circle after the first second.  They stay in place
 *     the rest of the match, with a distance twice their initial distance, or
 *     the diameter of the circle.
 */

float Distance(float * myState, float * otherState) {
    float dist = 0;
    int k;

    for (k=0; k<3; k++)
        dist += pow(otherState[k] - myState[k] , 2);
    dist = sqrt(dist);

    return dist;
}

void ZRUser(float * myState, float * otherState, int time) {
    printf("%f\n", Distance(myState, otherState));
}
