//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "dfr.h"
#include "dfrbullet.h"

//=============================================================================
// default constructor
//=============================================================================
DfrBullet::DfrBullet() : Entity()
{
	spriteData.width = dfrbulletNS::WIDTH;           // size of Ship1
	spriteData.height = dfrbulletNS::HEIGHT;
	spriteData.x = dfrbulletNS::X;                   // location on screen
	spriteData.y = dfrbulletNS::Y;
	spriteData.rect.bottom = dfrbulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = dfrbulletNS::WIDTH;
	velocity.x = 1;                             // velocity X
	velocity.y = 1;                             // velocity Y
	frameDelay = dfrbulletNS::DFRBULLET_ANIMATION_DELAY;
	startFrame = dfrbulletNS::DFRBULLET_START_FRAME;     // first frame of ship animation
	endFrame = dfrbulletNS::DFRBULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = dfrbulletNS::WIDTH / 2.0;
	mass = dfrbulletNS::MASS;
	collisionType = entityNS::CIRCLE;
	collided = false;
	bounce = false;
	targeted = false;
}

//=============================================================================
// Initialize the DfrBullet.
// Post: returns true if successful, false if failed
//=============================================================================
bool DfrBullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void DfrBullet::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void DfrBullet::update(float frameTime)
{
	Entity::update(frameTime);
	//spriteData.angle += frameTime * dfrbulletNS::ROTATION_RATE;  // rotate the ship

	//for spray and 1 shot
	
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y*/

	if (bounce == true)
	{
		if (spriteData.x > GAME_WIDTH - dfrbulletNS::WIDTH)    // if hit right screen edge
		{
			spriteData.x = GAME_WIDTH - dfrbulletNS::WIDTH;    // position at right screen edge
			velocity.x = -velocity.x;                   // reverse X direction
			bounce = false;
		}

		if (spriteData.y > GAME_HEIGHT - dfrbulletNS::HEIGHT)  // if hit bottom screen edge
		{
			spriteData.y = GAME_HEIGHT - dfrbulletNS::HEIGHT;  // position at bottom screen edge
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
		if (spriteData.x > GAME_WIDTH + dfrbulletNS::WIDTH * dfrbulletNS::WIDTH)    // if hit right screen edge
		{
			collided = true;
		}
		else if (spriteData.x < -dfrbulletNS::WIDTH * dfrbulletNS::WIDTH)                    // else if hit left screen edge
		{
			collided = true;
		}
		if (spriteData.y > GAME_HEIGHT + dfrbulletNS::HEIGHT * dfrbulletNS::HEIGHT)  // if hit bottom screen edge
		{
			collided = true;
		}
		else if (spriteData.y < -dfrbulletNS::HEIGHT * dfrbulletNS::HEIGHT)                    // else if hit top screen edge
		{
			collided = true;
		}
	}
}

void DfrBullet::getDir(float x, float y, float fromx, float fromy, float speed)
{
	spriteData.x = fromx - spriteData.width / 2;
	spriteData.y = fromy - spriteData.height / 2;
	VECTOR2 travel(x - getCenterX(), y - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * speed;
}

void DfrBullet::appImpulse(float xpos, float ypos, float angle, float speed)
{
	spriteData.x = xpos - spriteData.width / 2;
	spriteData.y = ypos - spriteData.height / 2;

	//D3DXMATRIX matrix;
	//D3DXMatrixTranslation

	VECTOR2 ref(0 - getCenterX(), 0);
	//VECTOR2 travel = matrix * ref;
	VECTOR2 travel(Graphics::Vector2Length(&ref)*cos((angle / 360)*(2 * PI)), Graphics::Vector2Length(&ref)*sin((angle / 360)*(2 * PI)));
	Graphics::Vector2Normalize(&travel);
	velocity = travel * speed;
}