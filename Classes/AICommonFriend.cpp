#include "AICommonFriend.h"
#include "Player.h"

AICommonFriend::AICommonFriend()
{
}

AICommonFriend::~AICommonFriend()
{
}

void AICommonFriend::update()
{
	int viewSize = characterPtr->getViewSize();

	Character* enemyTarget = searchTargetBFS(Character::Bad);

	if (enemyTarget)
	{
		//�����player�����Զ���͸���player
		if (getManhattanDistance(Player::getInstance()->getcharacterPtr()) > 6)
		{
			seek(Player::getInstance()->getcharacterPtr());
		}
		else
		{
			if (isInAttackArea(enemyTarget))
			{
				characterPtr->attack();
			}
			else
			{
				seek(enemyTarget);
			}
		}
	}
	else
	{
		cocos2d::Point playerCoord = Player::getInstance()->getcharacterPtr()->getMapCoord();
		if (isNear(playerCoord))
		{
			characterPtr->idle();
		}
		else
		{
			seek(Player::getInstance()->getcharacterPtr());
		}
	}
}
