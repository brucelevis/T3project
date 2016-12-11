#include "AIPortal.h"
#include "Player.h"
#include "ToolFunction.h"
#include "GameController.h"



AIPortal::AIPortal()
{
}


AIPortal::~AIPortal()
{
}

void AIPortal::update()
{
	if (isPlayerNear())
	{
		characterPtr->speak(L"��'E'������һ��");
		characterPtr->idle();
	}
	else
	{
		characterPtr->idle();
	}
}

void AIPortal::feedback(Character* character)
{
	GameController::getInstance()->startMission(1);
}

bool AIPortal::isPlayerNear()
{
	cocos2d::Point oriCoord = characterPtr->getMapCoord();
	cocos2d::Point playerCoord = Player::getInstance()->getcharacterPtr()->getMapCoord();

	if (ToolFunction::isNear8(oriCoord,playerCoord))
	{
		return true;
	}
	return false;
}
