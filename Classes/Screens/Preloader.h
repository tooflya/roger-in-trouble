#ifndef CONST_PRELOADER_H
#define CONST_PRELOADER_H

#include "cocos2d.h"

#include "AppDelegate.h"

#include "Screen.h"
#include "Level.h"
#include "ScreenManager.h"

using namespace cocos2d;

class Preloader : public Screen
{
	private:
		int mNumberOfSprites;
		int mNumberOfLoadedSprites;

		Entity* mBackground;
		Entity* mBarBackground;
		Entity* mBar;

		CCLabelTTF* mLoadingText;

	public:
		Preloader(void);

		void loadingCallBack(CCObject *obj);

		virtual void update(float pDeltaTime);
};

#endif