/* Global Variable: history[width*210]
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
 *
 * See HistValues.txt
 */

void HistDump(float * myState, float * otherState, int time) {
	int width = 35;
	float pos[3] = {0,0,0};
	int k;

	for (k=0; k<3; k++) {
		pos[k] = myState[k];
	}

	for (k=0; k<12; k++) {
		history[width*time+k] = myState[k];
		history[width*time+12+k] = otherState[k];
	}
	history[width*time+24] = iHavePanel();
	history[width*time+25] = otherHasPanel();
	history[width*time+26] = isPanelFound();
	history[width*time+27] = isPanelInSync();
	history[width*time+28] = isStationInSync();
	history[width*time+29] = getCurrentScore();
	history[width*time+30] = getOtherCurrentScore();
	history[width*time+31] = getPercentChargeRemaining();
	history[width*time+32] = getPercentFuelRemaining();
	history[width*time+33] = otherRepelling();
	history[width*time+34] = outsideBoundary(pos);
}

void ZRUser(float * myState, float * otherState, float time) {
	HistDump(myState, otherState, time);
}