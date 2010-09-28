/* Global Variable: history[7350]
 *
 * Inputs:
 *    part:  An array of 'len' number of floats (pointer)
 *           The array you wish to replace with a certain part from the history
 *    time:  An integer
 *           The time in which you want to get information from
 *    start: An integer
 *           The starting history 'value'
 *    len:   An integer
 *           The length of the part you want 
 *
 * Outputs:
 *    Original array is set to a sequence from the history
 *    no returns
 *
 * Description of behavior:
 *    Allows you to copy out a segment of the history to use    
 *
 * Example:
 *    If you wanted the myState array at time = 15: 
 *
 *    float State15[12];
 *    HistRetrieve(State15,15,0,12);
 * 
 * See HistValues.txt
 */

void HistRetrieve(float * part, int time,int start, int len) {
	int k;
	//replaces the array with information from the history
	for (k=0; k<len; k++) {
		part[k] = history[35*time+start+k];
	}
}
