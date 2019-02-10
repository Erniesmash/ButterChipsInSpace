//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "dfb.h"
#include "dfbbullet.h"

//=============================================================================
// default constructor
//=============================================================================
DfbBullet::DfbBullet() : Entity()
{
	spriteData.width = dfbbulletNS::WIDTH;           // size of Ship1
	spriteData.height = dfbbulletNS::HEIGHT;
	spriteData.x = dfbbulletNS::X;                   // location on screen
	spriteData.y = dfbbulletNS::Y;
	spriteData.rect.bottom = dfbbulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = dfbbulletNS::WIDTH;
	velocity.x = 1;                             // velocity X
	velocity.y = 1;                             // velocity Y
	frameDelay = dfbbulletNS::DFBBULLET_ANIMATION_DELAY;
	startFrame = dfbbulletNS::DFBBULLET_START_FRAME;     // first frame of ship animation
	endFrame = dfbbulletNS::DFBBULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = dfbbulletNS::WIDTH / 2.0;
	mass = dfbbulletNS::MASS;
	collisionType = entityNS::CIRCLE;
	collided = false;
	bounce = false;
}

//=============================================================================
// Initialize the DfbBullet.
// Post: returns true if successful, false if failed
//=============================================================================
bool DfbBullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void DfbBullet::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void DfbBullet::update(float frameTime)
{
	Entity::update(frameTime);
	//spriteData.angle += frameTime * dfbbulletNS::ROTATION_RATE;  // rotate the ship

	//for spray and 1 shot
	
	spriteData.x += frameTime * velocity.x;			// move ship along X
	spriteData.y += frameTime * velocity.y;         // move ship along Y


	if (bounce == true)
	{
		if (spriteData.x > GAME_WIDTH - dfbbulletNS::WIDTH)    // if hit right screen edge
		{
			spriteData.x = GAME_WIDTH - dfbbulletNS::WIDTH;    // position at right screen edge
			velocity.x = -velocity.x;                   // reverse X direction
			bounce = false;
		}

		if (spriteData.y > GAME_HEIGHT - dfbbulletNS::HEIGHT)  // if hit bottom screen edge
		{
			spriteData.y = GAME_HEIGHT - dfbbulletNS::HEIGHT;  // position at bottom screen edge
			velocity.y = -velocity.y;                   // reverse Y direction
			bounce = false;
		}
		else if (spriteData.y < 0)                    // else if hit top screen edge
		{
			spriteData.y = 0;                           // position at top screen edge
			velocity.y = -velocity.y;                   // reverse Y direction
			bounce = false;
		}
	}

	if (bounce == false)
	{
		// destroy at walls
		if (spriteData.x > GAME_WIDTH + dfbbulletNS::WIDTH * dfbbulletNS::WIDTH)    // if hit right screen edge
		{
			collided = true;
		}
		else if (spriteData.x < -dfbbulletNS::WIDTH * dfbbulletNS::WIDTH)                    // else if hit left screen edge
		{
			collided = true;
		}
		if (spriteData.y > GAME_HEIGHT + dfbbulletNS::HEIGHT * dfbbulletNS::HEIGHT)  // if hit bottom screen edge
		{
			collided = true;
		}
		else if (spriteData.y < -dfbbulletNS::HEIGHT * dfbbulletNS::HEIGHT)                    // else if hit top screen edge
		{
			collided = true;
		}
	}
}

void DfbBullet::getDir(float x, float y, float fromx, float fromy, float speed)
{
	spriteData.x = fromx - spriteData.width / 2;
	spriteData.y = fromy - spriteData.height / 2;
	VECTOR2 travel(x - getCenterX(), y - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * speed;
}

void DfbBullet::appImpulse(float xpos, float ypos, float angle, float speed)
{
	spriteData.x = xpos - spriteData.width / 2;
	spriteData.y = ypos - spriteData.height / 2;

	//D3DXMATRIX matrix;
	//D3DXMatrixTranslation

	VECTOR2 ref(0 - getCenterX(), 0);
	//VECTOR2 travel = matrix * ref;
	VECTOR2 travel(Graphics::Vector2Length(&ref)*cos((angle/360)*(2*PI)), Graphics::Vector2Length(&ref)*sin((angle / 360)*(2*PI)));
	Graphics::Vector2Normalize(&travel);
	velocity = travel * speed;
}