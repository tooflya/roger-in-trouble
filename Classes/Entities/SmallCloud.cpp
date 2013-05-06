#ifndef CONST_SMALLCLOUD
#define CONST_SMALLCLOUD

#include "SmallCloud.h"

// ===========================================================
// Init
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

SmallCloud::SmallCloud()
{
}

SmallCloud::SmallCloud(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
	}

// ===========================================================
// Getters
// ===========================================================

// ===========================================================
// Setters
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

void SmallCloud::init(float pBoundsX1, float pBoundsX2, float pBoundsY1, float pBoundsY2, bool pRandomX)
{
	this->mBoundsX1 = pBoundsX1;
	this->mBoundsX2 = pBoundsX2;
	this->mBoundsY1 = pBoundsY1;
	this->mBoundsY2 = pBoundsY2;

	float x = pRandomX ? Utils::random(pBoundsX1, pBoundsX2) : (Utils::random(0, 1) == 1 ? pBoundsX1 : pBoundsX2);
	float y = Utils::random(pBoundsY1, pBoundsY2);

	this->setCenterPosition(x, y);

	this->mCenterX = x;
	this->mCenterY = y;

	float potencialSpeed = Utils::randomf(-150.0, 150.0);

	if(potencialSpeed < 0)
	{
		if(potencialSpeed > -50)
		{
			potencialSpeed = -50;
		}
	}
	else
	{
		if(potencialSpeed < 50)
		{
			potencialSpeed = 50;
		}
	}

	potencialSpeed = pRandomX ? potencialSpeed : (x > Options::CENTER_X ? -abs(potencialSpeed) : abs(potencialSpeed));

	this->setSpeed(potencialSpeed);
}

// ===========================================================
// Virtual methods
// ===========================================================

Entity* SmallCloud::create()
{
	SmallCloud* entity = ((SmallCloud*) Entity::create());

	entity->setCurrentFrameIndex(Utils::random(0, 2));

	return entity;
}

SmallCloud* SmallCloud::deepCopy()
{
	return new SmallCloud("main-menu/main-menu-cloud-sprite.png", 1, 3);
}

void SmallCloud::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);

	this->mCenterX = this->getCenterX() + this->getSpeed(pDeltaTime);

	this->setRotation(-(Options::CAMERA_CENTER_X - this->getCenterX()) / 30);
	this->setCenterPosition(this->mCenterX, this->mCenterY - ((this->getCenterX() > Options::CAMERA_CENTER_X ? this->getRotation() : -this->getRotation()) * 5));

	if(!this->collideWith(((Entity*) this->getParent()), 2.0f))
	{
		this->destroy();
	}
}

#endif