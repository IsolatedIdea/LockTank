#pragma warning (disable:4786)

// based on code provided by Matt Buckland, Programming Game AI by Example

#include <windows.h>
#include <time.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#include <cassert>

#include "GameWorld.h"

#include "AdditionalObjects.h"
#include "Controls.h"
#include "definitions.h"

//Custom Classes
#include "GameBoard.h"
#include "Tank.h"
#include "Turret.h"
#include "Lock.h"

using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")

//forward declaration of message handling function
LRESULT CALLBACK WindowProc (HWND   hwnd,
                             UINT   msg,
                             WPARAM wParam,
                             LPARAM lParam);

//--------------------------------- Globals ------------------------------
//
//------------------------------------------------------------------------

char*   g_szApplicationName = "SSample Window";
char*	g_szWindowClassName = "MyWindowClass";

GameWorld* g_GameWorld;


//-------------------------------- WinMain -------------------------------
//
//	The entry point of the windows program
//------------------------------------------------------------------------
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     szCmdLine, 
                    int       iCmdShow)
{


  //GDI+
  GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR           gdiplusToken;
  //Initialise GDI+
  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

  //handle to our window
  HWND						hWnd;

  //our window class structure  NOT a C++ class!
  WNDCLASSEX     winclass;


  // first fill in the window class stucture
  winclass.cbSize        = sizeof(WNDCLASSEX);         // size of structure
  winclass.style         = CS_HREDRAW | CS_VREDRAW;    // Winodwstyle - can also be set to 0
  winclass.lpfnWndProc   = WindowProc;                 // callback for all messages
  winclass.cbClsExtra    = 0;                          // extra data for this class
  winclass.cbWndExtra    = 0;                          // extradata for instances of the class
  winclass.hInstance     = hInstance;                  // parent applicaiton (paramenter fromWinMain)
  winclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);  // icon used in ALT+TAB switchin
  winclass.hCursor       = LoadCursor(NULL, IDC_ARROW); // cursor
  winclass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));                        // background Brush for colouring window
  winclass.lpszMenuName  = NULL;                        // menu resource naem fro this class
  winclass.lpszClassName = g_szWindowClassName;         // name for this class
  winclass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);  //taskbar icon for htis class


  //register the window class
  if (!RegisterClassEx(&winclass))
  {
    MessageBox(NULL, "Registration Failed!", "Error", 0);

    //exit the application
    return 0;
  }

  hWnd = CreateWindow(g_szWindowClassName,
    g_szApplicationName,
    WS_DLGFRAME,
    CW_USEDEFAULT,
    0,
    CW_USEDEFAULT,
    0,
    NULL,
    NULL,
    hInstance,
    NULL);

  //Remove all window styling
  SetWindowLong(hWnd, GWL_STYLE, 0);

  //make sure the window creation has gone OK
  if(!hWnd)
  {
    MessageBox(NULL, "CreateWindowEx Failed!", "Error!", 0);
  }


  //make the window visible
  ShowWindow (hWnd, SW_MAXIMIZE);
  UpdateWindow (hWnd);

  // Enter the message loop
  bool bDone = false;

  MSG msg;

  while(!bDone)
  {		
    while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) 
    {
      if( msg.message == WM_QUIT  || msg.message == WM_CLOSE) 
      {
        //stop loop if it's a quit message
        bDone = true;
      } 
      else 
      {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
      }
    }

    if (msg.message != WM_QUIT && msg.message != WM_CLOSE)
    {      
      //render
      //re-draw the window
      RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
      //InvalidateRect(hWnd, NULL, TRUE);
      //UpdateWindow(hWnd);

      Sleep(2);
    }

  }//end while

  delete g_GameWorld;

  //shutdown GDI+
  GdiplusShutdown(gdiplusToken);

  UnregisterClass( g_szWindowClassName, winclass.hInstance );

  return msg.wParam;
}


//---------------------------- WindowProc ---------------------------------
//	
//	This is the callback function which handles all the windows messages
//-------------------------------------------------------------------------

LRESULT CALLBACK WindowProc (HWND   hwnd,
                             UINT   msg,
                             WPARAM wParam,
                             LPARAM lParam)
{
  //these hold the dimensions of the client window area
  static int cxClient, cyClient; 

  //used to create the back buffer
  static HDC		hdcBackBuffer;
  static HBITMAP	hBitmap;
  static HBITMAP	hOldBitmap;

  switch (msg)
  {

    //A WM_CREATE msg is sent when your application window is first
    //created
  case WM_CREATE:
    {
      //As this is a fullscreen application, get the size of the current monitor
      //and set cxClient and cyClient accordingly 

      HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
      MONITORINFO info;
      info.cbSize = sizeof(MONITORINFO);
      GetMonitorInfo(monitor, &info);
      cxClient = info.rcMonitor.right - info.rcMonitor.left;
      cyClient = info.rcMonitor.bottom - info.rcMonitor.top;


      //seed random number generator
      srand((unsigned) time(NULL));  

      //---------------create a surface to render to(backbuffer)
      //create a memory device context
      hdcBackBuffer = CreateCompatibleDC(NULL);

      //get the DC for the front buffer
      HDC hdc = GetDC(hwnd);

      //set the center of the viewport
      SetViewportOrgEx(hdc, ORIGIN_X, ORIGIN_Y, NULL);

      hBitmap = CreateCompatibleBitmap(hdc,
        cxClient,
        cyClient);

      //select the bitmap into the memory device context
      hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);

      //don't forget to release the DC
      ReleaseDC(hwnd, hdc); 

      g_GameWorld = new GameWorld(cxClient, cyClient);      
    } // end WM_CREATE

    break;

  case WM_COMMAND:
    {
      g_GameWorld->HandleMenuItems(wParam, hwnd); 
    }

    break;


  case WM_LBUTTONUP:
    {
    }

    break;

  case WM_KEYUP:
    {
      switch(wParam)
      {
      case VK_ESCAPE:
        {             
          SendMessage(hwnd, WM_DESTROY, NULL, NULL);
        }

        break;

      case 'R':
        {
          delete g_GameWorld;

          g_GameWorld = new GameWorld(cxClient, cyClient);
        }

        break;


      }//end switch

      //handle any others
      g_GameWorld->HandleKeyPresses(wParam, WM_KEYUP);

    }//end WM_KEYUP

    break;

  case WM_KEYDOWN:
    g_GameWorld->HandleKeyPresses(wParam, WM_KEYDOWN);
    break;

  case WM_PAINT:
    { 		       
      PAINTSTRUCT ps;

      BeginPaint (hwnd, &ps);

      //fill our backbuffer with white
      BitBlt(hdcBackBuffer,
        0,
        0,
        cxClient,
        cyClient,
        NULL,
        NULL,
        NULL,
        WHITENESS);

      //StartDrawing(hdcBackBuffer);

      g_GameWorld->Render(hdcBackBuffer);

      //StopDrawing(hdcBackBuffer);

      //now blit backbuffer to front
      BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY); 

      EndPaint (hwnd, &ps);
    } // end WM_PAINT

    break;

  case WM_DESTROY:
    {

      //clean up our backbuffer objects
      SelectObject(hdcBackBuffer, hOldBitmap);

      DeleteDC(hdcBackBuffer);
      DeleteObject(hBitmap); 



      // kill the application, this sends a WM_QUIT message  
      PostQuitMessage (0);
    }

    break;

  }//end switch

  //this is where all the messages not specifically handled by our 
  //winproc are sent to be processed
  return DefWindowProc (hwnd, msg, wParam, lParam);
}

