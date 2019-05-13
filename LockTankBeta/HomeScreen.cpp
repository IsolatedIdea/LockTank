#include "HomeScreen.h"

#include <ObjIdl.h>
#include <gdiplus.h>

using namespace Gdiplus;


HomeScreen::HomeScreen(void)
{
}


HomeScreen::~HomeScreen(void)
{
}

HomeScreen::HomeScreen(int h, int w)
{
  height=h;
  width=w;
}
int HomeScreen::get_height()
{
  return height;
}

int HomeScreen::get_width()
{
  return width;
}

void HomeScreen::set_height(int h)
{
  height=h;
}

void HomeScreen::set_width(int w)
{
  width=w;
}

void HomeScreen::draw_homescreen(HDC hdc)
{
  Graphics home_screen(hdc);
  Pen title_pen(Color(150, 0, 130, 255),10);
  SolidBrush back_brush(Color(255, 0, 0, 0));

  //draw a black background
  home_screen.FillRectangle(&back_brush, 0, 0, width, height);

  //display messages
  FontFamily font_family(L"Arial");
  Font font_title(&font_family, 48, FontStyleBold, UnitPixel);
  PointF point(100, 100);
  SolidBrush text(Color(255, 0, 130, 255));

  home_screen.DrawString(L"Lock-Tank", -1, &font_title, point, &text);

  home_screen.DrawRectangle(&title_pen, 80, 80, 300, 100);

  //instructions
  
  //display messages
  Font font_heading(&font_family, 24, FontStyleBold, UnitPixel);
  Font font(&font_family, 15, FontStyleBold, UnitPixel);
  PointF heading(100, 220);
  PointF line1(100, 250);
  PointF line2(100, 270);
  PointF line3(100, 290);
  PointF line4(100, 310);
  PointF line5(100, 330);
  PointF line6(100, 350);
  PointF oops_forgot(100, 390);

  home_screen.DrawString(L"Controls", -1, &font_heading, heading, &text);
  home_screen.DrawString(L"Left:  Z", -1, &font, line1, &text);
  home_screen.DrawString(L"Right: X", -1, &font, line2, &text);
  home_screen.DrawString(L"Fire Green: N", -1, &font, line3, &text);
  home_screen.DrawString(L"Fire Red:  M", -1, &font, line4, &text);
  home_screen.DrawString(L"Exit back to start screen: Q", -1, &font, line5, &text);
  home_screen.DrawString(L"Exit Game (From Start Screen):  Q", -1, &font, line6, &text);
  
  home_screen.DrawString(L"Start Game: S", -1, &font, oops_forgot, &text);

  home_screen.DrawRectangle(&title_pen, 80, 200, 300, 220);

  PointF description_title(420, 220);
  PointF line7(420, 250);
  PointF line8(420, 270);
  PointF line9(420, 290);
  PointF line10(420, 310);
  PointF line11(420, 330);
  PointF line12(420, 350);
  PointF line13(420, 370);
  PointF line14(420, 390);

  home_screen.DrawString(L"Description", -1, &font_heading, description_title, &text);
  home_screen.DrawString(L"Break the code to beat the level!", -1, &font, line7, &text);
  home_screen.DrawString(L"< = AND", -1, &font, line8, &text);
  home_screen.DrawString(L"> = OR", -1, &font, line9, &text);
  home_screen.DrawString(L"| = NOT", -1, &font, line10, &text);
  home_screen.DrawString(L"( = Start of combination", -1, &font, line11, &text);

  home_screen.DrawString(L"Watch out for the Turret! And remember:", -1, &font, line13, &text);
  home_screen.DrawString(L"Not all things in this world are the same way up...", -1, &font, line14, &text);

  home_screen.DrawRectangle(&title_pen, 400, 200, 400, 220);
}

void HomeScreen::draw_alpha_layer(HDC hdc)
{
  Graphics home_screen(hdc);
  SolidBrush back_brush(Color(200, 0, 0, 0));

  //draw a black background
  home_screen.FillRectangle(&back_brush, 0, 0, width, height);

}


  void HomeScreen::draw_level_change(HDC hdc)
  {
    Graphics home_screen(hdc);
    Pen pen(Color(150, 0, 130, 255),10);
    SolidBrush back_brush(Color(255, 0, 0, 0));

    //draw a black background
    home_screen.FillRectangle(&back_brush, 0, 0, width, height);

    //display messages
    FontFamily font_family(L"Arial");
    Font font_title(&font_family, 48, FontStyleBold, UnitPixel);
    PointF point(100, 100);
    SolidBrush text(Color(255, 0, 130, 255));



    home_screen.DrawString(L"Next Level", -1, &font_title, point, &text);

    home_screen.DrawRectangle(&pen, 80, 80, 300, 100);
  }

  void HomeScreen::draw_death_screen(HDC hdc)
  {
    Graphics home_screen(hdc);
    Pen pen(Color(150, 0, 130, 255),10);
    SolidBrush back_brush(Color(255, 0, 0, 0));

    //draw a black background
    home_screen.FillRectangle(&back_brush, 0, 0, width, height);

    //display messages
    FontFamily font_family(L"Arial");
    Font font(&font_family, 48, FontStyleBold, UnitPixel);
    PointF point(100, 100);
    SolidBrush text(Color(255, 0, 130, 255));

    home_screen.DrawString(L"Game Over", -1, &font, point, &text);

    home_screen.DrawRectangle(&pen, 80, 80, 300, 100);
  }

void HomeScreen::draw_credits(HDC hdc)
{
  Graphics home_screen(hdc);
  Pen title_pen(Color(150, 0, 130, 255),10);
  SolidBrush back_brush(Color(255, 0, 0, 0));

  //draw a black background
  home_screen.FillRectangle(&back_brush, 0, 0, width, height);

  //display messages
  FontFamily font_family(L"Arial");
  Font font_title(&font_family, 48, FontStyleBold, UnitPixel);
  PointF point(100, 100);
  SolidBrush text(Color(255, 0, 130, 255));

  home_screen.DrawString(L"The End", -1, &font_title, point, &text);

  home_screen.DrawRectangle(&title_pen, 80, 80, 300, 100);

  //instructions
  
  //display messages
  Font font_heading(&font_family, 24, FontStyleBold, UnitPixel);
  Font font(&font_family, 15, FontStyleBold, UnitPixel);
  PointF heading(100, 220);
  PointF line1(100, 250);
  PointF line2(100, 270);

  home_screen.DrawString(L"Credits", -1, &font_heading, heading, &text);
  home_screen.DrawString(L"Design: Graeme Tinsdale", -1, &font, line1, &text);
  home_screen.DrawString(L"Coding: Graeme Tinsdale", -1, &font, line2, &text);

  home_screen.DrawRectangle(&title_pen, 80, 200, 300, 150);

}