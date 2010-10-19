/* Simpler version of RepelTest.c (which is still in progress).

Description: Test for effects of repelling when SPH1 is at (-.7, 0, 0) and SPH2 is at (.7, 0, 0), or the two centers of the panel initialization circles.

Global Variables: float history[7560] = 0.0
float G_time = 0.0

(both of these are used due to HistFunc.c)

Calls: HistFunc, Vfunc, FaceOtherSphere, OtherSphereVisible (this can later be replaced, I think we have this in HistFunc)

*/

void ZRUser(float * myState, float * otherState, float time){
    float history_portion[36];
    int i;
    HistFunc(0, myState, otherState, NULL, time);
    HistFunc(1, history_portion, &history_portion[12], &history_portion[24], time);
    
    for(i = 0; i < 36; i++) {
        printf("%f", history_portion[i]);
        if (i % 36) printf(",");
        else printf("\n");
    }
    
FaceOtherSphere(myState, otherState);
//}
if (OtherSphereVisible(myState, otherState) == 1){
	ZRRepel();
}

}
