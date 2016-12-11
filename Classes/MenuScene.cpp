#include "Stdafx.h"

USING_NS_CC;

CCScene* MenuScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	MenuScene *layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 3. add your codes below...

	//背景标题图片
	CCSprite* pSprite = CCSprite::create("menu_bg.png");
	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite, 0);

	//菜单按钮
	char * pngNames[] = {"menu_1_1.png","menu_1_2.png","menu_2_1.png","menu_2_2.png","menu_3_1.png","menu_3_2.png",};
	ccaItems = CCArray::create();

	for(int i = 0; i < 3; ++ i)
	{
		CCMenuItemImage* ccmiiItem = CCMenuItemImage::create(pngNames[2 * i], pngNames[2 * i + 1], this, menu_selector(MenuScene::menuCallback) );
		ccmiiItem->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - i * 65));
		ccmiiItem->setTag(i);
		ccaItems->addObject(ccmiiItem);
	}

	CCMenu *menu = CCMenu::createWithArray(ccaItems);
	menu->setPosition(ccp(0,0));
	this->addChild(menu);

	return true;
}

void MenuScene::menuCallback(CCObject* pSender)
{
	CCMenuItemImage* ccmiiItem = (CCMenuItemImage*)pSender;
	switch(ccmiiItem->getTag())
	{
	case 0:
	case 3:
		{
			CCDirector::sharedDirector()->resume();

			CCDirector::sharedDirector()->purgeCachedData();

			CCScene * scene = PlayScene::scene();  
			CCDirector::sharedDirector()->replaceScene((CCTransitionSlideInR::create(0.5, scene)));
		}
		break;
	case 1:
		{
			CCDirector::sharedDirector()->resume();

			CCDirector::sharedDirector()->purgeCachedData();

			CCScene * scene = RecordScene::scene();  
			CCDirector::sharedDirector()->replaceScene((CCTransitionSlideInR::create(0.5, scene)));
		}
		break;
	case 2:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
		CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
		CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
#endif
		break;
	case 4:
		{
			CCDirector::sharedDirector()->resume();

			CCDirector::sharedDirector()->purgeCachedData();

			CCScene * scene = MenuScene::scene();  
			CCDirector::sharedDirector()->replaceScene((CCTransitionSlideInR::create(0.5, scene)));
		}
		break;
	}
}
