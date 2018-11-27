// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "rocket.h"

//=============================================================================
// default constructor
//=============================================================================
Rocket::Rocket() : Entity()
{
	spriteData.width = rocketNS::WIDTH;           // size of rocket
	spriteData.height = rocketNS::HEIGHT;
	spriteData.x = rocketNS::X;                   // location on screen
	spriteData.y = rocketNS::Y;
	spriteData.rect.bottom = rocketNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = rocketNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = rocketNS::ROCKET_ANIMATION_DELAY;
	startFrame = rocketNS::ROCKET_START_FRAME;     // first frame of ship animation
	endFrame = rocketNS::ROCKET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = rocketNS::WIDTH / 2.0;
	shieldOn = false;
	mass = rocketNS::MASS;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Rocket::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	shield.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	shield.setFrames(rocketNS::SHIELD_START_FRAME, rocketNS::SHIELD_END_FRAME);
	shield.setCurrentFrame(rocketNS::SHIELD_START_FRAME);
	shield.setFrameDelay(rocketNS::SHIELD_ANIMATION_DELAY);
	shield.setLoop(false);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Rocket::draw()
{
	Image::draw();              // draw ship
	if (shieldOn)
		// draw shield using colorFilter 50% alpha
		shield.draw(spriteData, graphicsNS::ALPHA50 & colorFilter);
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Rocket::update(float frameTime)
{
	Entity::update(frameTime);
	//spriteData.angle += frameTime * rocketNS::ROTATION_RATE;  // rotate the ship
	//spriteData.x += frameTime * velocity.x;         // move ship along X 
	//spriteData.y += frameTime * velocity.y;         // move ship along Y

	// Bounce off walls
	if (spriteData.x > GAME_WIDTH - rocketNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - rocketNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - rocketNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - rocketNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	if (shieldOn)
	{
		shield.update(frameTime);
		if (shield.getAnimationComplete())
		{
			shieldOn = false;
			shield.setAnimationComplete(false);
		}
	}

	if (input->isKeyDown(ROCKET_RIGHT_KEY))            // if move right
	{
		//if (rocketMain.getX() < GAME_WIDTH - rocketMain.getWidth())
		spriteData.x = spriteData.x + frameTime * rocketNS::SPEED;
	}
	
	if (input->isKeyDown(ROCKET_LEFT_KEY))             // if move left
	{
		//if (rocketMain.getX() > 0)
		spriteData.x = spriteData.x - frameTime * rocketNS::SPEED;
	}

	if (input->isKeyDown(ROCKET_UP_KEY))               // if move up
	{
		//if (rocketMain.getY() > 0 + rocketMain.getHeight()) // limit move up
		spriteData.y = spriteData.y - frameTime * rocketNS::SPEED;
	}

	if (input->isKeyDown(ROCKET_DOWN_KEY))             // if move down
	{
		//if (rocketMain.getY() < GAME_HEIGHT - rocketMain.getHeight()) // limit move down
		spriteData.y = spriteData.y + frameTime * rocketNS::SPEED;
	}

	/*
	if (input->isKeyDown(ROCKET_ARROW_RIGHT))
	{
		spriteData.angle += frameTime * rocketNS::ROTATION_RATE;
	}

	if (input->isKeyDown(ROCKET_ARROW_LEFT))
	{
		spriteData.angle -= frameTime * rocketNS::ROTATION_RATE;
	}
	*/	
	/*
	if (input->isKeyDown(ROCKET_SPACE_KEY))
	{
		drawBullet();
		shootBullet();
	}
	*/
	/*
	VECTOR2 start(spriteData.x, spriteData.y); //Determine start position of bullet and set it based on rocket position
	for each(Bullet *p in bulletList)
	{
		if (p->getX() == start.x + rocketNS::WIDTH / 4) { spriteData.angle -= frameTime * rocketNS::ROTATION_RATE; }
	}
	*/
	/*
	if (bulletList.empty() == 0)
	{
		spriteData.angle -= frameTime * rocketNS::ROTATION_RATE;
	}
	*/
}

//=============================================================================
// damage
//=============================================================================
void Rocket::damage(WEAPON weapon)
{
	shieldOn = true;
}

/*
void Rocket::shootBullet()
{
	Bullet *a = new Bullet(); //Create new bullet                                                    

	VECTOR2 start(spriteData.x, spriteData.y); //Determine start position of bullet and set it based on rocket position
	//a->setMapX(start.x + rocketNS::WIDTH / 4);
	//a->setMapY(start.y + rocketNS::HEIGHT / 2);
	a->setMapX(GAME_WIDTH / 2);
	a->setMapY(GAME_HEIGHT/4);
	/*
	// bullet texture
	TextureManager bulletTexture;	// bullet texture
	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	if (!a->initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &bulletTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	*/
	/*
	player.x -= a->getWidth() / 2 * a->getScale();
	player.x -= bulletNS::WIDTH / 4;
	player.y -= a->getHeight() / 2 * a->getScale();
	player.y -= bulletNS::HEIGHT / 2;
	*/
	/*
	a->setVStart(start); //Set velocity?
	//a->setvtarget(player); //For chase?
	bulletList.push_back(a); //Append to list bulletList
	*/
/*
}
*/

/*
void Rocket::drawBullet()
{
	/*
	for (std::vector<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); )
	{
		if ((*it)->getdel() == true) //if bullets have collided with player, del of bullet set to true
		{
			SAFE_DELETE(*it);
			it = bulletlist.erase(it);
		}
		else
		{
			++it;
		}
	}
	*/
	/*
	for each(Bullet *p in bulletList)
	{
		graphics->spriteBegin();
		p->draw();
		graphics->spriteEnd();
	}
	*/
/*
}
*/
