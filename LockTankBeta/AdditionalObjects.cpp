
#include <ObjIdl.h>
#include <gdiplus.h>

using namespace Gdiplus;
//------------------------------------------------------------------

void DrawCross(HDC hdc, float x, float y)
{//DrawCross(...) starts
  Graphics graphics(hdc);

  Pen pen(Color(255, 255, 0, 0), 1);

  //move-scale-rotate
  graphics.TranslateTransform(-6,-6);

  graphics.TranslateTransform(x, y);

  graphics.DrawEllipse(&pen, 4, 4, 4, 4);
  graphics.DrawLine(&pen, Point(6,0), Point(6,11));
  graphics.DrawLine(&pen, Point(0,6), Point(11,6));
}//DrawCross(...) ends

void DrawCrossRotateAroundPoint(HDC hdc, float x, float y)
{//DrawCross(...) starts
  Graphics graphics(hdc);

  Pen pen(Color(255, 255, 255, 255), 1);

  //move-scale-rotate
  graphics.TranslateTransform(-6,-6);

  graphics.TranslateTransform(x, y, MatrixOrderAppend);
  graphics.RotateTransform(-45, MatrixOrderAppend);

  graphics.DrawEllipse(&pen, 4, 4, 4, 4);
  graphics.DrawLine(&pen, Point(6,0), Point(6,11));
  graphics.DrawLine(&pen, Point(0,6), Point(11,6));
}//DrawCross(...) ends