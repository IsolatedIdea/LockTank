#include "Tank.h"

int adjust_angle(int angle)
{//adjust_angle(...) starts
  if(angle>360)
  {
    angle=angle-360;
    return angle;
  }
  else if(angle<0)
  {
    
    angle=360+angle;
    return angle;
  }
  else
  {
    return angle;
  }
}//adjust_angle(...) ends