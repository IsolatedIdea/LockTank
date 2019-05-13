#pragma once

#include <ObjIdl.h>
#include <gdiplus.h>

class Shell
{
private:
  int value;
  float x;
  float y;
  float angle;
public:
  Shell(void);
  ~Shell(void);

  Shell(int v, float new_x, float new_y, float a);

  //getters and setters
  float get_value();
  float get_x();
  float get_y();
  float get_angle();

  void set_value(int v);
  void set_x(float new_x);
  void set_y(float new_y);
  void set_angle(float a);

  //functions
  void draw_shell(HDC hdc);
  bool update_position();
};

