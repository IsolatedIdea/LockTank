#include "GameWorld.h"
#include <gdiplus.h>
#include <stdio.h>
#include <iostream>

#include "AdditionalObjects.h"
#include "Controls.h"
#include <list>
using std::list;





//------------------------------- creator --------------------------------
//------------------------------------------------------------------------
GameWorld::GameWorld(int cx, int cy):

  m_cxClient(cx),
  m_cyClient(cy),
  m_bPaused(false)

{
  //Custom Global Vars

  home_screen=HomeScreen(cy, cx);
  home_background=Lock(" ");

  levelA="((L&R))";
  solA.push_back("TT");

  levelB="((L|R)&(L|R))&(!(L|R)&!(L|R))";
  solB.push_back("FFFFTTTT");
  solB.push_back("FFFTTTTT");
  solB.push_back("FFTFTTTT");
  solB.push_back("FTFFTTTT");
  solB.push_back("FTFTTTTT");
  solB.push_back("FTTFTTTT");
  solB.push_back("TFFFTTTT");
  solB.push_back("TFFTTTTT");
  solB.push_back("TFTFTTTT");


  //string TestB="(L&R)|(L&R)";
  //string TestC="(!(L&R))";
  //string TestD="(L&!R)&R";
  //string TestE="((L&R)&(L&R)&!((L)|((L&R)&(L|R))))";
  board = GameBoard(ORIGIN_X, ORIGIN_Y); //The main gameboard
  tank = Tank(BOARD_WIDTH/2, 0, 0);//Players tank
  tank_hit=FALSE;
  turret = Turret(-180, tank, 'R');
  //lock = Lock(TestE, 0, 0, LOCK_WIDTH, LOCK_HEIGHT, FALSE);

  levels.push_back(Lock(levelA, solA, 0, 0, LOCK_WIDTH, LOCK_HEIGHT, FALSE));
  levels.push_back(Lock(levelB, solB, 0, 0, LOCK_WIDTH, LOCK_HEIGHT, FALSE));
  current_level=0;


  home_screen_running=TRUE;
  level_running=FALSE;
  level_change_screen_running=FALSE;
  death_screen_running=FALSE;
  credits=FALSE;
  start=clock();
}


//-------------------------------- destructor ----------------------------
//------------------------------------------------------------------------
GameWorld::~GameWorld()
{

}


//----------------------------- Update -----------------------------------
//------------------------------------------------------------------------
void GameWorld::Update(double time_elapsed)
{ 
  if (m_bPaused) return;

}


//------------------------- HandleKeyPresses -----------------------------
void GameWorld::HandleKeyPresses(WPARAM wParam, int key_direction)
{

  switch(wParam)
  {


  case 'P':

    TogglePause(); break;

    break;

  case 'Q':
    {//case Q starts
      if(home_screen_running&&(key_direction==WM_KEYDOWN))
      {
        //Exit the application
        exit(0);
      }
      if(level_running)
      {
        level_running=FALSE;
        home_screen_running=TRUE;
      }
    }//case Q ends
    break;

  case 'Z':
    {//case , starts
      switch(key_direction)
      {
      case WM_KEYDOWN:
        tank.set_move('L');
        break;
      case WM_KEYUP:
        tank.set_move('S');
        break;
      default:
        tank.set_move('S');
        break;
      }
      //turret.update_turret(tank);
    }//case , ends
    break;

  case 'X':
    {//case . starts
      switch(key_direction)
      {
      case WM_KEYDOWN:
        tank.set_move('R');
        break;
      case WM_KEYUP:
        tank.set_move('S');
        break;
      default:
        tank.set_move('S');
        break;
      }
      //int angle=adjust_angle(tank.get_angle()-TANK_SPEED);
      //tank.set_angle(angle);
      //turret.update_turret(tank);
    }//case.ends
    break;

  case 'N':
    {//case , starts
      if(key_direction==WM_KEYUP)
      {
        tank_shells.push_back(Shell(1, (BOARD_WIDTH/2)-48, 0, tank.get_angle()));
      }
    }//case , ends
    break;

  case 'M':
    {//case . startsn
      if(key_direction==WM_KEYUP)
      {
        tank_shells.push_back(Shell(-1, (BOARD_WIDTH/2)-48, 0, tank.get_angle()));
      }
    }//case.ends
    break;

  case 'S':
    {
      home_screen_running=FALSE;
      level_running=TRUE;
      start=0;
      start=clock();
    }
    break;

  }//end switch
}


//-------------------------- HandleMenuItems -----------------------------
void GameWorld::HandleMenuItems(WPARAM wParam, HWND hwnd)
{
  switch(wParam)
  {
  case 1:
    break;
  default:
    break;
  }//end switch
}


//------------------------------ Render ----------------------------------
//------------------------------------------------------------------------
void GameWorld::Render(HDC hdc)
{ 
  
  //display the home screen
  if(home_screen_running)
  {
    //home_background.draw_lock(hdc);
    home_screen.draw_alpha_layer(hdc);
    home_screen.draw_homescreen(hdc);
    
  }

  //run the level
  if(level_running)
  {

    //black background
    //home_background.draw_lock(hdc);
    //draw the gameboard
    board.DrawBoard(hdc, BOARD_WIDTH, BOARD_HEIGHT, m_cxClient, m_cyClient);
    //draw the current level
    levels.at(current_level).draw_lock(hdc);
    //draw the tank
    tank.DrawTank(hdc);
    //draw the turret
    turret.draw_turret(hdc, tank);
  
  
    //check to see what time it is
    if(check_timer())
    {
      //if we are at the right interval fire the turret
      turret_shells.push_back(Shell(0,
                                  100,
                                  0,
                                  turret.get_turret_angle()));
    }//if timer ends

    //show any tank shells
    if(!tank_shells.empty())
    {//if tank shells starts
      for(unsigned int i=0;i<tank_shells.size();i++)
      {//for tank shells starts
        //check to see if the shell should still exist
        if(tank_shells.at(i).update_position())
        {//update tank shell pos starts
          //if it should draw it
          tank_shells.at(i).draw_shell(hdc);
        }//update tank shell pos ends
        else
        {//update tank shell pos else starts
          //if it shouldn't erase it
          tank_shells.erase(tank_shells.begin());
          //as we just deleted the first shell in the vector
          //we need to set i to -1
          i--;
        }//update tank shell pos esle ends
      }//for tank shells ends
    }//if tank shells ends

    //show any turret shells
    if(!turret_shells.empty())
    {
      for(unsigned int i=0;i<turret_shells.size();i++)
      {
        //check to see if the shell should still exist
        if(turret_shells.at(i).update_position())
        {
          //if it should draw it
          turret_shells.at(i).draw_shell(hdc);
        }
        else
        {
          //if it shouldn't erase it
          turret_shells.erase(turret_shells.begin());
          //as we just deleted the first shell in the vector
          //we need to set i to -1
          i--;
        }
      }
    }//if(...) turret shells ends

    //check to see if we hav a hit
    check_collision();
  }

  //what to do if the tank has been hit
  if(tank_hit)
  {
    level_running=FALSE;
    death_screen_running=TRUE;
    //re-set the scene
    tank_shells.erase(tank_shells.begin(), tank_shells.begin()+tank_shells.size());
    turret_shells.erase(turret_shells.begin(), turret_shells.begin()+turret_shells.size());

    levels.erase(levels.begin(), levels.begin()+levels.size());
    levels.push_back(Lock(levelA, solA, 0, 0, LOCK_WIDTH, LOCK_HEIGHT, FALSE));
    levels.push_back(Lock(levelB, solB, 0, 0, LOCK_WIDTH, LOCK_HEIGHT, FALSE));
    tank.set_angle(0);

    //start the clock
    start=clock();
  }
  
    
  //check to see if we have a soloution
  if(levels.at(current_level).simple_check())
  {
    level_running=FALSE;
    level_change_screen_running=TRUE;
    
    //re-set the scene
    tank_shells.erase(tank_shells.begin(), tank_shells.begin()+tank_shells.size());
    turret_shells.erase(turret_shells.begin(), turret_shells.begin()+turret_shells.size());
    tank.set_angle(0);
    
    levels.erase(levels.begin(), levels.begin()+levels.size());
    levels.push_back(Lock(levelA, solA, 0, 0, LOCK_WIDTH, LOCK_HEIGHT, FALSE));
    levels.push_back(Lock(levelB, solB, 0, 0, LOCK_WIDTH, LOCK_HEIGHT, FALSE));

    //increment the current level
    current_level++;
    
    if(current_level==levels.size())
    {
      current_level=0;
      level_change_screen_running=FALSE;
      credits=TRUE;
    }

    //re-set the timer
    start=clock();
  }

  //display the death screen for 3 seconds
  if(death_screen_running)
  {
    tank_hit=FALSE;
    home_screen.draw_death_screen(hdc);
    if(screen_timer())
    {
      death_screen_running=FALSE;
      home_screen_running=TRUE;
    }
  }

  
  if(level_change_screen_running)
  {

    home_screen.draw_level_change(hdc);
    if(screen_timer())
    {
      level_change_screen_running=FALSE;
      level_running=TRUE;
    }
  }

  if(credits)
  {
    home_screen.draw_credits(hdc);
    if(screen_timer())
    {
      credits=FALSE;
      home_screen_running=TRUE;
    }
  }
}//render(HDC hdc) ends

bool GameWorld::check_timer()
{
  time=clock()-start;

  double result=(double)time/((double)CLOCKS_PER_SEC);

  if(result>0.75)
  {
    start=clock();
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

bool GameWorld::screen_timer()
{
  time=clock()-start;

  double result=(double)time/((double)CLOCKS_PER_SEC);

  if(result>3)
  {
    start=clock();
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

void GameWorld::check_collision()
{//check_collision() starts
  float start_angle;
  float end_angle;
  vector<LockSeg> local_segments=levels.at(current_level).get_segments();
 

  //check if the tank shells hav hit...
  //loop over all the tank shells
  for(unsigned int i=0;i<tank_shells.size();i++)
  {
    //loop over all the segments checking to see
    //if we have a hit...

    if(tank_shells.at(i).get_x() < LOCK_WIDTH/2)
    {
      //get the angle of the shell and adjust for the segments
      float shell_angle=tank_shells.at(i).get_angle();
      shell_angle=shell_angle;
      if(shell_angle < 0)
      {
        shell_angle=shell_angle+360;
      }

      for(unsigned int j=0;j<local_segments.size();j++)
      {
        start_angle=local_segments.at(j).get_start_angle();
        end_angle=start_angle+local_segments.at(j).get_sweep();

        
       if(start_angle > 360)
        {
          start_angle=start_angle-360;
        }

        if(end_angle>360)
        {
            end_angle=end_angle-360;
          
          if((shell_angle > start_angle)||
             (shell_angle < end_angle))
          {
            int new_value = tank_shells.at(i).get_value();
            local_segments.at(j).set_value(new_value);
            levels.at(current_level).set_segments(local_segments);
          }//if shell angle less than end angle
        }
        else
        {
          if(shell_angle > start_angle)
          {       
            if(shell_angle < end_angle)
            {
              int new_value = tank_shells.at(i).get_value();
              local_segments.at(j).set_value(new_value);
              levels.at(current_level).set_segments(local_segments);
            }//if shell angle less than end angle
          }
        }//if shell angle greater than start angle
      }//end segment loop
    }//if tank_shells less than half lock width ends
  }//end shell loop

  
  //see if the tank has been hit
  for(unsigned int k=0;k<turret_shells.size();k++)
  {
    int hit=-1;
    int shell_x=turret_shells.at(k).get_x();
    if(shell_x>((BOARD_WIDTH/2)-10))
    {
      hit=0;
    }
    else  if(shell_x>((BOARD_WIDTH/2)-20))
    {
      hit=1;
    }
    else if(shell_x>((BOARD_WIDTH/2)-30))
    {
      hit=2;
    }

    switch(hit)
    {
    case 0:
      {
        float shell_angle=turret_shells.at(k).get_angle();
        float tank_angle=tank.get_angle();
        //get the spread
        float upper=tank_angle+7;
        float lower=tank_angle-7;

        if((shell_angle > lower)&&(shell_angle < upper))
        {
          tank_hit=TRUE;
        }//if tank hit ends
      }
      break;

    case 1:
      {
        float shell_angle=turret_shells.at(k).get_angle();
        float tank_angle=tank.get_angle();
        //get the spread
        float upper=tank_angle+5;
        float lower=tank_angle-5;

        if((shell_angle > lower)&&(shell_angle < upper))
        {
          tank_hit=TRUE;
        }//if tank hit ends
      }
      break;

    case 2:
      {
        float shell_angle=turret_shells.at(k).get_angle();
        float tank_angle=tank.get_angle();
        //get the spread
        float upper=tank_angle+2;
        float lower=tank_angle-2;

        if((shell_angle > lower)&&(shell_angle < upper))
        {
          tank_hit=TRUE;
        }//if tank hit ends
      }
      break;

    default:
      break;
    }
  }//tank hit loop ends
}//check_collision() ends