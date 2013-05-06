#ifndef CONST_ENEMYGROUP_H
#define CONST_ENEMYGROUP_H

#include "cocos2d.h"

#include "EntityManager.h"

using namespace cocos2d;

class Level;

class EnemyGroup : public CCNode
{
	protected:
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

		// ===========================================================
		// Methods
		// ===========================================================

		// ===========================================================
		// Virtual Methods
		// ===========================================================

	private:
		// ===========================================================
		// Inner Classes
		// ===========================================================

		// ===========================================================
		// Constants
		// ===========================================================

		// ===========================================================
		// Fields
		// ===========================================================

		CCArray* mGroups;

		float mTimeOutSinceLastWave;
		float mTimeOutSinceLastWaveElapsed;

		Level* mWorld;

		CCPoint* mEmmiters;

		// ===========================================================
		// Constructors
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

	public:
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

		EnemyGroup(Level* pWorld, float pTimeOutSinceLastWave);

		// ===========================================================
		// Methods
		// ===========================================================

		EnemyGroup* addEnemy(int pCount, int pType, int pLevel);
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

		void update(float pDeltaTime);
};

#endif