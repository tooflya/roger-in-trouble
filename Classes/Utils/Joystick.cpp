#ifndef CONST_JOYSTICK
#define CONST_JOYSTICK

#include "Joystick.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

Joystick::Joystick(bool pIsLeftJoystick) :
	Entity(pIsLeftJoystick ? "joysticks/move-1.png" : "joysticks/fire-1.png")
	{
		this->mButton = new Entity(pIsLeftJoystick ? "joysticks/move-2.png" : "joysticks/fire-2.png");
		this->mButton->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2);

		this->addChild(this->mButton);

		this->create()->setOpacity(0.0f);
	}

// ===========================================================
// Methods
// ===========================================================

void Joystick::fade(bool pAction)
{
	if(pAction)
	{
		this->runAction(CCFadeTo::create(0.4f, 255.0f));
	}
	else
	{
		this->runAction(CCFadeTo::create(0.4f, 0.0f));
	}
	
	this->mButton->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2);
}

void Joystick::update(CCPoint pLocation)
{
	float x = pLocation.x - this->getCenterX();
	float y = pLocation.y - this->getCenterY();

	if(x * x + y * y <= 3000.0f)
	{

	}
	else
	{
		float angleRad = atan2(y, x);

		x = cos(angleRad) * 60.5f;
		y = sin(angleRad) * 60.5f;
	}

	this->mVectorX = -x * 10;
	this->mVectorY = -y * 10;
	
	x += this->getWidth() / 2;
	y += this->getHeight() / 2;

	this->mButton->setCenterPosition(x, y);
}

CCPoint Joystick::getVector()
{
	return ccp(this->mVectorX, this->mVectorY);
}

// ===========================================================
// Virtual Methods
// ===========================================================

void Joystick::setOpacity(GLubyte pOpaque)
{
	Entity::setOpacity(pOpaque);

	for(int i = 0; i < this->getChildren()->count(); i++)
	{
		((Entity*) this->getChildren()->objectAtIndex(i))->setOpacity(pOpaque);
	}
}

#endif