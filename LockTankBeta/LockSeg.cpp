#include "LockSeg.h"

#include <ObjIdl.h>
#include <gdiplus.h>
#include <vector>

#include "definitions.h"

using namespace Gdiplus;

LockSeg::LockSeg(void)
{
}


LockSeg::~LockSeg(void)
{
}

LockSeg::LockSeg(int new_x, int v, float a, float s, float sw)
{
  x=new_x;
  value=v;
  angle=a;
  start_angle=s;
  sweep=sw;
  switch(v)
  {
  case -1:
    TorF='F';
      break;

  case 0:
    TorF='0';
      break;

  case 1:
    TorF='T';
    break;

  default:
    break;
  }
}


//getters---------------------------------------------------


int LockSeg::get_value()
{//get_value() starts
  return value;
}//get_value() ends

float LockSeg::get_angle()
{//get_position() starts
  return angle;
}//get_position() ends

float LockSeg::get_start_angle()
{
  return start_angle;
}

float LockSeg::get_sweep()
{
  return sweep;
}


void LockSeg::set_value(int v)
{//set_value(...) start
  value=v;
}//set_value(...) ends

void LockSeg::set_angle(float a)
{//set_position(...) starts
  angle=a;
}//set_position(...) ends

void LockSeg::set_start_angle(float a)
{
  start_angle=a;
}

void LockSeg::set_sweep(float a)
{
  sweep=a;
}