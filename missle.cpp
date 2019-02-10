//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "missle.h"

//=============================================================================
// default constructor
//=============================================================================
Missle::Missle() : Entity()
{
	spriteData.width = missleNS::WIDTH;           // size of missle
	spriteData.height = missleNS::HEIGHT;
	spriteData.rect.bottom = missleNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = missleNS::WIDTH;
	velocity.x = 0;
	velocity.y = 0;
	frameDelay = missleNS::MISSLE_ANIMATION_DELAY;
	startFrame = missleNS::MISSLE_START_FRAME;     // first frame of ship animation
	endFrame = missleNS::MISSLE_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = missleNS::WIDTH / 2.0;
	mass = missleNS::MASS;
	collisionType = entityNS::CIRCLE;

	explosionOn = false;
}

//=============================================================================
// Initialize
// Post: returns true if successful, false if failed
//=============================================================================
bool Missle::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	
	// explosion texture
	if (!explosionTexture.initialize(gamePtr->getGraphics(), EXPLOSION_ADVANCED_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing explosion advanced texture"));

	explosion.initialize(gamePtr->getGraphics(), 256, 256, 8, &explosionTexture);
	explosion.setFrames(missleNS::EXPLOSION_START_FRAME, missleNS::EXPLOSION_END_FRAME);
	explosion.setCurrentFrame(missleNS::EXPLOSION_START_FRAME);
	explosion.setFrameDelay(missleNS::EXPLOSION_ANIMATION_DELAY);
	explosion.setLoop(false);               // do not loop animation
	
	/*
	// explosion texture
	if (!explosionTexture.initialize(gamePtr->getGraphics(), EXPLOSION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing explosion texture"));

	explosion.initialize(gamePtr->getGraphics(), 50, 50, 1, &explosionTexture);
	explosion.setFrames(missleNS::EXPLOSION_START_FRAME, missleNS::EXPLOSION_END_FRAME);
	explosion.setCurrentFrame(missleNS::EXPLOSION_START_FRAME);
	explosion.setFrameDelay(missleNS::EXPLOSION_ANIMATION_DELAY);
	explosion.setLoop(false);               // do not loop animation
	*/
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw missle
//=============================================================================
void Missle::draw()
{
	if (explosionOn == true)
	{
		explosion.setVisible(true);
		explosion.draw();
		explosion.setX(spriteData.x - explosion.getWidth() / 2 * explosion.getScale());
		explosion.setY(spriteData.y - explosion.getHeight() / 2 * explosion.getScale());
	}
		
	else
	{
		Image::draw();
	}	
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Missle::update(float frameTime)
{
	if (explosionOn == true)
	{
		explosion.update(frameTime);

		if (explosion.getAnimationComplete() == true)    
		{		             
			visible = false;
			active = false;
			explosion.setAnimationComplete(false);
			explosion.setCurrentFrame(missleNS::EXPLOSION_START_FRAME);
			explosionOn = false;
		}
		
	}

	else
	{
		Entity::update(frameTime);

		/*
		velocity.y = velocity.y + gravity * frameTime; // updating the y component of the velocity
		spriteData.x = spriteData.x + velocity.x * frameTime;
		spriteData.y = spriteData.y + ((velocity.y * frameTime) - ((gravity / 2) * frameTime * frameTime));
		spriteData.angle += theta * frameTime;
		*/

		// Missle Shot (Ability 3)
		if (missleOnCooldown == false)
		{
			active = true;
			if (input->isKeyDown(THREE_KEY))
			{
				explosionOn = false;
				missleActive = true;
				visible = true;
				missleOnCooldown = true;
				alreadyFired = false;
			}
		}

		else //missle shot is on cooldown
		{
			if (alreadyFired == false)
			{
				if (input->getMouseRButton() == true)
				{
					explode();
					audio->playCue(EXPLOSION1);
				}
			}
				
			velocity.y = velocity.y + gravity * frameTime; // updating the y component of the velocity
			spriteData.x = spriteData.x + velocity.x * frameTime;
			spriteData.y = spriteData.y + ((velocity.y * frameTime) - ((gravity / 2) * frameTime * frameTime));
			spriteData.angle += theta * frameTime;

			missleCooldownTimer -= frameTime;
			if (missleCooldownTimer < 0)
			{
				missleOnCooldown = false;
				missleCooldownTimer = 15;
				missleActive = false;			
			}
		}	
	}	
}

void Missle::explode()
{
	//explosion.setScale(3.0);
	active = false;
	explosionOn = true;
	velocity.x = 1.0f;
	velocity.y = 1.0f;
	alreadyFired = true;
}

void Missle::shoot(Entity *whereFrom, float frameTime)
{
	spriteData.x = whereFrom->getCenterX() - spriteData.width / 2 * spriteData.scale;
	spriteData.y = whereFrom->getCenterY() - spriteData.height / 2 * spriteData.scale;

	float initialVelocity = 50;

	// Horizonal Vx component of initial velocity
	velocity.x = initialVelocity * cos(theta);

	// Horizonal Vy component of initial velocity
	velocity.y = initialVelocity * sin(theta);
}