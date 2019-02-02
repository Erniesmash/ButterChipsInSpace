#include "dfg.h"
#include "dfgbullet.h"

float height;

//=============================================================================
// default constructor
//=============================================================================
DfgBullet::DfgBullet() : Entity()
{
	spriteData.width = dfgbulletNS::WIDTH;           // size of Ship1
	spriteData.height = dfgbulletNS::HEIGHT;
	spriteData.x = dfgbulletNS::X;                   // location on screen
	spriteData.y = dfgbulletNS::Y;
	spriteData.rect.bottom = dfgbulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = dfgbulletNS::WIDTH;
	velocity.x = 1;                             // velocity X
	velocity.y = 1;                             // velocity Y
	frameDelay = dfgbulletNS::DFGBULLET_ANIMATION_DELAY;
	startFrame = dfgbulletNS::DFGBULLET_START_FRAME;     // first frame of ship animation
	endFrame = dfgbulletNS::DFGBULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = dfgbulletNS::WIDTH / 2.0;
	mass = dfgbulletNS::MASS;
	collisionType = entityNS::CIRCLE;
	collided = false;
	invert = false;
}

//=============================================================================
// Initialize the DfgBullet.
// Post: returns true if successful, false if failed
//=============================================================================
bool DfgBullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void DfgBullet::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void DfgBullet::update(float frameTime)
{
	Entity::update(frameTime);
	//spriteData.angle += frameTime * dfgbulletNS::ROTATION_RATE;  // rotate the ship

	//for spray and 1 shot
	/*
	spriteData.x += frameTime * velocity.x; //* velocity.x;         // move ship along X
	spriteData.y += frameTime * velocity.y;         // move ship along Y*/

	//for wave
	if (invert == true)
	{
		spriteData.x -= frameTime * dfgbulletNS::SPEED;
		spriteData.y = height - ((GAME_HEIGHT / 20)*sin(0.05*spriteData.x));
	}
	if (invert == false)
	{
		spriteData.x -= frameTime * dfgbulletNS::SPEED;
		spriteData.y = height + ((GAME_HEIGHT / 20)*sin(0.05*spriteData.x));
	}

	// destroy at walls
	if (spriteData.x > GAME_WIDTH - dfgbulletNS::WIDTH)    // if hit right screen edge
	{
		collided = true;
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		collided = true;
	}
	if (spriteData.y > GAME_HEIGHT - dfgbulletNS::HEIGHT)  // if hit bottom screen edge
	{
		collided = true;
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		collided = true;
	}
}

void DfgBullet::getDir(Entity *to, Entity *from)
{
	spriteData.x = from->getCenterX() - spriteData.width / 2;
	spriteData.y = from->getCenterY() - spriteData.height / 2;
	VECTOR2 travel(to->getCenterX() - getCenterX(), to->getCenterY() - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * dfgbulletNS::SPEED;
}

void DfgBullet::appImpulse(float xpos, float ypos, float ximp, float yimp)
{
	spriteData.x = xpos - spriteData.width / 2;
	spriteData.y = ypos - spriteData.height / 2;

	VECTOR2 travel(ximp - getCenterX(), yimp - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * dfgbulletNS::SPEED;
}

void DfgBullet::wavy(Entity* from)
{
	spriteData.x = from->getCenterX();
	height = from->getCenterY();
}