#include "spaceWar.h"

// lvl variables
bool gameStart = false;
bool changed;
int progress;
bool lvl;

float spawnTimer = 0;
float lvlTime = 30;

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{
	menuOn = true;
	gameOver = false;
	gameWin = false;
	cheatCodeInvincible = false;
}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	// dxFont
	if (dxFont.initialize(graphics, gameNS::POINT_SIZE, false, false, gameNS::FONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	// dxFont Green
	if (dxFontGreen.initialize(graphics, gameNS::POINT_SIZE, false, false, gameNS::FONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));
	dxFontGreen.setFontColor(spacewarNS::FONT_COLOR);

	// initialize DirectX fonts
	fontBig.initialize(graphics, spacewarNS::FONT_BIG_SIZE, false, false, spacewarNS::FONT);

	// initialize DirectX fonts
	fontMenu.initialize(graphics, spacewarNS::FONT_MENU_SIZE, false, false, spacewarNS::FONT_MENU);

	// heart texture
	if (!heartTexture.initialize(graphics, HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart texture"));

	for (int x = 0; x < playerMain.health; x++)
	{
		Heart *heart = new Heart();
		heart->initialize(this, heartNS::WIDTH, heartNS::HEIGHT, heartNS::TEXTURE_COLS, &heartTexture);
		heart->setX(GAME_WIDTH / 24 * (playerMain.health - (x - 17.5)));
		heart->setY(GAME_HEIGHT / 100);
		heartList.push_back(heart);
	}

	// selection texture
	if (!selectionTexture.initialize(graphics, SELECTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selection texture"));

	// selection items
	for (int x = 0; x < numberOfSpecials; x++)
	{
		Selection *selection = new Selection();
		selection->initialize(this, selectionNS::WIDTH, selectionNS::HEIGHT, selectionNS::TEXTURE_COLS, &selectionTexture);
		selection->setX(GAME_WIDTH / 15 * (numberOfSpecials - (x + 0.8)));
		selection->setY(GAME_HEIGHT / 100);
		selectionList.push_back(selection);
	}

	// specials texture
	if (!specialsTexture.initialize(graphics, SPECIALS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing specials texture"));

	// specials items
	for (int x = 0; x < numberOfSpecials; x++)
	{
		Specials *special = new Specials();
		special->initialize(this, specialsNS::WIDTH, specialsNS::HEIGHT, specialsNS::TEXTURE_COLS, &specialsTexture);
		//special->setFrames(x, x);
		special->setCurrentFrame(x);
		special->setX(GAME_WIDTH / 15 * (numberOfSpecials - (x + 0.8)));
		special->setY(GAME_HEIGHT / 100);
		specialList.push_back(special);
	}

//=============================================================================
// Player
//=============================================================================
	// player texture
	if (!playerTexture.initialize(graphics, PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));

	// player
	if (!playerMain.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	playerMain.setX(GAME_WIDTH / 3);

	// player menu
	if (!startPlayer.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing startplayer"));

//=============================================================================
// Missle
//=============================================================================
	// missle texture
	if (!missleTexture.initialize(graphics, MISSLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missle texture"));

	// missle
	if (!missleShot.initialize(this, missleNS::WIDTH, missleNS::HEIGHT, missleNS::TEXTURE_COLS, &missleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missle"));

//=============================================================================
// Bullet Stuff
//=============================================================================
	// bullet texture
	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));

//=============================================================================
// Misc Background Stuff
//=============================================================================
	// main game textures
	if (!gameTextures.initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	// farback texture
	if (!farbackTexture.initialize(graphics, FARBACK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing farback texture"));

	// space texture
	if (!spaceTexture.initialize(graphics, SPACE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing space texture"));

	// farback image
	if (!space.initialize(graphics,0,0,0,&spaceTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing space"));

	// starfield texture
	if (!starfieldTexture.initialize(graphics, STARFIELD_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing starfield texture"));

	// starfield image
	if (!starfield.initialize(graphics, 0, 0, 0, &starfieldTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing starfield"));

	// menu image
	if (!menu.initialize(graphics, 0, 0, 0, &farbackTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

//=============================================================================
// Enemies
//=============================================================================
	if (!dfrTexture.initialize(graphics, DFR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfr"));
	if (!dfbTexture.initialize(graphics, DFB_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfb"));
	if (!dfgTexture.initialize(graphics, DFG_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfg"));
	if (!skullTexture.initialize(graphics, SKULL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing skull"));
	if (!bossTexture.initialize(graphics, BOSS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss"));
	if (!ebTexture.initialize(graphics, EBULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing eb"));
	if (!eTexture.initialize(graphics, EXPLOSION))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing e"));

//=============================================================================
// Misc
//=============================================================================
	// characterPortrait texture
	if (!characterPortraitTexture.initialize(graphics, HAPPY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing characterPortraitTexture"));

	// characterPortrait image
	if (!characterPortrait.initialize(graphics, 0, 0, 0, &characterPortraitTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing characterPortrait"));

	// forest1 texture
	if (!forest1Texture.initialize(graphics, FOREST1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing forest1 Texture"));

	// forest1 image
	if (!forest1.initialize(graphics, 0, 0, 0, &forest1Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing forest1"));

	// forest2 texture
	if (!forest2Texture.initialize(graphics, FOREST2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing forest2 Texture"));

	// forest2 image
	if (!forest2.initialize(graphics, 0, 0, 0, &forest2Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing forest2"));

	// textbox texture
	if (!textBoxTexture.initialize(graphics, TEXTBOX_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Textbox Texture"));

	// textbox image
	if (!textBox.initialize(graphics, 0, 0, 0, &textBoxTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Textbox"));
	textBox.setX(GAME_WIDTH / 2 - textBox.getWidth() / 2 * textBox.getScale());
	textBox.setY(GAME_HEIGHT / 1.2 - textBox.getHeight() / 2 * textBox.getScale());

	// button texture
	if (!buttonTexture.initialize(graphics, BUTTON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Button Texture"));

	// button
	if (!button.initialize(this, buttonNS::WIDTH, buttonNS::HEIGHT, buttonNS::TEXTURE_COLS, &buttonTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button"));
	button.setX(GAME_WIDTH / 1.55 - button.getWidth() / 2 * button.getScale());
	button.setY(GAME_HEIGHT / 1.15 - button.getHeight() / 2 * button.getScale());

	//PlaySound("C:\\Users\\ernes\\Documents\\GitHub\\ButterChipsInSpace\\audio\\menu.wav", NULL, SND_LOOP | SND_ASYNC);
}
	
//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	if (input->isKeyDown(ROCKET_Q_KEY) && input->isKeyDown(ROCKET_E_KEY))
	{
		cheatCodeInvincible = true;
	}

	waitTimer -= frameTime;
	spawnTimer -= frameTime;
	if (menuOn == true)
	{
		if (input->anyKeyPressed())
		{
			menuOn = false;
			input->clearAll();
		}

		startPlayer.setX(startPlayer.getX() + frameTime * playerNS::SPEED);
		startPlayer.update(frameTime);

		if (startPlayer.getX() > GAME_WIDTH - playerNS::WIDTH * startPlayer.getScale() - 1)    // if hit right screen edge
		{
			startPlayer.setX(0);    // position at right screen edge
		}
	}
	
	if (menuOn == false)
	{
		for (std::vector<Bullet*>::iterator it = bulletList.begin();
			it != bulletList.end();)
		{
			if ((*it)->bounceInUseTimer == 4)
			{
				if ((*it)->getX() > GAME_WIDTH - bulletNS::WIDTH * (*it)->getScale())    // if hit right screen edge
				{
					SAFE_DELETE(*it);
					it = bulletList.erase(it);
				}
				else if ((*it)->getX() < 0)                    // else if hit left screen edge
				{
					SAFE_DELETE(*it);
					it = bulletList.erase(it);
				}

				else if ((*it)->getY() > GAME_HEIGHT - bulletNS::HEIGHT * (*it)->getScale())  // if hit bottom screen edge
				{
					SAFE_DELETE(*it);
					it = bulletList.erase(it);
				}
				else if ((*it)->getY() < 0)                    // else if hit top screen edge
				{
					SAFE_DELETE(*it);
					it = bulletList.erase(it);
				}

				else
				{
					++it;
				}
			}

			else
			{
				++it;
			}
		}

		if (missleShot.missleActive == false)
		{
			if (input->isKeyDown(THREE_KEY))
			{
				missleShot.shoot(&playerMain, frameTime);
				missleShot.missleActive = true;
			}
		}

		if (input->getMouseLButton() == true)
		{
			if (waitTimer <= 0.0f)
			{
				waitTimer = 0.4f;
				Bullet *b = new Bullet();
				b->initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &bulletTexture);
				bulletList.push_back(b);
				b->shoot(&playerMain, frameTime);
				audio->playCue(GUNSHOT1);
			}
		}

		//=============================================================================
		// Update frameTime for Animation 
		//=============================================================================

		for each(Bullet*  bull in bulletList)
		{
			bull->update(frameTime);
		}

		playerMain.update(frameTime);
		missleShot.update(frameTime);
	}	
//=============================================================================
// update enemies per frame 
//=============================================================================
	for each (Dfr* r in dfrList)
	{
		r->getPlayer(&playerMain);
		r->update(frameTime);
	}

	for each (Dfb* b in dfbList)
	{
		b->update(frameTime);
	}

	for each (Dfg* g in dfgList)
	{
		g->update(frameTime);
	}

	for each (Skull* skull in skullList)
	{
		skull->update(frameTime);

		if (skull->exited == true)
		{
			for (int i = 1; i < 25; i++)
			{
				EBullet* e = new EBullet;
				e->initialize(this, ebulletNS::WIDTH, ebulletNS::HEIGHT, ebulletNS::TEXTURE_COLS, &ebTexture);
				e->appImpulse(skull->getCenterX(), skull->getCenterY(), 0 + 15 * i, 30);
				ebList.push_back(e);
			}
		}
	}

	for each (Boss* boss in bossList)
	{
		boss->getPlayer(&playerMain);
		boss->update(frameTime);
	}

	for each  (EBullet* eb in ebList)
	{
		eb->update(frameTime);
	}

	for each (Explosion* e in eList)
	{
		e->update(frameTime);
	}


//=============================================================================
// Game Levels 
//=============================================================================
	/*if (menuOn == false && gameStart == false)
	{
		progress = 1;
		gameStart = true;
	}*/

	// lvl 1
	if (progress == 1)
	{
		if (lvl == false && changed == false)
		{
			if (!dfrTexture.initialize(graphics, DFR_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfr"));
			spawnDfr(GAME_WIDTH - dfrNS::WIDTH * 2, GAME_HEIGHT / 4);
			spawnDfr(GAME_WIDTH - dfrNS::WIDTH * 2, GAME_HEIGHT / 2);
			spawnDfr(GAME_WIDTH - dfrNS::WIDTH * 2, 3 * GAME_HEIGHT / 4);
			lvl = true;
		}

		if (checkEnemies() == true)
		{
			progress = 2;
			lvl = false;
		}
	}

	// lvl 2
	else if (progress == 2)
	{
		if (lvl == false && changed == false)
		{
			if (!dfbTexture.initialize(graphics, DFB_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfb"));
			spawnDfb(GAME_WIDTH - dfbNS::WIDTH * 2, GAME_HEIGHT / 3);
			spawnDfb(GAME_WIDTH - dfbNS::WIDTH * 2, 2 * GAME_HEIGHT / 3);
			lvl = true;
		}

		if (checkEnemies() == true)
		{
			progress = 3;
			lvl = false;
		}
	}

	//lvl 3
	else if (progress == 3)
	{
		if (lvl == false && changed == false)
		{
			if (!dfrTexture.initialize(graphics, DFR_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfr"));
			if (!dfbTexture.initialize(graphics, DFB_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfb"));

			spawnDfr(GAME_WIDTH - dfrNS::WIDTH * 4, GAME_HEIGHT / 4);
			spawnDfb(GAME_WIDTH - dfbNS::WIDTH * 2, GAME_HEIGHT / 2);
			spawnDfr(GAME_WIDTH - dfrNS::WIDTH * 4, 3 * GAME_HEIGHT / 4);
			lvl = true;
		}

		if (checkEnemies() == true)
		{
			progress = 4;
			lvl = false;
		}
	}

	// lvl 4
	else if (progress == 4)
	{
		if (lvl == false && changed == false)
		{
			if (!dfrTexture.initialize(graphics, DFR_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfr"));
			if (!dfbTexture.initialize(graphics, DFB_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfb"));
			if (!dfgTexture.initialize(graphics, DFG_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfg"));

			spawnDfg(GAME_WIDTH - dfrNS::WIDTH * 2, GAME_HEIGHT / 5);
			spawnDfg(GAME_WIDTH - dfrNS::WIDTH * 2, 4 * GAME_HEIGHT / 5);

			spawnDfr(GAME_WIDTH - dfrNS::WIDTH * 4, 2 * GAME_HEIGHT / 5);
			spawnDfr(GAME_WIDTH - dfrNS::WIDTH * 4, 3 * GAME_HEIGHT / 5);

			spawnDfb(GAME_WIDTH - dfbNS::WIDTH * 6, GAME_HEIGHT / 2);

			lvl = true;
		}

		if (checkEnemies() == true)
		{
			progress = 5;
			lvl = false;
		}
	}

	// lvl 5
	else if (progress == 5)
	{
		if (lvl == false && changed == false)
		{
			if (!dfgTexture.initialize(graphics, DFG_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfg"));

			spawnDfg(GAME_WIDTH - dfrNS::WIDTH * 2, GAME_HEIGHT / 5);
			spawnDfg(GAME_WIDTH - dfrNS::WIDTH * 2, 4 * GAME_HEIGHT / 5);
			lvl = true;
		}

		if (spawnTimer <= 0)
		{
			spawnSkull(GAME_WIDTH, rand() % GAME_HEIGHT);
			spawnTimer = 0.5;
		}

		if (checkEnemies() == true)
		{
			progress = 6;
			lvl = false;
		}
	}

	// lvl 6
	else if (progress == 6)
	{
		if (lvl == false && changed == false)
		{
			if (!dfbTexture.initialize(graphics, DFB_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfb"));
			if (!dfgTexture.initialize(graphics, DFG_IMAGE))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfg"));

			spawnDfg(GAME_WIDTH - dfrNS::WIDTH * 2, GAME_HEIGHT / 5);
			spawnDfg(GAME_WIDTH - dfrNS::WIDTH * 2, 4 * GAME_HEIGHT / 5);

			spawnDfb(GAME_WIDTH - dfbNS::WIDTH * 6, GAME_HEIGHT / 2);

			lvl = true;
		}

		if (spawnTimer <= 0)
		{
			spawnSkull(GAME_WIDTH, rand() % GAME_HEIGHT);
			spawnTimer = 0.5;
		}

		if (checkEnemies() == true)
		{
			progress = 7;
			lvl = false;
		}
	}

	else if (progress == 7)
	{
		if (lvl == false && changed == false)
		{
			spawnBoss(GAME_WIDTH - bossNS::WIDTH * 4, GAME_HEIGHT / 2);
			lvl = true;
		}

		if (checkEnemies() == true)
		{
			progress = 8;
			lvl = false;
		}
	}
//=============================================================================
// check to delete vector objects 
//=============================================================================
	delEnemies();
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{
	VECTOR2 collisionVector;
	

	if (menuOn == false && gameWin == false && gameOver == false)
	{
		for (std::vector<Bullet*>::iterator it = bulletList.begin();
			it != bulletList.end();)
		{
			if ((*it)->collidesWith(button, collisionVector))
			{
				SAFE_DELETE(*it);
				it = bulletList.erase(it);
				playerMain.dialogueChoice++;
			}

			else
			{
				++it;
			}
		}

		for each(Dfr* dfr in dfrList)
		{
			if (dfr->collidesWith(missleShot, collisionVector))
			{
				dfr->health = dfr->health - 100;
			}

			for (std::vector<Bullet*>::iterator it = bulletList.begin();
				it != bulletList.end();)
			{
				if ((*it)->collidesWith(*dfr, collisionVector))
				{
					SAFE_DELETE(*it);
					it = bulletList.erase(it);
					if (dfr->health >= 0)
					{
						dfr->health = dfr->health - 50;
					}
				}

				else
				{
					++it;
				}
			}
		}	
		
		// dfrb on player collision
		for each(Dfr* dfr in dfrList)
		{
			for each (DfrBullet* d in dfr->dfrbList)
			{
				if (d->collidesWith(playerMain, collisionVector))
				{
					if (playerMain.getShieldOn() == false && playerMain.dashActive == false && cheatCodeInvincible == false)
					{
						playerMain.health = playerMain.health - 1;
						if (heartList.size() != 0)
						{
							heartList.erase(heartList.end() - 1);
						}
					}
					d->collided = true;
				}
			}
		}	

		for each(Dfg* dfg in dfgList)
		{
			if (dfg->collidesWith(missleShot, collisionVector))
			{
				dfg->health = dfg->health - 100;
			}
			for (std::vector<Bullet*>::iterator it = bulletList.begin();
				it != bulletList.end();)
			{
				if ((*it)->collidesWith(*dfg, collisionVector))
				{
					SAFE_DELETE(*it);
					it = bulletList.erase(it);
					if (dfg->health >= 0)
					{
						dfg->health = dfg->health - 50;
					}
				}

				else
				{
					++it;
				}
			}
		}

		// dfgb on player collision
		for each(Dfg* dfg in dfgList)
		{
			for each (DfgBullet* d in dfg->dfgbList)
			{
				if (d->collidesWith(playerMain, collisionVector))
				{
					if (playerMain.getShieldOn() == false && playerMain.dashActive == false && cheatCodeInvincible == false)
					{
						playerMain.health = playerMain.health - 1;
						if (heartList.size() != 0)
						{
							heartList.erase(heartList.end() - 1);
						}
					}
					d->collided = true;
				}
			}
		}

		for each(Dfb* dfb in dfbList)
		{
			if (dfb->collidesWith(missleShot, collisionVector))
			{
				dfb->health = dfb->health - 100;
			}
			for (std::vector<Bullet*>::iterator it = bulletList.begin();
				it != bulletList.end();)
			{
				if ((*it)->collidesWith(*dfb, collisionVector))
				{
					SAFE_DELETE(*it);
					it = bulletList.erase(it);
					if (dfb->health >= 0)
					{
						dfb->health = dfb->health - 50;
					}
				}

				else
				{
					++it;
				}
			}
		}

		//dfbb on player collision
		for each(Dfb* dfb in dfbList)
		{
			for each (DfbBullet* d in dfb->dfbbList)
			{
				if (d->collidesWith(playerMain, collisionVector))
				{
					if (playerMain.getShieldOn() == false && playerMain.dashActive == false && cheatCodeInvincible == false)
					{
						playerMain.health = playerMain.health - 1;
						if (heartList.size() != 0)
						{
							heartList.erase(heartList.end() - 1);
						}
					}
					d->collided = true;
				}
			}
		}

		//eb on player collision
		for each (EBullet* eb in ebList)
		{
			if (eb->collidesWith(playerMain, collisionVector))
			{
				if (playerMain.getShieldOn() == false && playerMain.dashActive == false && cheatCodeInvincible == false)
				{
					playerMain.health = playerMain.health - 1;
					if (heartList.size() != 0)
					{
						heartList.erase(heartList.end() - 1);
					}
				}
				eb->collided = true;
			}
		}

		//skull on player collision
		for each (Skull* s in skullList)
		{
			if (s->collidesWith(playerMain, collisionVector))
			{
				if (playerMain.getShieldOn() == false && playerMain.dashActive == false && cheatCodeInvincible == false)
				{
					playerMain.health = playerMain.health - 1;
					if (heartList.size() != 0)
					{
						heartList.erase(heartList.end() - 1);
					}
				}
				s->dead = true;
			}

			if (s->collidesWith(missleShot, collisionVector))
			{
				s->health = s->health - 100;
			}
			for (std::vector<Bullet*>::iterator it = bulletList.begin();
				it != bulletList.end();)
			{
				if ((*it)->collidesWith(*s, collisionVector))
				{
					SAFE_DELETE(*it);
					it = bulletList.erase(it);
					if (s->health >= 0)
					{
						s->health = s->health - 50;
					}
				}

				else
				{
					++it;
				}
			}
		}

		//boss bullets on player collision
		for each (Boss* b in bossList)
		{
			for each (DfbBullet* d in b->dfbbList)
			{
				if (d->collidesWith(playerMain, collisionVector))
				{
					if (playerMain.getShieldOn() == false && playerMain.dashActive == false && cheatCodeInvincible == false)
					{
						playerMain.health = playerMain.health - 1;
						if (heartList.size() != 0)
						{
							heartList.erase(heartList.end() - 1);
						}
					}
					d->collided = true;
				}
			}

			for each (DfrBullet* d in b->dfrbList)
			{
				if (d->collidesWith(playerMain, collisionVector))
				{
					if (playerMain.getShieldOn() == false && playerMain.dashActive == false && cheatCodeInvincible == false)
					{
						playerMain.health = playerMain.health - 1;
						if (heartList.size() != 0)
						{
							heartList.erase(heartList.end() - 1);
						}
					}
					d->collided = true;
				}
			}

			for each (DfgBullet* d in b->dfgbList)
			{
				if (d->collidesWith(playerMain, collisionVector))
				{
					if (playerMain.getShieldOn() == false && playerMain.dashActive == false && cheatCodeInvincible == false)
					{
						playerMain.health = playerMain.health - 1;
						if (heartList.size() != 0)
						{
							heartList.erase(heartList.end() - 1);
						}
					}
					d->collided = true;
				}
			}

			for each (EBullet* e in b->ebList)
			{
				if (e->collidesWith(playerMain, collisionVector))
				{
					if (playerMain.getShieldOn() == false && playerMain.dashActive == false && cheatCodeInvincible == false)
					{
						playerMain.health = playerMain.health - 1;
						if (heartList.size() != 0)
						{
							heartList.erase(heartList.end() - 1);
						}
					}
					e->collided = true;
				}
			}

			if (b->collidesWith(missleShot, collisionVector))
			{
				b->health = b->health - 100;
			}
			for (std::vector<Bullet*>::iterator it = bulletList.begin();
				it != bulletList.end();)
			{
				if ((*it)->collidesWith(*b, collisionVector))
				{
					SAFE_DELETE(*it);
					it = bulletList.erase(it);
					if (b->health >= 0)
					{
						b->health = b->health - 50;
					}
				}

				else
				{
					++it;
				}
			}
		}
		

		/*
		for each(Bullet*  bullet in bulletList)
		{
			if (bullet->collidesWith(button, collisionVector))
			{
				
				playerMain.i++;
			}
		}
		*/
	}    
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	if (menuOn == true)
	{
		menu.draw();
		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "Blob and Trouble!");
		fontMenu.print(buffer, GAME_WIDTH / 3.35, GAME_HEIGHT / 2.5);

		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "Click any button on the keyboard to begin your adventure!");
		dxFont.print(buffer, GAME_WIDTH / 100, GAME_HEIGHT / 1.05);

		startPlayer.draw();
	}

	if (gameOver == true)
	{
		menu.draw();
		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "Game Over :(");
		fontMenu.print(buffer, GAME_WIDTH / 2.7, GAME_HEIGHT / 2.5);

		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "Maybe try not to suck so much next time!");
		dxFont.print(buffer, GAME_WIDTH / 100, GAME_HEIGHT / 1.05);
	}

	if (menuOn == false && gameWin == false && gameOver == false)
	{	
		//space.draw();
		//starfield.draw();
		//characterPortrait.draw();

		forest1.draw();
		playerMain.draw();

		if (playerMain.dialogueEnd == false)
		{		
			textBox.draw();
			button.draw();
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, playerMain.playerDialogue);
			dxFont.print(buffer, GAME_WIDTH / 1.86 - textBox.getWidth() / 2 * textBox.getScale(), GAME_HEIGHT / 1.16 - textBox.getHeight() / 2 * textBox.getScale());
		}

		if (playerMain.dialogueEnd == true && gameStart == false)
		{
			progress = 1;
			gameStart = true;
		}

		if (missleShot.missleActive == true)
		{
			missleShot.draw();
		}

		if (heartList.size() != 0)
		{
			for each (Heart* h in heartList)
			{
				if (h->getActive() == true)
				{
					h->draw();
				}
			}
		}

		if (heartList.size() <= 0)
		{
			gameOver = true;
		}

		for each (Selection* s in selectionList)
		{
			if (s->getActive() == true)
			{
				s->draw();
			}
		}

		for each (Specials* s in specialList)
		{
			if (s->getActive() == true)
			{
				s->draw();
			}
		}

		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "Click 1, 2, 3 or 4 to use Special Abilities!");
		dxFont.print(buffer, GAME_WIDTH / 100, GAME_HEIGHT / 1.05);

		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", input->getMouseX());
		dxFont.print(buffer, GAME_WIDTH / 100, GAME_HEIGHT / 3);

		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", input->getMouseY());
		dxFont.print(buffer, GAME_WIDTH / 100, GAME_HEIGHT / 4);

		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "Wave");
		dxFont.print(buffer, GAME_WIDTH / 2.2, GAME_HEIGHT / 100);

		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", progress);
		dxFont.print(buffer, GAME_WIDTH / 2, GAME_HEIGHT / 100);

		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "of 6");
		dxFont.print(buffer, GAME_WIDTH / 1.93, GAME_HEIGHT / 100);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Ability One: Sine Wave Dash
		if (playerMain.dashOnCooldown == true)
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", (int)playerMain.dashCooldownTimer);
			dxFont.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (3 + 0.8)), GAME_HEIGHT / 10);
		}

		else
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "READY");
			dxFontGreen.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (3 + 0.8)), GAME_HEIGHT / 10);
		}

		//Ability Two: Bullet Bounce
		for each(Bullet* bullet in bulletList)
		{
			if (bullet->bounceOnCooldown == true)
			{
				//_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", (int)bullet->bounceCooldownTimer);
				//dxFont.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (2 + 0.8)), GAME_HEIGHT / 10);

				_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", (int)bullet->bounceInUseTimer);
				dxFont.print(buffer, playerMain.getCenterX() - 5, playerMain.getCenterY() + 20);
			}

			else
			{
				_snprintf_s(buffer, spacewarNS::BUF_SIZE, "READY");
				dxFontGreen.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (2 + 0.8)), GAME_HEIGHT / 10);
			}
		}
		if (bulletList.size() <= 0)
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "READY");
			dxFontGreen.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (2 + 0.8)), GAME_HEIGHT / 10);
		}

		//Ability Three: Falling Missle Shot
		if (missleShot.missleOnCooldown == true)
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", (int)missleShot.missleCooldownTimer);
			dxFont.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (1 + 0.8)), GAME_HEIGHT / 10);
		}

		else
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "READY");
			dxFontGreen.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (1 + 0.8)), GAME_HEIGHT / 10);
		}

		//Ability Four: Reflective Shield
	
		if (playerMain.shieldOnCooldown == true)
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", (int)playerMain.shieldCooldownTimer);
			dxFont.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (0 + 0.8)), GAME_HEIGHT / 10);
		}

		else
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "READY");
			dxFontGreen.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (0 + 0.8)), GAME_HEIGHT / 10);
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//change ability/specials selection
		if (input->isKeyDown(ONE_KEY))
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "^");
			fontBig.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (3 + 0.8)), GAME_HEIGHT / 10);
			audio->playCue(SELECTION1);
		}

		if (input->isKeyDown(TWO_KEY))
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "^");
			fontBig.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (2 + 0.8)), GAME_HEIGHT / 10);
			audio->playCue(SELECTION1);
		}

		if (input->isKeyDown(THREE_KEY))
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "^");
			fontBig.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (1 + 0.8)), GAME_HEIGHT / 10);
			audio->playCue(SELECTION1);
		}

		if (input->isKeyDown(FOUR_KEY))
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "^");
			fontBig.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (0 + 0.8)), GAME_HEIGHT / 10);
			audio->playCue(SELECTION1);
		}

		for each(Bullet*  bullet in bulletList)
		{
			bullet->draw();
		}
	}
//=============================================================================
// draw enemies
//=============================================================================
	if (gameOver == false && gameWin == false)
	{
		for each (Dfr* d in dfrList)
		{
			d->draw();
		}
		for each (Dfb* b in dfbList)
		{
			b->draw();
		}

		for each (Dfg* g in dfgList)
		{
			g->draw();
		}

		for each (Skull* skull in skullList)
		{
			skull->draw();
		}

		for each (Boss* boss in bossList)
		{
			boss->draw();
		}

		for each (EBullet* eb in ebList)
		{
			eb->draw();
		}
		for each (Explosion* e in eList)
		{
			e->draw();
		}
	}
	
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
    gameTextures.onLostDevice();
	farbackTexture.onLostDevice();
	starfieldTexture.onLostDevice();
	rocketTexture.onLostDevice();
	bulletTexture.onLostDevice();	
	heartTexture.onLostDevice();
	specialsTexture.onLostDevice();
	selectionTexture.onLostDevice();
	playerTexture.onLostDevice();
	spaceTexture.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
    gameTextures.onResetDevice();
	rocketTexture.onResetDevice();
	farbackTexture.onResetDevice();
	starfieldTexture.onResetDevice();
	bulletTexture.onResetDevice();
	heartTexture.onResetDevice();
	specialsTexture.onResetDevice();
	selectionTexture.onResetDevice();
	playerTexture.onResetDevice();
	spaceTexture.onResetDevice();
    Game::resetAll();
    return;
}