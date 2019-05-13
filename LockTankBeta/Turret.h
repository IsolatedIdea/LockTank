#pragma once
#include "Tank.h"

class Turret
{
private:
  float turret_angle;
  float tank_angle;
  char dir;
public:
  Turret(void);
  ~Turret(void);

  Turret(float a, Tank tank, char d);

  float get_turret_angle();
  float get_tank_angle();

  void set_turret_angle(float a);
  void set_tank_angle(float a);

  void update_turret(Tank tank);
  void draw_turret(HDC hdc, Tank tank);

  void target_tank();
};

