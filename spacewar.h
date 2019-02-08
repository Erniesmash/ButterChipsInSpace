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

//enemies
#include "dfr.h"
#include "dfb.h"
#include "dfg.h"
#include "skull.h"
#include "boss.h"
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

	//enemy texture
	TextureManager dfrTexture;
	TextureManager dfbTexture;
	TextureManager dfgTexture;
	TextureManager skullTexture;
	TextureManager bossTexture;
	TextureManager ebTexture;
	TextureManager ebulletTexture;

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

	//enemy vectors
	vector<Dfr*> dfrList;
	vector<Dfb*> dfbList;
	vector<Dfg*> dfgList;
	vector<Skull*> skullList;
	vector<Boss*> bossList;
	vector<EBullet*> ebList;

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

	// kill enemy
	void checkDfr();
	void checkDfb();
	void checkDfg();
	void checkSkull();
	void checkBoss();

	// spawn enemy
	void spawnDfr(float x, float y)
	{
		Dfr* r = new Dfr;
		r->initialize(this, dfrNS::WIDTH, dfrNS::HEIGHT, dfrNS::TEXTURE_COLS, &dfrTexture);
		r->setX(GAME_WIDTH / 2);
		r->setY(GAME_HEIGHT / 5);
		dfrList.push_back(r);
	}

	void spawnDfb(float x, float y)
	{
		Dfb* b = new Dfb;
		b->initialize(this, dfbNS::WIDTH, dfbNS::HEIGHT, dfbNS::TEXTURE_COLS, &dfbTexture);
		b->setX(x);
		b->setY(y);
		dfbList.push_back(b);
	}

	void spawnDfg(float x, float y, float start, float end)
	{
		Dfg* g = new Dfg;
		g->initialize(this, dfgNS::WIDTH, dfgNS::HEIGHT, dfgNS::TEXTURE_COLS, &dfgTexture);
		g->setX(x);
		g->setY(y);
		g->startheight = start;
		g->endheight = end;
		dfgList.push_back(g);
	}

	void spawnSkull(float x, float y)
	{
		Skull* skull = new Skull;
		skull->initialize(this, skullNS::WIDTH, skullNS::HEIGHT, skull->textcols, &skullTexture);
		skull->setX(x);
		skull->setY(y);
		skullList.push_back(skull);
	}

	void spawnBoss(float x, float y)
	{
		Boss* boss = new Boss;
		boss->initialize(this, bossNS::WIDTH, bossNS::HEIGHT, bossNS::TEXTURE_COLS, &bossTexture);
		boss->setX(x);
		boss->setY(y);
		bossList.push_back(boss);
	}
};

#endif
