/* Global Variable: history[7350]
 * 
 * Inputs:
 *    Same inputs as the ZRUser Procedure
 *
 * Outputs:
 *    History is modified
 *    no returns
 *
 * Description of behavior:
 *    Add to the beginning of main ZRUser procedure to run every second
 *    HistDump(myState, otherState, time);
 *
 * See HistValues.txt
 */

void HistDump(float * myState, float * otherState, int time) {
	float pos[3] = {0,0,0};
	int k;

	for (k=0; k<3; k++) {
		pos[k] = myState[k];
	}

	for (k=0; k<12; k++) {
		history[35*time+k] = myState[k];
		history[35*time+12+k] = otherState[k];
	}
	history[35*time+24] = iHavePanel();
	history[35*time+25] = otherHasPanel();
	history[35*time+26] = isPanelFound();
	history[35*time+27] = isPanelInSync();
	history[35*time+28] = isStationInSync();
	history[35*time+29] = getCurrentScore();
	history[35*time+30] = getOtherCurrentScore();
	history[35*time+31] = getPercentChargeRemaining();
	history[35*time+32] = getPercentFuelRemaining();
	history[35*time+33] = otherRepelling();
	history[35*time+34] = outsideBoundary(pos);
}
