#include "bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Bullet::Bullet() : Entity() 
{
	isFired = false; // default to bullet not fired
	spriteData.width = bulletNS::WIDTH;           // size of bullet
	spriteData.height = bulletNS::HEIGHT;
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
	collisionType = entityNS::BOX;	
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
	Entity::update(frameTime); 
	spriteData.x = spriteData.x + frameTime * velocity.x;
	spriteData.y = spriteData.y + frameTime * velocity.y;
}

void Bullet::shoot(Entity *whereFrom, float frameTime)
{	
	isFired = true;
	velocity.x = cos(whereFrom->getRadians()) * bulletNS::SPEED; //basic trigo toa coa soh
	velocity.y = sin(whereFrom->getRadians()) * bulletNS::SPEED;
	spriteData.x = whereFrom->getCenterX() - spriteData.width / 2; //starting position
	spriteData.y = whereFrom->getCenterY() - spriteData.height / 2;
}

void Bullet::shootHoming(Entity *whereFrom, Entity *whereTo, float frameTime)
{
	isFired = true;
	VECTOR2 fromHere(whereFrom->getCenterX() - spriteData.width / 2, whereFrom->getCenterY() - spriteData.height / 2);
	VECTOR2 goingTo(whereTo->getCenterX() - getCenterX(), whereTo->getCenterY() - getCenterY());
	VECTOR2 minus(goingTo - fromHere);
	Graphics::Vector2Normalize(&minus);
	velocity = minus * bulletNS::SPEED;
}


