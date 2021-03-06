#ifndef CONST_SCREENMANAGER_H
#define CONST_SCREENMANAGER_H

#include "cocos2d.h"

#include "Level.h"
#include "GameOver.h"
#include "GameWon.h"

using namespace cocos2d;

class ScreenManager
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

		Screen* mScreens[3];

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

		ScreenManager();

		// ===========================================================
		// Methods
		// ===========================================================

		void generate();
		
		void set(float pAnimationTime, int pIndex);
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================
};

#endif