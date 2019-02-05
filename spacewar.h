#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "bullet.h"
#include <vector>
#include <string>
#include "player.h"
#include "textDX.h"
#include "heart.h"
#include "specials.h"
#include "selection.h"
#include "missle.h"
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

namespace spacewarNS
{
	const char FONT[] = "Arial Bold";  // font
	const char FONT_MENU[] = "Consolas";  // font menu
	const int FONT_BIG_SIZE = 100;     // font height
	const int BUF_SIZE = 200;
	const int FONT_MENU_SIZE = 60;
	const COLOR_ARGB FONT_COLOR = graphicsNS::GREEN;
}


//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
    // game items
	TextDX dxFont;
	TextDX fontBig;
	TextDX dxFontGreen;
	TextDX fontMenu;

	char buffer[spacewarNS::BUF_SIZE];
    TextureManager gameTextures;    
	TextureManager rocketTexture;	
	TextureManager farbackTexture;	
	TextureManager bulletTexture;	
	TextureManager starfieldTexture;
	TextureManager explosionTexture;
	TextureManager playerTexture;
	TextureManager missleTexture;
	TextureManager spaceTexture;
	TextureManager enemyTexture;
	TextureManager selectionTexture;
	std::vector<Selection*> selectionList;

	TextureManager heartTexture;
	std::vector<Heart*> heartList;

	// Adjust Starting Number of Lives here
	float numberOfLives = 6;
	float numberOfSpecials = 4;

	TextureManager specialsTexture;
	std::vector<Specials*> specialList;

	Image	farback;
	Image	starfield;
	Image space;

	Image menu;
	bool menuOn;

	Player playerMain;
	Player startPlayer;
	Missle missleShot;

	std::vector<Bullet*> bulletList;
	float waitTimer;

public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
