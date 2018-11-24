#include "bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Bullet::Bullet() : Entity() 
{
	spriteData.width = bulletNS::WIDTH;           // size of bullet
	spriteData.height = bulletNS::HEIGHT;
	spriteData.x = bulletNS::X;                   // location on screen
	spriteData.y = bulletNS::Y;
	spriteData.rect.bottom = bulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bulletNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = bulletNS::BULLET_ANIMATION_DELAY;
	startFrame = bulletNS::BULLET_START_FRAME;     // first frame of ship animation
	endFrame = bulletNS::BULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = bulletNS::WIDTH / 2.0;
	mass = bulletNS::MASS;
	collisionType = entityNS::CIRCLE;		
}

//=============================================================================
// Initialize
// Post: returns true if successful, false if failed
//=============================================================================
bool Bullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw bullet
//=============================================================================
void Bullet::draw()
{
	Image::draw();              // draw bullet
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bullet::update(float frameTime) 
{
	Entity::update(frameTime);
	// Bounce off walls
	if (spriteData.x > GAME_WIDTH - bulletNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - bulletNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;
	}
	if (spriteData.y > GAME_HEIGHT - bulletNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - bulletNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;
	}
	//spriteData.x = spriteData.x + frameTime * bulletNS::SPEED;
	//Bullet *bullet = new Bullet();
	//Bullet::draw();
	if (input->isKeyDown(ROCKET_ARROW_UP))
	{
		spriteData.y = spriteData.y - frameTime * bulletNS::SPEED;
	}
	if (input->isKeyDown(ROCKET_ARROW_DOWN))
	{
		spriteData.y = spriteData.y + frameTime * bulletNS::SPEED;
	}
	if (input->isKeyDown(ROCKET_ARROW_LEFT))
	{
		spriteData.x = spriteData.x - frameTime * bulletNS::SPEED;
	}
	if (input->isKeyDown(ROCKET_ARROW_RIGHT))
	{
		spriteData.x = spriteData.x + frameTime * bulletNS::SPEED;
	}
}


//=============================================================================
// damage
//=============================================================================
void Bullet::damage(WEAPON weapon){}
