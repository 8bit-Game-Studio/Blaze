#include "Stdafx.h"

USING_NS_CC;

CCScene* PlayScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	PlayScene *layer = PlayScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
	iScore = 0;
	isStop = false;
	iGameOver = false;
	bDestoryExplosionTemp = true;

	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	//add touch event
	setTouchEnabled(true);
	registerWithTouchDispatcher();

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
		menu_selector(PlayScene::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	//CCLabelTTF
	pLabel = CCLabelTTF::create("Score : 000000", "Arial", 24);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width/8,
		origin.y + visibleSize.height - pLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	/////////////////////////////
	// 3. add your codes below...

	// Background starry
	CCSpriteBatchNode* sbnpStarry = CCSpriteBatchNode::create(PATH_PNG_PLAY_BACKGROUND,2);
	sbnpStarry->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sbnpStarry, 0, kTagSBNP_PLAY_BACKGROUN);

	CCSprite* spChildStarry_1 = CCSprite::create(PATH_PNG_PLAY_BACKGROUND);
	spChildStarry_1->setScaleX(visibleSize.width / spChildStarry_1->getTextureRect().getMaxX());
	spChildStarry_1->setScaleY(visibleSize.height / spChildStarry_1->getTextureRect().getMaxY());
	spChildStarry_1->setPositionY(0);
	sbnpStarry->addChild(spChildStarry_1);

	CCSprite* spChildStarry_2 = CCSprite::create(PATH_PNG_PLAY_BACKGROUND);
	spChildStarry_2->setScaleX(visibleSize.width / spChildStarry_2->getTextureRect().getMaxX());
	spChildStarry_2->setScaleY(visibleSize.height / spChildStarry_2->getTextureRect().getMaxY());
	spChildStarry_2->setPositionY(visibleSize.height);
	sbnpStarry->addChild(spChildStarry_2);

	// Fighter
	spFighter = CCSprite::create("player.png");
	spFighter->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(spFighter);

	//
	arrEnemy = CCArray::create();
	arrEnemy->retain();
	arrBullet = CCArray::create();
	arrBullet->retain();

	// gcControl
	gcControl.SetFighterPos(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	//add CallBack Function
	this->schedule( schedule_selector(PlayScene::backgroundClock), 0.05);
	this->schedule( schedule_selector(PlayScene::bulletClock), 0.20);
	this->schedule( schedule_selector(PlayScene::enemyClock), 0.10);
	this->schedule( schedule_selector(PlayScene::playerClock), 0.05);

	return true;
}


// 背景时钟
void PlayScene::backgroundClock(float dt)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSpriteBatchNode* sbnpStarry = (CCSpriteBatchNode*) getChildByTag(kTagSBNP_PLAY_BACKGROUN);

	int PosY = sbnpStarry->getPositionY();
	if(PosY <= - visibleSize.height / 2)
	{
		PosY = visibleSize.height / 2;
	}
	else
	{
		-- PosY;
	}
	sbnpStarry->setPositionY(PosY);
}


void PlayScene::bulletClock(float dt)
{
	// Bullet
	CCSprite* spBullet = CCSprite::create("bullet.png");
	spBullet->setPosition(ccp(gcControl.GetFighterPos().x,gcControl.GetFighterPos().y + 20));
	this->addChild(spBullet);
	arrBullet->addObject(spBullet);

	float fTime = 1.0 - 1.0 * gcControl.GetFighterPos().y / ((CCDirector::sharedDirector()->getWinSize().height + spBullet->getContentSize().height / 2.0));

	CCSequence* seqAction = CCSequence::create(
		CCMoveTo::create(fTime,ccp(gcControl.GetFighterPos().x,CCDirector::sharedDirector()->getWinSize().height + spBullet->getContentSize().height / 2)),
		CCCallFuncN::create(this,callfuncN_selector(PlayScene::DestoryBullet)),
		NULL
		);
	spBullet->runAction(seqAction);
}


void PlayScene::enemyClock(float dt)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	// Bullet
	CCSprite* spEnemy = CCSprite::create("enemy.png");
	spEnemy->setPosition(ccp(((float)rand()/RAND_MAX) * visibleSize.width, CCDirector::sharedDirector()->getWinSize().height + spEnemy->getContentSize().height / 2.0));
	this->addChild(spEnemy);
	arrEnemy->addObject(spEnemy);

	CCSequence* seqAction = CCSequence::create(
		CCMoveTo::create(2,ccp(gcControl.GetFighterPos().x,- spEnemy->getContentSize().height / 2)),
		CCCallFuncN::create(this,callfuncN_selector(PlayScene::DestoryEnemy)),
		NULL
		);
	spEnemy->runAction(seqAction);
}


void PlayScene::playerClock(float tmd)
{
	for(int j = arrEnemy->count() - 1;j >= 0 ;-- j)
	{
		if(CheckCrush(spFighter->getPosition(),20,((CCSprite*)arrEnemy->objectAtIndex(j))->getPosition(),20))
		{
			CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

			CCLabelTTF* pLabel = CCLabelTTF::create("Game Over", "Arial", 50);
			pLabel->setPosition(ccp(visibleSize.width / 2,visibleSize.height / 2));

			this->unschedule( schedule_selector(PlayScene::bulletClock));
			this->unschedule( schedule_selector(PlayScene::playerClock));

			spFighter->setOpacity(0);

			if(userDefault->getIntegerForKey("record",0) < iScore)
			{
				userDefault->setIntegerForKey("record",iScore);
			}
			iScore = 0;
			iGameOver = true;

			CreateExplosion(((CCSprite*)arrEnemy->objectAtIndex(j))->getPosition());
			CreateExplosion(spFighter->getPosition(),false);

			DestoryEnemy((CCSprite*)arrEnemy->objectAtIndex(j));
			this->addChild(pLabel, 1);

			break;
		}
		for(int i = arrBullet->count() - 1;i >= 0 ;-- i)
		{
			if(CheckCrush(((CCSprite*)arrBullet->objectAtIndex(i))->getPosition(),15,((CCSprite*)arrEnemy->objectAtIndex(j))->getPosition(),20))
			{
				char arrStr[128] = "Score : ", arrTemp[64] = "";
				sprintf(arrTemp,"%06d",++ iScore); 
				strcat(arrStr,arrTemp);

				pLabel->setString(arrStr);

				DestoryBullet((CCSprite*)arrBullet->objectAtIndex(i));
				CreateExplosion(((CCSprite*)arrEnemy->objectAtIndex(j))->getPosition());
				DestoryEnemy((CCSprite*)arrEnemy->objectAtIndex(j));
				break;
			}
		}
	}
}


void PlayScene::DestoryBullet(CCNode* pSender)
{
	CCSprite* bullet = (CCSprite*)pSender;
	arrBullet->removeObject(bullet);
	this->removeChild(bullet,true);
}


void PlayScene::DestoryEnemy(CCNode* pSender)
{
	CCSprite* enemy = (CCSprite*)pSender;
	arrEnemy->removeObject(enemy);
	this->removeChild(enemy,true);
}


void PlayScene::CreateExplosion(CCPoint newPos,bool isEnemy)
{
	//
	CCSize szWin = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* pSprite = CCSprite::create();//创建一个精灵以执行动画
	pSprite->setPosition(newPos);
	this->addChild(pSprite);

	CCAnimation* pAnimation = CCAnimation::create();
	if(isEnemy)
	{
		pAnimation->addSpriteFrameWithFileName(PATH_PNG_EXPLOSION_1);
		pAnimation->addSpriteFrameWithFileName(PATH_PNG_EXPLOSION_2);
		pAnimation->addSpriteFrameWithFileName(PATH_PNG_EXPLOSION_3);
		pAnimation->addSpriteFrameWithFileName(PATH_PNG_EXPLOSION_4);
	}
	else
	{
		pAnimation->addSpriteFrameWithFileName(PATH_PNG_EXPLOSION1);
		pAnimation->addSpriteFrameWithFileName(PATH_PNG_EXPLOSION2);
		pAnimation->addSpriteFrameWithFileName(PATH_PNG_EXPLOSION3);
		pAnimation->addSpriteFrameWithFileName(PATH_PNG_EXPLOSION4);
	}
	pAnimation->setDelayPerUnit(0.1f);//每帧停留的时间
	pAnimation->setRestoreOriginalFrame(false);//动画播放完成后是否返回到原始帧
	CCSequence* seqAction = CCSequence::create(
		CCAnimate::create(pAnimation),
		CCCallFuncN::create(this,callfuncN_selector(PlayScene::DestoryExplosion)),
		NULL
		);
	pSprite->runAction(seqAction);
}

void PlayScene::DestoryExplosion(CCNode* pSender)
{
	CCSprite* enemy = (CCSprite*)pSender;
	this->removeChild(enemy,true);

	if(iGameOver && bDestoryExplosionTemp)
	{
		CreateGameMenu();
		bDestoryExplosionTemp = false;
	}
}


void PlayScene::MoveFighter(cocos2d::CCPoint newPos)
{
	gcControl.SetFighterPos(newPos);
	spFighter->setPosition(gcControl.GetFighterPos());
}


bool PlayScene::CheckCrush(CCPoint p1,float r1,CCPoint p2,float r2)
{
	//用三角型定理来计算圆心距,然后与半径和对比
	if(sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2))>r1+r2)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void PlayScene::CreateGameMenu()
{
	CCDirector::sharedDirector()->pause();

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//菜单按钮
	char * pngNames[] = {"ReplayNormal.png","ReplaySelected.png","CloseNormal.png","CloseSelected.png"};
	ccaItems = CCArray::create();

	for(int i = 0; i < 2; ++ i)
	{
		ccmiiItem = CCMenuItemImage::create(pngNames[2 * i], pngNames[2 * i + 1], this, menu_selector(MenuScene::menuCallback) );
		ccmiiItem->setPosition(ccp(origin.x + visibleSize.width / 2 - ccmiiItem->getContentSize().width * (i * 1.4 - 0.7), origin.y + visibleSize.height / 2 - ccmiiItem->getContentSize().height));
		ccmiiItem->setTag(i + 3);
		ccaItems->addObject(ccmiiItem);
	}	

	menu = CCMenu::createWithArray(ccaItems);
	menu->setPosition(ccp(0,0));

	this->addChild(menu);
}

void PlayScene::DestoryGameMenu()
{
	CCDirector::sharedDirector()->resume();
	this->removeChild(menu);
}

//菜单回调
void PlayScene::menuCloseCallback(CCObject* pSender)
{
	if(!iGameOver)
	{
		if(isStop)
		{
			DestoryGameMenu();
			isStop = false;
		}
		else
		{
			CreateGameMenu();
			isStop = true;
		}
	}
	/*
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	#else
	//CCDirector::sharedDirector()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
	#endif
	#endif*/
}


////////////////////////////////////////////////////////
//
// TouchesPerformTest1
//
////////////////////////////////////////////////////////

void PlayScene::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool PlayScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	MoveFighter(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()));

	return true;
}

void PlayScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	MoveFighter(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()));
}

void PlayScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	MoveFighter(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()));
}

void PlayScene::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{

}

