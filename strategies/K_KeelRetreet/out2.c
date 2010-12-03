float Vfunc(int which, float* v1, float* v2, float* vresult, float scalar)
{
 int i = 0;
 float fTmp[3];
 if (which == 2) { // vresult = v1 - v2
  for (; i < 3; i++)
   vresult[i] = v1[i] - v2[i];
 }
 if (which == 4) { // vresult = scalar * v1
  for (; i < 3; ++i)
   vresult[i] = scalar * v1[i];
 }
 if (which == 6) { // returns distance between v1 and v2
  Vfunc(2, (v1), (v2), (fTmp), 0); // fTmp = v1 - v2
  return mathVecMagnitude((fTmp), 3);
 }
 if (which == 8)
  return acosf(mathVecInner((v1), (v2), 3)/(mathVecMagnitude((v1), 3) * mathVecMagnitude((v2), 3)))*180.0/PI;
 if (which == 9)
 { // unit vector pointing from v1 toward v2
  Vfunc(2, (v2), (v1), (vresult), 0);
  mathVecNormalize((vresult), 3);
 }
 return 0;
}
