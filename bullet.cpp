#include "bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Bullet::Bullet() : Entity() 
{
	isFired = false; // default to bullet not fired
	waitShotTimer = 0.0f;
	spriteData.width = bulletNS::WIDTH;           // size of bullet
	spriteData.height = bulletNS::HEIGHT;
	spriteData.x = GAME_WIDTH / 4;                   // location on screen
	spriteData.y = GAME_HEIGHT /2;
	spriteData.rect.bottom = bulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bulletNS::WIDTH;
	velocity.x = 10;
	velocity.y = 10;
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
	if (isFired == true)
	{
		Image::draw();	
	}	
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bullet::update(float frameTime) 
{
	waitShotTimer -= frameTime;
	Entity::update(frameTime);
	spriteData.x = spriteData.x + frameTime * bulletNS::SPEED;
}

//=============================================================================
// damage
//=============================================================================
void Bullet::damage(WEAPON weapon){}

void Bullet::shoot(Entity *ship)
{	
	if (waitShotTimer <= 0.0f)
	{
		waitShotTimer = bulletNS::WAIT_SHOOT; //Resets the shotTimer using namespace value
		isFired = true;
		spriteData.x = ship->getCenterX() - spriteData.width / 2;
		spriteData.y = ship->getCenterY() - spriteData.height / 2;
	}
}


