#include "Turret.h"
#include "definitions.h"
#include "Controls.h"
#include "Tank.h"

#include <ObjIdl.h>
#include <gdiplus.h>

using namespace Gdiplus;

Turret::Turret(void)
{
}


Turret::~Turret(void)
{
}

Turret::Turret(float a, Tank tank, char d)
{
  turret_angle=a;
  tank_angle=tank.get_angle();
  dir=d;
}

float Turret::get_turret_angle()
{
  return turret_angle;
}

float Turret::get_tank_angle()
{
  return tank_angle;
}

void Turret::set_turret_angle(float a)
{
  turret_angle=a;
}

void Turret::set_tank_angle(float a)
{
  tank_angle=a;
}

void Turret::update_turret(Tank tank)
{
  turret_angle=tank.get_angle();
}

void Turret::draw_turret(HDC hdc, Tank tank)
{
  Graphics turret(hdc);
  Pen pen(Color(255, 0, 100, 0));
  SolidBrush turret_brush(Color(255, 0, 100, 0));
  GraphicsPath path;

  update_turret(tank);PointF turret_points[]={PointF(20, 0),
                          PointF( 20, 0),
                          PointF( 80, 0),
                          PointF(100, 20),
                          PointF(60, 40),
                          PointF(100, 40),
                          PointF(100, 60),
                          PointF(60, 60),
                          PointF(100, 80),
                          PointF(80, 100),
                          PointF(20, 100),
                          PointF(0, 80),
                          PointF(0, 20)};

  //move-scale-rotate
  turret.TranslateTransform(-50,-50, MatrixOrderAppend);
  turret.RotateTransform(turret_angle, MatrixOrderAppend);
  turret.TranslateTransform(ORIGIN_X, ORIGIN_Y, MatrixOrderAppend);


  //turret.DrawLines(&pen, turret_points, 10);
  path.AddLines(turret_points, 13);
  turret.FillPath(&turret_brush, &path);
  turret.DrawPath(&pen, &path);

  //turret.TranslateTransform(-ORIGIN_X, -ORIGIN_Y, MatrixOrderAppend);
  //turret.RotateTransform(-turret_angle, MatrixOrderAppend);
  //turret.TranslateTransform(50, 50, MatrixOrderAppend);
}

void Turret::target_tank()
{
}