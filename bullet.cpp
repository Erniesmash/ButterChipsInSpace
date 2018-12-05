//  Module:             Gameplay Programming
//  Assignment1:        Butter Chips in Space
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

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
	velocity.x = 0;
	velocity.y = 0;
	frameDelay = bulletNS::BULLET_ANIMATION_DELAY;
	startFrame = bulletNS::BULLET_START_FRAME;     // first frame of ship animation
	endFrame = bulletNS::BULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = bulletNS::WIDTH / 2.0;
	mass = bulletNS::MASS;
	collisionType = entityNS::BOX;	
	checkCollided = false;
	increaseSpeed = false;
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
	if (increaseSpeed == true)
	{
		velocity.x = cos(whereFrom->getRadians()) * bulletNS::QUICKSPEED; //basic trigo toa coa soh
		velocity.y = sin(whereFrom->getRadians()) * bulletNS::QUICKSPEED;
	}

	if (increaseSpeed == false)
	{
		velocity.x = cos(whereFrom->getRadians()) * bulletNS::SPEED; //basic trigo toa coa soh
		velocity.y = sin(whereFrom->getRadians()) * bulletNS::SPEED;
	}
	spriteData.x = whereFrom->getCenterX() - spriteData.width / 2; //starting position
	spriteData.y = whereFrom->getCenterY() - spriteData.height / 2;
}

void Bullet::shootHoming(Entity *whereFrom, Entity *whereTo, float frameTime)
{
	isFired = true;
	/*
	VECTOR2 fromHere(whereFrom->getCenterX() - spriteData.width / 2, whereFrom->getCenterY() - spriteData.height / 2);
	VECTOR2 goingTo(whereTo->getCenterX() - getCenterX(), whereTo->getCenterY() - getCenterY());
	VECTOR2 arrowVector(goingTo - fromHere);
	Graphics::Vector2Normalize(&arrowVector);
	velocity = arrowVector * bulletNS::SPEED;
	*/
}


