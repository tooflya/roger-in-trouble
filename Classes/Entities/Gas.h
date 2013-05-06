#ifndef CONST_GAS_H
#define CONST_GAS_H

#include "cocos2d.h"

#include "Entity.h"
#include "Hero.h"
#include "Options.h"

using namespace cocos2d;

class Gas : public Entity
{
	protected:
		// ===========================================================
		// Protected fields
		// ===========================================================

	private:
		// ===========================================================
		// Constructor private function
		// ===========================================================

		void constructor(Entity* pHero);

		// ===========================================================
		// Private fields
		// ===========================================================

		Entity* mHero;

		Entity* mShadow;

		// ===========================================================
		// Private methods
		// ===========================================================

	public:
		// ===========================================================
		// Constructors
		// ===========================================================

		Gas(Entity* pHero);
		Gas(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Entity* pHero);

		// ===========================================================
		// Getters
		// ===========================================================

		// ===========================================================
		// Setters
		// ===========================================================

		// ===========================================================
		// Checkers
		// ===========================================================

		// ===========================================================
		// Events
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================

		// ===========================================================
		// Virtual methods
		// ===========================================================

		virtual Entity* create();

		virtual void onAnimationCircleEnd();

		virtual void setCurrentFrameIndex(int pIndex);

		virtual void update(float pDeltaTime);

		virtual Gas* deepCopy();
};

#endif