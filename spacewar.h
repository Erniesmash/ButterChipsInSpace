//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

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
#include "explosion.h"
#include "button.h"
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
	TextureManager eTexture;

	float numberOfSpecials = 4;

	TextureManager specialsTexture;
	std::vector<Specials*> specialList;

	Image	farback;
	Image	starfield;
	Image space;

	Image characterPortrait;
	TextureManager characterPortraitTexture;

	Image forest1;
	TextureManager forest1Texture;
	Image forest2;
	TextureManager forest2Texture;
	Image forest3;
	TextureManager forest3Texture;
	Image forest4;
	TextureManager forest4Texture;
	Image forest5;
	TextureManager forest5Texture;
	Image forest6;
	TextureManager forest6Texture;
	Image forest7;
	TextureManager forest7Texture;

	Image textBox;
	TextureManager textBoxTexture;
	Button button;
	TextureManager buttonTexture;

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
	vector<Explosion*> eList;

	std::vector<Bullet*> bulletList;
	float waitTimer;

	bool gameOver;
	bool gameWin;
	bool cheatCodeInvincible;
	bool musicOn;

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

	// check enemy vector
	bool checkEnemies()
	{
		if (dfrList.size() <= 0
			&& dfbList.size() <= 0
			&& dfgList.size() <= 0
			&& bossList.size() <= 0)
			return true;
		else
			return false;
	}
	// kill enemy
	void delEnemies()
	{
		for (vector<Dfr*>::iterator it = dfrList.begin();
			it != dfrList.end();)
		{
			if ((*it)->dead == true)
			{
				Explosion* e = new Explosion;
				e->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &eTexture);
				e->setX((*it)->getCenterX() - e->getWidth() / 2);
				e->setY((*it)->getCenterY() - e->getHeight() / 2);
				eList.push_back(e);
				SAFE_DELETE(*it);
				it = dfrList.erase(it);
			}

			else
			{
				++it;
			}
		}

		for (vector<Dfb*>::iterator it = dfbList.begin();
			it != dfbList.end();)
		{
			if ((*it)->dead == true)
			{
				Explosion* e = new Explosion;
				e->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &eTexture);
				e->setX((*it)->getCenterX() - e->getWidth() / 2);
				e->setY((*it)->getCenterY() - e->getHeight() / 2);
				eList.push_back(e);
				SAFE_DELETE(*it);
				it = dfbList.erase(it);
			}

			else
			{
				++it;
			}
		}

		for (vector<Dfg*>::iterator it = dfgList.begin();
			it != dfgList.end();)
		{
			if ((*it)->dead == true)
			{
				Explosion* e = new Explosion;
				e->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &eTexture);
				e->setX((*it)->getCenterX() - e->getWidth() / 2);
				e->setY((*it)->getCenterY() - e->getHeight() / 2);
				eList.push_back(e);
				SAFE_DELETE(*it);
				it = dfgList.erase(it);
			}

			else
			{
				++it;
			}
		}

		for (vector<Skull*>::iterator it = skullList.begin();
			it != skullList.end();)
		{
			if ((*it)->dead == true)
			{
				Explosion* e = new Explosion;
				e->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &eTexture);
				e->setX((*it)->getCenterX() - e->getWidth() / 2);
				e->setY((*it)->getCenterY() - e->getHeight() / 2);
				eList.push_back(e);
				SAFE_DELETE(*it);
				it = skullList.erase(it);
			}

			/*if ((*it)->exited == true && (*it)->dead == false)
			{
				SAFE_DELETE(*it);
				it = skullList.erase(it);
			}*/

			else
			{
				++it;
			}
		}

		for (vector<Boss*>::iterator it = bossList.begin();
			it != bossList.end();)
		{
			if ((*it)->dead == true)
			{
				Explosion* e = new Explosion;
				e->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &eTexture);
				e->setX((*it)->getCenterX() - e->getWidth() / 2);
				e->setY((*it)->getCenterY() - e->getHeight() / 2);
				eList.push_back(e);
				SAFE_DELETE(*it);
				it = bossList.erase(it);
			}

			else
			{
				++it;
			}
		}

		for (vector<EBullet*>::iterator it = ebList.begin();
			it != ebList.end();)
		{
			if ((*it)->collided == true)
			{
				SAFE_DELETE(*it);
				it = ebList.erase(it);
			}

			else
			{
				++it;
			}
		}

		for (vector<Explosion*>::iterator it = eList.begin();
			it != eList.end();)
		{
			if ((*it)->exploded == true)
			{
				SAFE_DELETE(*it);
				it = eList.erase(it);
			}

			else
			{
				++it;
			}
		}
	}

	// spawn enemy
	void spawnDfr(float x, float y)
	{
		Dfr* r = new Dfr;
		r->initialize(this, dfrNS::WIDTH, dfrNS::HEIGHT, dfrNS::TEXTURE_COLS, &dfrTexture);
		r->setX(x);
		r->setY(y);
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

	void spawnDfg(float x, float y)
	{
		Dfg* g = new Dfg;
		g->initialize(this, dfgNS::WIDTH, dfgNS::HEIGHT, dfgNS::TEXTURE_COLS, &dfgTexture);
		g->setX(x);
		g->setY(y);
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
