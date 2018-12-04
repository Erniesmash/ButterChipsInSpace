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
	velocity.x = 1;                             // velocity X
	velocity.y = 1;                             // velocity Y
	frameDelay = ebulletNS::EBULLET_ANIMATION_DELAY;
	startFrame = ebulletNS::EBULLET_START_FRAME;     // first frame of ship animation
	endFrame = ebulletNS::EBULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = ebulletNS::WIDTH / 2.0;
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
}

void EBullet::getDir(Entity *to, Entity *from)
{
	spriteData.x = from->getCenterX() - spriteData.width / 2;
	spriteData.y = from->getCenterY() - spriteData.height / 2;
	VECTOR2 travel(to->getCenterX() - getCenterX(), to->getCenterY() - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * ebulletNS::SPEED;
}

