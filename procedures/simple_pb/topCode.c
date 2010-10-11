// Copy this to the beginning of your ZRUser() code...

int timeOffset = 0;     // non-zero for ISS, 0 for simulation
G_time = time - timeOffset;
HistFunc(0,myState,otherState,NULL,G_time); // save properties

