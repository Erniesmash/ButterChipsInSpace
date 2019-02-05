#include "skull.h"
#include "spacewar.h"

//=============================================================================
// default constructor
//=============================================================================
Skull::Skull() : Entity()
{
	spriteData.width = skullNS::WIDTH;           // size of Ship1
	spriteData.height = skullNS::HEIGHT;
	spriteData.x = skullNS::X;                   // location on screen
	spriteData.y = skullNS::Y;
	spriteData.rect.bottom = skullNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = skullNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = skullNS::SKULL_ANIMATION_DELAY;
	startFrame = skullNS::SKULL_START_FRAME;     // first frame of Skull animation
	endFrame = skullNS::SKULL_END_FRAME;     // last frame of Skull animation
	currentFrame = startFrame;
	radius = skullNS::WIDTH / 2.0;
	mass = skullNS::MASS;
	health = skullNS::SKULL_HEALTH;
	collisionType = entityNS::CIRCLE;
	active = false;
	dead = false;
	imgChanged = false;
	entered = false;
	enteredChanged == false;
	textcols = skullNS::TEXTURE_COLS;
}

//=============================================================================
// Initialize the Skull.
// Post: returns true if successful, false if failed
//=============================================================================
bool Skull::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	sw = gamePtr;
	//skullbTexture.initialize(graphics, SKULLBULLET_IMAGE);
	//hbTexture.initialize(graphics, HEALTHBAR_IMAGE);
	hb.initialize(sw, hbNS::WIDTH, hbNS::HEIGHT, hbNS::TEXTURE_COLS, &hbTexture);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

//=============================================================================
// draw the Skull
//=============================================================================
void Skull::draw()
{
	Image::draw();
	hb.draw();
	// draw Skull
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Skull::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.angle += frameTime * skullNS::ROTATION_RATE;  // rotate the Skull


	if (enteredChanged == true && entered == false)
	{
		float x = getCenterX();
		spriteData.width = skullNS::ACTIVE_WIDTH;
		spriteData.height = skullNS::ACTIVE_HEIGHT;
		textcols = skullNS::ACTIVE_TEXTURE_COLS;
		startFrame = skullNS::ACTIVE_START_FRAME;
		endFrame = skullNS::ACTIVE_END_FRAME;
		currentFrame == skullNS::ACTIVE_START_FRAME;
		spriteData.x = x - skullNS::ACTIVE_WIDTH / 2;
		entered = true;
	}

	if (active == true)
	{
		spriteData.x -= frameTime * skullNS::SPEED;         // move Skull along X
		//initialize hb
		hbTexture.initialize(graphics, HEALTHBAR_IMAGE);

		hb.setY(spriteData.y - 2 * hbNS::HEIGHT);
		hb.setX(getCenterX() - hbNS::WIDTH / 2);
		hb.setWidth((health / skullNS::SKULL_HEALTH) * hbNS::WIDTH);

		hb.update(frameTime);

		// Bounce off walls
		if (spriteData.x > GAME_WIDTH - skullNS::WIDTH)    // if hit right screen edge
		{
			spriteData.x = GAME_WIDTH - skullNS::WIDTH;    // position at right screen edge
			velocity.x = -velocity.x;                   // reverse X direction
		}
		else if (spriteData.x < 0)                    // else if hit left screen edge
		{
			spriteData.x = 0;                           // position at left screen edge
			velocity.x = -velocity.x;                   // reverse X direction
		}
		if (spriteData.y > GAME_HEIGHT - skullNS::HEIGHT)  // if hit bottom screen edge
		{
			spriteData.y = GAME_HEIGHT - skullNS::HEIGHT;  // position at bottom screen edge
			velocity.y = -velocity.y;                   // reverse Y direction
		}
		else if (spriteData.y < 0)                    // else if hit top screen edge
		{
			spriteData.y = 0;                           // position at top screen edge
			velocity.y = -velocity.y;                   // reverse Y direction
		}

		if (input->isKeyDown(VK_SPACE))
		{
			if (health >= 0)
			{
				health = health - 1;
			}
		}

		if (health <= 0)
		{
			dead = true;
		}
	}

}

void Skull::chase(Entity *target)
{
	VECTOR2 travel(target->getCenterX() - getCenterX(), target->getCenterY() - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * skullNS::SPEED;
}