// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "ebullet.h"

//=============================================================================
// default constructor
//=============================================================================
EBullet::EBullet() : Entity()
{
	spriteData.width = ebulletNS::WIDTH;           // size of Ship1
	spriteData.height = ebulletNS::HEIGHT;
	spriteData.x = ebulletNS::X;                   // location on screen
	spriteData.y = ebulletNS::Y;
	spriteData.rect.bottom = ebulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = ebulletNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = ebulletNS::EBULLET_ANIMATION_DELAY;
	startFrame = ebulletNS::EBULLET_START_FRAME;     // first frame of ship animation
	endFrame = ebulletNS::EBULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = ebulletNS::WIDTH / 2.0;
	shieldOn = false;
	mass = ebulletNS::MASS;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the EBullet.
// Post: returns true if successful, false if failed
//=============================================================================
bool EBullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	shield.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	shield.setFrames(ebulletNS::SHIELD_START_FRAME, ebulletNS::SHIELD_END_FRAME);
	shield.setCurrentFrame(ebulletNS::SHIELD_START_FRAME);
	shield.setFrameDelay(ebulletNS::SHIELD_ANIMATION_DELAY);
	shield.setLoop(false);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void EBullet::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void EBullet::update(float frameTime)
{
	Entity::update(frameTime);
	//spriteData.angle += frameTime * ebulletNS::ROTATION_RATE;  // rotate the ship
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y

													// Bounce off walls
	/*if (spriteData.x > GAME_WIDTH - ebulletNS::WIDTH)    // if hit right screen edge
	{
		SAFE_DELETE(this);
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - ebulletNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - ebulletNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}*/
}

//=============================================================================
// damage
//=============================================================================
void EBullet::damage(WEAPON weapon)
{
	shieldOn = true;
}

void EBullet::getDir(Entity *a)
{
	velocity.x = -(cos(a->getRadians()) * ebulletNS::SPEED);
	velocity.y = -(sin(a->getRadians()) * ebulletNS::SPEED);
	spriteData.x = a->getCenterX() - spriteData.width / 2;
	spriteData.y = a->getCenterY() - spriteData.height / 2;
}

