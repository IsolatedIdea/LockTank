#pragma once
#include <ObjIdl.h>
#include <gdiplus.h>
#include <vector>

using namespace std;

class LockSeg
{
private:
  float x;
  int value;
  char TorF;
  float angle;
  float start_angle;
  float sweep;

public:
  //constructors
  LockSeg(void);
  ~LockSeg(void);

  LockSeg(int new_x, int v, float a, float s, float sw);

  int get_value();
  char get_T0rF();
  float get_angle();
  int get_x();
  float get_start_angle();
  float get_sweep();

  void set_value(int v);
  char set_T0rF(char tf);
  void set_angle(float a);
  void set_x(float new_x);
  void set_start_angle(float a);
  void set_sweep(float a);
};

