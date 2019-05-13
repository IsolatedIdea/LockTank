#pragma once

#include <ObjIdl.h>
#include <gdiplus.h>

class Tank
{
private:
  int angle;
  int x;
  int y;
  char move;
public:
  Tank(void);
  ~Tank(void);
  Tank(int new_x, int new_y, int new_angle);

  //Getters and Setters
  int get_x();
  int get_y();
  int get_angle();
  char get_move();

  void set_x(int new_x);
  void set_y(int new_y);
  void set_angle(int new_angle);
  void set_move(char m);

  //functions
  void DrawTank(HDC hdc);
  void update_tank();
  bool HitTank();
};

