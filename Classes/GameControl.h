#ifndef  _GAME_CONTROL_H_
#define  _GAME_CONTROL_H_

class GameControl
{
private:

	cocos2d::CCPoint posFighterLocation;

public:

	GameControl();
	~GameControl();

	void SetFighterPos(cocos2d::CCPoint );
	cocos2d::CCPoint GetFighterPos();
};

#endif