#include "Tank.h"
#include "definitions.h"
#include "Controls.h"

#include <gdiplus.h>
#include <ObjIdl.h>

using namespace Gdiplus;

Tank::Tank(void)
{
}


Tank::~Tank(void)
{
}

Tank::Tank(int new_x, int new_y, int new_angle)
{//Tank(...) starts
  x=new_x;
  y=new_y;
  angle=new_angle;
  move='S';
}//Tank(...) ends


//Getters and setters----------------------------------
int Tank::get_x()
{//get_y starts
  return x;
}//get_x ends

int Tank::get_y()
{//get_y starts
  return y;
}//tet_y ends

int Tank::get_angle()
{//get_angle() starts
  return angle;
}//get_angle() ends

char Tank::get_move()
{
  return move;
}

void Tank::set_x(int new_x)
{//set_x(...) starts
  x=new_x;
}//Set_X(...) ends

void Tank::set_y(int new_y)
{//set_y(...) starts
  x=new_y;
}//Set_y(...) ends

void Tank::set_angle(int new_angle)
{//set_angle(...) starts
  angle=new_angle;
}//Set_angle(...) ends

void Tank::set_move(char m)
{
  move=m;
}


//Functions-----------------------------------------------
void Tank::DrawTank(HDC hdc)
{//DrawTank(...) starts
  Graphics tank(hdc);
  Pen pen(Color(255, 0, 0, 0));
  SolidBrush tank_brush(Color(255, 50, 50, 50));
  GraphicsPath path;

  //check to see if we need to update
  update_tank();

  //move-scale-rotate
  
  //PointF tank_pointsA[]={
  //  PointF(10, 2),
  //  PointF(35, 0),
  //  PointF(35, -10),
  //  PointF(25, -20),
  //  PointF(10, -20),
  //  PointF(10, -30),
  //  PointF(-10, -30),
  //  PointF(-10, -20),
  //  PointF(-25, -20),
  //  PointF(-35, -10),
  //  PointF(-35, 0),
  //  PointF(-10, 2),
  //  PointF(10 , 2)};

  PointF tank_pointsA[]={
    PointF(2, 10),
    PointF(0, 35),
    PointF(-10, 35),
    PointF(-20, 25),
    PointF(-20, 10),
    PointF(-30, 10),
    PointF(-30, -10),
    PointF(-20, -10),
    PointF(-20, -25),
    PointF(-10, -35),
    PointF(0, -35),
    PointF(2, -10),
    PointF(2 , 10)};

    //draw hit cone
    Pen temp(Color(255, 0, 0, 0));
  //  int start_outer=90+angle-7;
  //  int sweep_outer=14;

  //  int start_between=90+angle-5;
  //  int sweep_between=10;

  //  int start_inner=90+angle-2;
  //  int sweep_inner=4;
  //  
  //tank.TranslateTransform(ORIGIN_X, ORIGIN_Y, MatrixOrderAppend);
  //  tank.DrawPie(&temp,
  //                -BOARD_WIDTH/2,
  //                -BOARD_HEIGHT/2,
  //                BOARD_WIDTH,
  //                BOARD_HEIGHT,
  //                start_outer,
  //                sweep_outer);

  //  tank.DrawPie(&temp,
  //                -BOARD_WIDTH/2,
  //                -BOARD_HEIGHT/2,
  //                BOARD_WIDTH,
  //                BOARD_HEIGHT,
  //                start_between,
  //                sweep_between);
  //  
  //  tank.DrawPie(&temp,
  //                -BOARD_WIDTH/2,
  //                -BOARD_HEIGHT/2,
  //                BOARD_WIDTH,
  //                BOARD_HEIGHT,
  //                start_inner,
  //                sweep_inner);
  //tank.DrawLine(&temp, 0, 0, 0, -600);
  //tank.DrawLine(&temp, 0, 0, 600, 0);
  //  
  //tank.TranslateTransform(-ORIGIN_X, -ORIGIN_Y, MatrixOrderAppend);

  //tank.DrawLines(&pen, tank_points, 10);
  path.AddLines(tank_pointsA, 13);

  
  //tank.TranslateTransform(ORIGIN_X, ORIGIN_Y, MatrixOrderAppend);
  tank.TranslateTransform(-6,0, MatrixOrderAppend);
  tank.TranslateTransform(x, y, MatrixOrderAppend);
  tank.RotateTransform(angle, MatrixOrderAppend);
  tank.TranslateTransform(ORIGIN_X, ORIGIN_Y, MatrixOrderAppend);

  //draw the tank
  tank.FillPath(&tank_brush, &path);
  tank.DrawPath(&pen, &path);

  


  
  //tank.TranslateTransform(-ORIGIN_X, ORIGIN_Y, MatrixOrderAppend);
  //tank.RotateTransform(-angle, MatrixOrderAppend);
  //tank.TranslateTransform(-x, -y, MatrixOrderAppend);
  //tank.TranslateTransform(0,6, MatrixOrderAppend);
}//DrawTank(...) ends

void Tank::update_tank()
{
  switch(move)
  {
  case 'L':
    angle=adjust_angle(angle+TANK_SPEED);
    break;
  case 'S':
    break;
  case 'R':
    
    angle=adjust_angle(angle-TANK_SPEED);
    break;
  default:
    break;
  }

}

bool Tank::HitTank()
{//HitTank() starts
  return false;
}//HitTank() ends