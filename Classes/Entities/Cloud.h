#ifndef CONST_CLOUD_H
#define CONST_CLOUD_H

#include "cocos2d.h"

#include "Entity.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class Cloud : public Entity
{
	protected:
		// ===========================================================
		// Protected fields
		// ===========================================================

		float mBoundsX1;
		float mBoundsX2;
		float mBoundsY1;
		float mBoundsY2;

		float mVectorX;
		float mVectorY;

		bool mIsMove;

	private:
		// ===========================================================
		// Constructor private function
		// ===========================================================

		void constructor();

		// ===========================================================
		// Private fields
		// ===========================================================

		// ===========================================================
		// Private methods
		// ===========================================================

	public:
		// ===========================================================
		// Public fields
		// ===========================================================
		
		// ===========================================================
		// Constructors
		// ===========================================================

		Cloud();
		Cloud(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

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

		void init(float pVectorX, float pVectorY, float pBoundsX1, float pBoundsX2, float pBoundsY1, float pBoundsY2);

		// ===========================================================
		// Virtual methods
		// ===========================================================

		virtual Entity* create();

		virtual void setCurrentFrameIndex(int pIndex);

		virtual void update(float pDeltaTime);

		virtual Cloud* deepCopy();	
};

#endif