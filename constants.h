
#ifndef _CONSTANTS_H            // prevent multiple definitions if this 
#define _CONSTANTS_H            // ..file is included in more than one place
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
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels
 
// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key
const UCHAR ROCKET_RIGHT_KEY = VK_RIGHT;
const UCHAR ROCKET_LEFT_KEY = VK_LEFT;
const UCHAR ROCKET_DOWN_KEY = VK_DOWN;
const UCHAR ROCKET_UP_KEY = VK_UP;

// rocket
const int  ROCKET_START_FRAME = 0;         // starting frame of ship animation
const int  ROCKET_END_FRAME = 3;           // last frame of ship animation
const float ROCKET_ANIMATION_DELAY = 0.1f; // time between frames of ship animation
const int  ROCKET_COLS = 1;                // ship texture has 1 column
const int  ROCKET_WIDTH = 64;              // width of ship image
const int  ROCKET_HEIGHT = 29;             // height of ship image
const float ROTATION_RATE = 180.0f;             // degrees per second
const float SCALE_RATE = 0.2f;                  // % change per second
const float ROCKET_SPEED = 250.0f;                // pixels per second
const float ROCKET_SCALE = 1.5f;                  // starting ship scale

// enemy ship
const int  ROCKET_START_FRAME = 0;         // starting frame of ship animation
const int  ROCKET_END_FRAME = 3;           // last frame of ship animation
const float ROCKET_ANIMATION_DELAY = 0.1f; // time between frames of ship animation
const int  ROCKET_COLS = 1;                // ship texture has 1 column
const int  ROCKET_WIDTH = 64;              // width of ship image
const int  ROCKET_HEIGHT = 29;             // height of ship image
const float ROTATION_RATE = 180.0f;             // degrees per second
const float SCALE_RATE = 0.2f;                  // % change per second
const float ROCKET_SPEED = 250.0f;                // pixels per second
const float ROCKET_SCALE = 1.5f;                  // starting ship scale

// graphic images
const char ENEMY_IMAGE[] = "Images\\eSpritesheet_40x30";
const char ROCKET_IMAGE[] = "Images\\Spritesheet_64x29.png";
const char FARBACK_IMAGE[] = "Images\\farback.jpg";

// damage types
//enum DAMAGE {BULLET, EBULLET};
#endif
