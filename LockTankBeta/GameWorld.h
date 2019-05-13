#ifndef GameWorld_H
#define GameWorld_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   GameWorld.h
//
//  Desc:   All the environment data and methods for the Steering
//          Behavior projects. This class is the root of the project's
//          update and render calls (excluding main of course)
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <windows.h>
#include <vector>
#include <time.h>
#include "definitions.h"

//Custom Classes
#include "GameBoard.h"
#include "Tank.h"
#include "Turret.h"
#include "Lock.h"
#include "LockSeg.h"
#include "Shell.h"
#include "HomeScreen.h"



class GameWorld
{ 
private:

  //set true to pause the motion
  bool                          m_bPaused;

  //local copy of client window dimensions
  int                           m_cxClient,
                                m_cyClient;

  //keeps track of the average FPS
  double                         m_dAvFrameTime;

  HomeScreen home_screen;
  GameBoard board;
  Tank tank;
  Turret turret;
  vector<Lock> levels;
  Lock lock;

  Lock home_background;


  vector<Shell> turret_shells;
  vector<Shell> tank_shells;
  clock_t start, time;
  int current_level;
  bool tank_hit;
  bool home_screen_running;
  bool level_running;
  bool level_change_screen_running;
  bool death_screen_running;
  bool credits;

  string levelA;
  vector<string> solA;

  string levelB;
  vector<string> solB;

public:
  
  GameWorld(int cx, int cy);

  ~GameWorld();

  void  Update(double time_elapsed);

  void  Render(HDC hdc);
  
  //handle WM_COMMAND messages
  void        HandleKeyPresses(WPARAM wParam, int key_direction);
  void        HandleMenuItems(WPARAM wParam, HWND hwnd);
  
  void        TogglePause(){m_bPaused = !m_bPaused;}
  bool        Paused()const{return m_bPaused;}

  int   cxClient()const{return m_cxClient;}
  int   cyClient()const{return m_cyClient;}

  bool check_timer();
  bool screen_timer();
  void check_collision();
};

#endif