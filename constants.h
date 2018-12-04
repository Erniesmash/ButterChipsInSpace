// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "Butter Chips in Space";
const char GAME_TITLE[] = "Butter Chips in Space";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1100;               // width of game in pixels640
const UINT GAME_HEIGHT = 600;               // height of game in pixels480

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float GRAVITY = 6.67428e-11f;             // gravitational constant
const float MASS_PLANET = 1.0e14f;
const float MASS_SHIP = 5.0f;

// graphic images
const char TEXTURES_IMAGE[] = "pictures\\textures.png";
const char ESHIP_IMAGE[] = "pictures\\eSpritesheet_40x30.png";
const char ROCKET_IMAGE[] = "pictures\\Spritesheet_64x29.png";
const char FARBACK_IMAGE[] = "pictures\\farback.jpg";
const char BULLET_IMAGE[] = "pictures\\hatch_sheet.png";
const char EBULLET_IMAGE[] = "pictures\\ehatch_sheet.png";
const char POWERUP_IMAGE[] = "pictures\\balls.png";
const char STARFIELD_IMAGE[] = "pictures\\starfield.png";
const char SPEEDBOOST_IMAGE[] = "pictures\\head_sheet.png";

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // enter key
const UCHAR LEFT_SHIFT_KEY = VK_LSHIFT;	// left shift key
const UCHAR ROCKET_D_KEY = 0x44;
const UCHAR ROCKET_A_KEY = 0x41;
const UCHAR ROCKET_S_KEY = 0x53;
const UCHAR ROCKET_W_KEY = 0x57;
const UCHAR ROCKET_E_KEY = 0x45;
const UCHAR ROCKET_Q_KEY = 0x51;
const UCHAR ARROW_LEFT = VK_LEFT;
const UCHAR ARROW_RIGHT = VK_RIGHT;
const UCHAR ARROW_UP = VK_UP;
const UCHAR ARROW_DOWN = VK_DOWN;
const UCHAR ROCKET_SPACE_KEY = VK_SPACE;

#endif
