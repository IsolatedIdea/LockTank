#pragma once

//includes
#include <ObjIdl.h>
#include <gdiplus.h>


class GameBoard
{
private:
  int board_width;
  int board_height;
  int origin_x;
  int origin_y;

  HDC hdc;

public:
  GameBoard(void);
  GameBoard(int o_x, int o_y);
  ~GameBoard(void);

  void DrawBoard(HDC hdc, int width, int height, int screnx, int screeny);
};
