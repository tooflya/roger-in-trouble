#ifndef CONST_JOYSTICK_H
#define CONST_JOYSTICK_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class Joystick : public Entity
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

		Entity* mButton;

		float mVectorX;
		float mVectorY;

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

		Joystick(bool pIsLeftJoystick);

		// ===========================================================
		// Methods
		// ===========================================================

		void fade(bool pAction);

		void update(CCPoint pLocation);

		CCPoint getVector();
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

		void setOpacity(GLubyte pOpaque);
};

#endif