//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

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
	collided = false;
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
	
	spriteData.x += frameTime * velocity.x; //* velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y; //* velocity.y;         // move ship along Y


	if (bounce == true)
	{
		if (spriteData.x > GAME_WIDTH - ebulletNS::WIDTH)    // if hit right screen edge
		{
			spriteData.x = GAME_WIDTH - ebulletNS::WIDTH;    // position at right screen edge
			velocity.x = -velocity.x;                   // reverse X direction
			bounce = false;
		}

		if (spriteData.y > GAME_HEIGHT - ebulletNS::HEIGHT)  // if hit bottom screen edge
		{
			spriteData.y = GAME_HEIGHT - ebulletNS::HEIGHT;  // position at bottom screen edge
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

	else if (bounce == false)
	{
		// destroy at walls
		if (spriteData.x > GAME_WIDTH + ebulletNS::WIDTH * ebulletNS::WIDTH)    // if hit right screen edge
		{
			collided = true;
		}
		else if (spriteData.x < -ebulletNS::WIDTH * ebulletNS::WIDTH)                    // else if hit left screen edge
		{
			collided = true;
		}
		if (spriteData.y > GAME_HEIGHT + ebulletNS::HEIGHT * ebulletNS::HEIGHT)  // if hit bottom screen edge
		{
			collided = true;
		}
		else if (spriteData.y < -ebulletNS::HEIGHT * ebulletNS::HEIGHT)                    // else if hit top screen edge
		{
			collided = true;
		}
	}
}

void EBullet::getDir(float x, float y, float fromx, float fromy, float speed)
{
	spriteData.x = fromx - spriteData.width / 2;
	spriteData.y = fromy - spriteData.height / 2;
	VECTOR2 travel(x - getCenterX(), y - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * speed;
}

void EBullet::appImpulse(float xpos, float ypos, float angle, float speed)
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

