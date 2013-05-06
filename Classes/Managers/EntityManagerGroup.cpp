#ifndef CONST_ENTITYMANAGERGROUP
#define CONST_ENTITYMANAGERGROUP

#include "EntityManagerGroup.h"

// ===========================================================
// Init
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

EntityManagerGroup::EntityManagerGroup(int pCapacity)
{
	this->initWithCapacity(pCapacity);

	this->mCount = 0;
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

void EntityManagerGroup::unpacking() // TODO: Maybe some perfomance refactoring? 
{
	float padding = Utils::coord(0.1f);

	for(int i = 0; i < this->mCount; i++)
	{
		Entity* entity1 = ((Entity*) this->objectAtIndex(i));

		if(!entity1->isVisible()) continue;

		for(int j = 0; j < this->mCount; j++)
		{
			Entity* entity2 = ((Entity*) this->objectAtIndex(j));

			if(i == j) continue;
			if(!entity2->isVisible()) continue;

			if(entity1->getShadow()->collideWith(entity2->getShadow()))
			{
				float x1 = entity1->getCenterX();
				float x2 = entity2->getCenterX();

				float y1 = entity1->getCenterY();
				float y2 = entity2->getCenterY();

				entity1->setCenterPosition(x1 + (x1 > x2 ? padding : -padding), y1 + (y1 > y2 ? padding : -padding));
				entity2->setCenterPosition(x2 + (x2 > x1 ? padding : -padding), y2 + (y2 > y1 ? padding : -padding));
			}
		}
	}
}

void EntityManagerGroup::add(EntityManager* pEntityManager) // TODO: Maybe some memory refactoring?
{
	for(int i = 0; i < pEntityManager->getCapacity(); i++)
	{
		this->addObject(pEntityManager->objectAtIndex(i));

		this->mCount++;
	}
}

void EntityManagerGroup::update(float pDeltaTime)
{
	this->unpacking();
}

// ===========================================================
// Virtual methods
// ===========================================================

#endif