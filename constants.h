//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

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


//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "Blob";
const char GAME_TITLE[] = "Blob";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1100;           
const UINT GAME_HEIGHT = 600;            

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
const char POWERUP_IMAGE[] = "pictures\\balls.png";
const char STARFIELD_IMAGE[] = "pictures\\starfield.png";
const char HEAD_IMAGE[] = "pictures\\head_sheet.png";
const char EXPLOSION_IMAGE[] = "pictures\\explode1.png";
const char PLAYER_IMAGE[] = "pictures\\player.png";
const char SPECIALS_IMAGE[] = "pictures\\MeatSmall.png";
const char HEART_IMAGE[] = "pictures\\heart.png";
const char SELECTION_IMAGE[] = "pictures\\selection.png";
const char MISSLE_IMAGE[] = "pictures\\missile.png";
const char EXPLOSION_ADVANCED_IMAGE[] = "pictures\\explosionAdvanced.png";
const char SHIELD_IMAGE[] = "pictures\\shield.png";
const char SPACE_IMAGE[] = "pictures\\space.png";

const char DFR_IMAGE[] = "pictures\\dfr_atk.png";
const char DFB_IMAGE[] = "pictures\\dfb_atk.png";
const char DFG_IMAGE[] = "pictures\\dfg_atk.png";
const char SKULL_IMAGE[] = "pictures\\h_skull.png";
const char BOSS_IMAGE[] = "pictures\\boss_walk.png";

const char DFRBULLET_IMAGE[] = "pictures\\dfrbullet.png";
const char DFBBULLET_IMAGE[] = "pictures\\dfbbullet.png";
const char DFGBULLET_IMAGE[] = "pictures\\dfgbullet.png";
const char EBULLET_IMAGE[] = "pictures\\ehatch_sheet.png";

const char HEALTHBAR_IMAGE[] = "pictures\\healthbar.png";
const char DF_DEATH_IMAGE[] = "pictures\\df_death.png";
const char SKULL_ENTRANCE_IMAGE[] = "pictures\\hskull_appear.png";
const char SKULL_DEATH_IMAGE[] = "pictures\\hskull_death.png";
const char BUFFER_IMAGE[] = "pictures\\buffer.png";
const char BOSS_DEATH[] = "pictures\\boss_death.png";
const char EXPLOSION[] = "pictures\\explosionAdvanced.png";

const char FOREST1_IMAGE[] = "pictures\\forest1.png";
const char FOREST2_IMAGE[] = "pictures\\forest2.png";
const char FOREST3_IMAGE[] = "pictures\\forest3.png";
const char FOREST4_IMAGE[] = "pictures\\forest4.png";
const char FOREST5_IMAGE[] = "pictures\\forest5.png";
const char FOREST6_IMAGE[] = "pictures\\forest6.png";
const char FOREST7_IMAGE[] = "pictures\\forest7.png";
const char HAPPY_IMAGE[] = "pictures\\happy.png";
const char TEXTBOX_IMAGE[] = "pictures\\textBox.png";
const char BUTTON_IMAGE[] = "pictures\\button.png";

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

// Keys For Specials
const UCHAR ONE_KEY = 0x31;
const UCHAR TWO_KEY = 0x32;
const UCHAR THREE_KEY = 0x33;
const UCHAR FOUR_KEY = 0x34;

// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[] = "audio\\Win\\BlobWave.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\BlobSound.xsb";

// Audio Files
const char SELECTION1[] = "selection1";
const char GUNSHOT1[] = "gunshot1";
const char EXPLOSION1[] = "explosion1";

#endif
