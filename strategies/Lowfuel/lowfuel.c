float cfuel;
float stop[3] = {0,0,0};
//float end[3] = {.7,0,0};

cfuel = getPercentFuelRemaining();
DEBUG(("Time:%f , Fuel:%f\n",time,cfuel));

if (cfuel > 10) {
//our code here

//if (time < 25)
//ZRSetPositionTarget(end);
//if ((time > 25) && (time < 50))
//ZRSetPositionTarget(stop);
//if ((time > 50) && (time < 75))
//ZRSetPositionTarget(end);
//if ((time > 75) && (time < 100))
//ZRSetPositionTarget(stop);
//if ((time > 100) && (time < 125))
//ZRSetPositionTarget(end);

}

else {
ZRSetVelocityTarget(stop);
}