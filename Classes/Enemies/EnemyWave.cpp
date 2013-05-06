#ifndef CONST_ENEMYWAVE
#define CONST_ENEMYWAVE

#include "EnemyWave.h"

#include "Level.h"

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

EnemyWave::EnemyWave(Level* pWorld)
{
	this->mWorld = pWorld;

	this->scheduleUpdate();
}

// ===========================================================
// Methods
// ===========================================================

EnemyWave* EnemyWave::addGroup(EnemyGroup* pEnemyGroup)
{
	this->addChild(pEnemyGroup);

	return this;
}

// ===========================================================
// Virtual Methods
// ===========================================================

#endif