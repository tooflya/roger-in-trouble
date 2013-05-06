#ifndef CONST_GAS
#define CONST_GAS

#include "Gas.h"

// ===========================================================
// Init
// ===========================================================

void Gas::constructor(Entity* pHero)
{
	this->mHero = pHero;
}

// ===========================================================
// Constructors
// ===========================================================

Gas::Gas(Entity* pHero)
{
	this->constructor(pHero);
}

Gas::Gas(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Entity* pHero) :
	Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->constructor(pHero);
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

// ===========================================================
// Virtual methods
// ===========================================================

Entity* Gas::create()
{
	this->animate(0.08f);

	this->mShadow = (((Hero*) this->mHero)->mGasesShadows->create());

	this->mShadow->setCurrentFrameIndex(this->getCurrentFrameIndex());
	this->mShadow->setCenterPosition(this->getCenterX(), this->getCenterY() - Utils::coord(10));
	this->mShadow->animate(0.08f);
	

	return Entity::create();
}

void Gas::onAnimationCircleEnd()
{
	this->mShadow->destroy();
	this->destroy(); // Some trouble here
}

Gas* Gas::deepCopy()
{
	return new Gas("main-character/gas-animation.png", 12, 1, this->mHero);
}

void Gas::setCurrentFrameIndex(int pIndex)
{
	Entity::setCurrentFrameIndex(pIndex);
}

void Gas::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);

	if(this->getCurrentFrameIndex() < 1)
	{
		this->setCenterPosition(this->mHero->getCenterX(), this->mHero->getCenterY() - Utils::coord(25));
	}

	 // WTF I'M DOING HERE????????????????? (this->mShadow)
}

#endif