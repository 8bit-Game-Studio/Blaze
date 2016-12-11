#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "Stdafx.h"

USING_NS_CC;

class MenuScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(MenuScene);

private:
	//CCMenu *m_pItemMenu;

	CCArray* ccaItems;
};


#endif