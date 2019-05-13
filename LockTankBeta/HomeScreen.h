#pragma once

#include <ObjIdl.h>
#include <gdiplus.h>

class HomeScreen
{
private:
  int height;
  int width;

public:
  HomeScreen(void);
  ~HomeScreen(void);
  HomeScreen(int h, int w);

  int get_height();
  int get_width();

  void set_height(int h);
  void set_width(int w);

  void draw_homescreen(HDC hdc);
  void draw_alpha_layer(HDC hdc);
  void draw_level_change(HDC hdc);
  void draw_death_screen(HDC hdc);
  void draw_credits(HDC hdc);
};

