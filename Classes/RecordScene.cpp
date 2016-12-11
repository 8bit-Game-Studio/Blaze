#include "Stdafx.h"

USING_NS_CC;

CCScene* RecordScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	RecordScene *layer = RecordScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool RecordScene::init()
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
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"OptionNormal.png",
		"OptionSelected.png",
		this,
		menu_selector(RecordScene::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	int iRecordScore = userDefault->getIntegerForKey("record",0);
	char arrStr[128] = "Best Score : ", arrTemp[64] = "";
	sprintf(arrTemp,"%06d",iRecordScore); 
	strcat(arrStr,arrTemp);

	CCLabelTTF* pLabel = CCLabelTTF::create(arrStr, "Arial", 50);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height / 1.5 - pLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("player.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/3 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	return true;
}


void RecordScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->resume();

	CCDirector::sharedDirector()->purgeCachedData();

	CCScene * scene = MenuScene::scene();  
	CCDirector::sharedDirector()->replaceScene((CCTransitionSlideInR::create(0.5, scene)));
}
