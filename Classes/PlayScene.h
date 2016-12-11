#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "Stdafx.h"

USING_NS_CC;

class PlayScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
	// make starry background move callback
	void backgroundClock(float dt);
	void bulletClock(float dt);
	void enemyClock(float dt);
	void playerClock(float tmd);

	void CreateGameMenu();
	void CreateExplosion(CCPoint newPos,bool isEnemy = true);
	
	void DestoryGameMenu();
	void DestoryBullet(CCNode* pSender);
	void DestoryEnemy(CCNode* pSender);
	void DestoryExplosion(CCNode* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(PlayScene);

	// TouchesPerformTest1
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	void ccTouchMoved(CCTouch* touch, CCEvent* event);
	void ccTouchEnded(CCTouch* touch, CCEvent* event);
	void ccTouchCancelled(CCTouch* touch, CCEvent* event);

	//Common Function
	void MoveFighter(CCPoint);
	bool CheckCrush(CCPoint p1,float r1,CCPoint p2,float r2);

public:
	int iScore;

private:
	bool iGameOver;
	bool bDestoryExplosionTemp;
	bool isStop;

	GameControl gcControl;

	CCSprite* spFighter;
	CCArray* arrEnemy;
	CCArray* arrBullet;

	CCLabelTTF* pLabel;

	CCArray* ccaItems;
	CCMenu *menu;

	CCMenuItemImage* ccmiiItem;
};

#endif