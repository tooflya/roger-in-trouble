#ifndef CONST_BACKGROUNDSTARSMANAGER
#define CONST_BACKGROUNDSTARSMANAGER

#include "BackgroundStarsManager.h"

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

BackgroundStarsManager::BackgroundStarsManager(CCNode* pScreen)
{
	pScreen->addChild(this);

	this->mTextures = new CCArray();
	this->mTextures->initWithCapacity(10);

	this->mTextures->addObject(new Texture("bg/bigstar.png", 1, 1));
	this->mTextures->addObject(new Texture("bg/bigstar2.png", 1, 1));
	this->mTextures->addObject(new Texture("bg/bigstar3.png", 1, 1));
	this->mTextures->addObject(new Texture("bg/mediumstar.png", 1, 1));
	this->mTextures->addObject(new Texture("bg/mediumstar2.png", 1, 1));
	this->mTextures->addObject(new Texture("bg/mediumstar3.png", 1, 1));
	this->mTextures->addObject(new Texture("bg/smallstar.png", 1, 1));
	this->mTextures->addObject(new Texture("bg/smallstar2.png", 1, 1));
	this->mTextures->addObject(new Texture("bg/smallstar3.png", 1, 1));

	for(int i = 0; i < 1000; i++)
	{
		Entity* star = new Entity("bg/bigstar.png");

		star->create()->changeTexture((Texture*) this->mTextures->objectAtIndex(Utils::random(0, 8)));

		star->setCenterPosition(Utils::random(-Options::CAMERA_WIDTH, Options::CAMERA_WIDTH * 2), Utils::random(-Options::CAMERA_HEIGHT, Options::CAMERA_HEIGHT * 2));
		star->setSpeed(0.95f + Utils::randomf(0.0f, 100.0f));

		this->addChild(star);
	}

	this->scheduleUpdate();
}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

void BackgroundStarsManager::update(float pDeltaTime)
{
	CCNode::update(pDeltaTime);

	for(int i = 0; i < 1000; i++)
	{
		Entity* star = (Entity*) this->getChildren()->objectAtIndex(i);

		if(star->getCenterY() < -Options::CAMERA_HEIGHT)
		{
			star->setCenterPosition(star->getCenterX(), Options::CAMERA_HEIGHT * 2);
		}
		else
		{
			star->setCenterPosition(star->getCenterX(), star->getCenterY() - star->getSpeed(pDeltaTime));
		}
	}
}

#endif