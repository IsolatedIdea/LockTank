#include "Shell.h"
#include "definitions.h"

#include <ObjIdl.h>
#include <gdiplus.h>

using namespace Gdiplus;

Shell::Shell(void)
{
}


Shell::~Shell(void)
{
}

Shell::Shell(int v, float new_x, float new_y, float a)
{//Shell(...) starts
  value=v;
  x=new_x;
  y=new_y;
  angle=a;
}//Shell(...) ends
//getters and setters

float Shell::get_value()
{//get_value() starts
  return value;
}//get_value ends

float Shell::get_x()
{//get_x() starts
  return x;
}//get_y() ends

float Shell::get_y()
{//get_y() starts
  return y;
}//get_y() ends

float Shell::get_angle()
{//get_angle() starts
  return angle;
}//get_angle() ends

void Shell::set_value(int v)
{//set_value(...) starts
  value=v;
}//set_value(...) ends

void Shell::set_x(float new_x)
{//set_x(...) starst
  x=new_x;
}//set_x(...) ends
void Shell::set_y(float new_y)
{//set_y(...) starts
  y=new_y;
}//set_y(...) ends
void Shell::set_angle(float a)
{//set_angle(...) starts
  angle=a;
}//set_amg;e(...) ends

//Functions-----------------------------------------------
void Shell::draw_shell(HDC hdc)
{//DrawTank(...) starts
  Graphics shell(hdc);
  GraphicsPath path;
  Pen shell_pen(Color(255, 255, 255, 255));
  SolidBrush shell_brush(Color(255, 255, 255, 255));
  //points that make up the shell
  PointF tank_shell[]={PointF(0, 0),
                        PointF(5, 5),
                        PointF(15, 5),
                        PointF(15, -5),
                        PointF(5, -5),
                        PointF(0, 0)};

  PointF Turret_shell[]={PointF(0, 0),
                        PointF(-5, 5),
                        PointF(-15, 5),
                        PointF(-15, -5),
                        PointF(-5, -5),
                        PointF(0, 0)};

  //move-scale-rotate
  shell.TranslateTransform(x, y, MatrixOrderAppend);
  shell.RotateTransform(angle, MatrixOrderAppend);
  shell.TranslateTransform(ORIGIN_X, ORIGIN_Y, MatrixOrderAppend);

  switch(value)
  {
  case -1:
    //False Tank shell - set colour to red
    shell_pen.SetColor(Color(255, 255, 0, 0));
    shell_brush.SetColor(Color(255, 255, 0, 0));
    path.AddLines(tank_shell, 6);
    shell.FillPath(&shell_brush, &path);
    shell.DrawPath(&shell_pen, &path);
    break;

  case 0:
    //Turret shell - set colour to white
    shell_pen.SetColor(Color(255, 255, 255, 255));
    shell_brush.SetColor(Color(255, 0, 0, 0));
    path.AddLines(Turret_shell, 6);
    shell.FillPath(&shell_brush, &path);
    shell.DrawPath(&shell_pen, &path);
    break;
    
  case 1:
    //True Tank shell - set colour to green
    shell_pen.SetColor(Color(255, 0, 255, 0));
    shell_brush.SetColor(Color(255, 0, 255, 0));
    path.AddLines(tank_shell, 6);
    shell.FillPath(&shell_brush, &path);
    shell.DrawPath(&shell_pen, &path);
    break;
    
  default:
    break;
  }
}//DrawTank(...) ends

bool Shell::update_position()
{//update_position() starts
  switch(value)
  {
  case -1:
    x=x-TANK_SHELL_SPEED;
    if(x<(LOCK_WIDTH/2)-10)
    {
      return false;
    }
    break;
  case 0:
    x=x+TURRET_SHELL_SPEED;
    if(x>BOARD_WIDTH/2)
    {
      return false;
    }
    break;
  case 1:
    x=x-TANK_SHELL_SPEED;
    if(x<(LOCK_WIDTH/2)-10)
    {
      return false;
    }
    break;

  default:
    break;
  }

  return true;
}//update_poistion() ends