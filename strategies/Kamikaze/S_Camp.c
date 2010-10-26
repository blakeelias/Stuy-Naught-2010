//Code to go camping towards the center

DEBUG(("currently camping\n"));


target[0] = target[1] = target[2] = 0;

SET_POSITION_TARGET(target);

if (Vfunc(6,myState,target,NULL,0) < .1){
	state = STATE_POSTCAMP;
break;
}