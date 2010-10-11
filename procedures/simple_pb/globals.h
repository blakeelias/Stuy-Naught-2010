/* Global variables.  Copy individually into the simulation. Documentation below. */

float history[7596]

int G_time=0

int G_state=0

float ProcVars[200]

/* history will contain all (or at least most) of the relevant properties of each SPHERE for each second.
 * 36 floats * 211 seconds = 7385 elements
 * see HistFunc.c for functions that dump and retrieve this data
 *
 * G_time will always start at 0 (even at the ISS), and will be the nunber of seconds since the beginning of action.  
 * ALWAYS use G_time, never use the system-provided time.
 *
 * G_state will be the major state (current task)
 * see ProcVars.txt for documentation
 *
 * ProcVars will contain the private values needed by the various functions that perform tasks.  Authors of these
 *   function MUST reserve blocks of slots within ProcVars for their exclusive (or shared) use.  You may
 *   reserve these slots by modifying ProcVars.txt
*/

