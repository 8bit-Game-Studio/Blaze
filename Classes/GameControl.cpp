#include "Stdafx.h"

GameControl::GameControl()
{
	posFighterLocation.x = 0;
	posFighterLocation.y = 0;
}

GameControl::~GameControl()
{

}

void GameControl::SetFighterPos(cocos2d::CCPoint newPos)
{
	posFighterLocation = newPos;
}

cocos2d::CCPoint GameControl::GetFighterPos()
{
	return posFighterLocation;
}