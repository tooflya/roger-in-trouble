#ifndef CONST_FOLLOWENEMY
#define CONST_FOLLOWENEMY

#include "FollowEnemy.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

FollowEnemy::FollowEnemy(Entity* pFollowEntity) :
	BaseEnemy("enemies/onion/onion-animation.png", 7, 2)
	{
		this->mFollowEntity = pFollowEntity;
		
		this->setAsCollidable();

		this->setBarsManagement(true, false);

		this->animate(0.1f);
	}

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

Entity* FollowEnemy::deepCopy()
{
	return new FollowEnemy(this->mFollowEntity);
}

void FollowEnemy::move(float pDeltaTime)
{
	float vectorX = this->getCenterX() - this->mFollowEntity->getCenterX();
	float vectorY = this->getCenterY() - this->mFollowEntity->getCenterY();

	CCPoint vector = Utils::vectorNormalize(vectorX, vectorY, this->getSpeed(pDeltaTime));

	this->setCenterPosition(this->getCenterX() - vector.x, this->getCenterY() - vector.y);
}

#endif