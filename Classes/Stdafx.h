#ifndef  _STD_AFX_H_
#define  _STD_AFX_H_

#include "cocos2d.h"

#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameControl.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include "RecordScene.h"

#define PATH_PNG_PLAY_BACKGROUND "farback.png"

#define	PATH_PNG_EXPLOSION_1	"Explosion_1.png"
#define	PATH_PNG_EXPLOSION_2	"Explosion_2.png"
#define	PATH_PNG_EXPLOSION_3	"Explosion_3.png"
#define	PATH_PNG_EXPLOSION_4	"Explosion_4.png"

#define	PATH_PNG_EXPLOSION1		"Explosion1.png"
#define	PATH_PNG_EXPLOSION2		"Explosion2.png"
#define	PATH_PNG_EXPLOSION3		"Explosion3.png"
#define	PATH_PNG_EXPLOSION4		"Explosion4.png"

#define userDefault CCUserDefault::sharedUserDefault()

enum 
{
	kTagSBNP_PLAY_BACKGROUN = 1
};

//! delta time type
//! if you want more resolution redefine it as a double
//typedef float ccTime;
typedef double ccTime;

#endif