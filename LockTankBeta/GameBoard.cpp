#include "GameBoard.h"
#include <ObjIdl.h>
#include <gdiplus.h>
#include "definitions.h"

using namespace Gdiplus;


GameBoard::GameBoard(void)
{
}


GameBoard::~GameBoard(void)
{
}

GameBoard::GameBoard(int o_x, int o_y)
{
  //SetViewportOrgEx(hdc, o_x, o_y, NULL);
}

void GameBoard::DrawBoard(HDC hdc, int width, int height, int screenx, int screeny)
{//DrawBoard(...) starts
  Graphics board(hdc);
  //create pens
  Pen pen(Color(255, 0, 130, 255), 8);
  SolidBrush back_brush(Color(255, 0, 0, 0));

  //draw a black background
  board.FillRectangle(&back_brush, 0, 0, screenx, screeny);

  board.TranslateTransform(ORIGIN_X, ORIGIN_Y);
  //draw the primary gameboard
  board.DrawEllipse(&pen, -(width/2), -(height/2), width, height);
}//DrawBoard(...) ends