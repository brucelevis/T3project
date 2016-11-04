#include "RoundSystem.h"
#include "Character.h"
#include "Dungeon.h"
#include "Marco.h"
#include "KeyController.h"
#include "Player.h"

using namespace Field;

RoundSystem::RoundSystem()
{
}

RoundSystem::~RoundSystem()
{
}

void RoundSystem::init()
{
	roundCount = 0;
}

void RoundSystem::loadStorey()
{
	int index = 0;
	Storey* storey = Dungeon::getInstance()->getStorey();
	std::list<Character* >& allStoreyCharacter = storey->getAllCharacter();
	for (std::list<Character*>::iterator iter = allStoreyCharacter.begin();
		iter != allStoreyCharacter.end();
		iter++)
	{
		allCharacter.push_back(*iter);
		//��ʼ����������character��ʱ�򣬽���һ���ж���Ϊplayer
		if (isPlayer(*iter))
		{
			curIndex = index;
		}
		index++;
	}
}

int RoundSystem::getRoundCount()
{
	return roundCount;
}

void RoundSystem::nextRound()
{
	allCharacter[curIndex]->endRound();

	do
	{
		nextIndex();
	} while (allCharacter[curIndex]->isDead());

	roundCount++;
	allCharacter[curIndex]->startRound();
	round(curIndex);
}

void RoundSystem::nextIndex()
{
	curIndex++;
	if (curIndex >= allCharacter.size())
	{
		curIndex = 0;
	}
}

bool RoundSystem::isPlayer(Character* character)
{
	return character == Player::getInstance()->getcharacterPtr();
}

void RoundSystem::round(int index)
{
	std::cout << roundCount << std::endl;

	Character* curCharacter = allCharacter[index];
	//����character��Ϣ������buff
	curCharacter->update();

	if (isPlayer(allCharacter[index]))
	{
		//��Ϊplayer character�����½����������������ݹ�ջ
		KeyController::getInstance()->setBlock(false);
		playerAction();
	}
	else
	{
		KeyController::getInstance()->setBlock(true);
		//������һ��character��ݹ����nextRound��ֱ��Ϊplayer character
		NPCAction(curCharacter);
	}

	//curCharacter->update();
}

void RoundSystem::NPCAction(Character* character)
{
	if (character->isActionAble())
	{
		character->action();
	}
	else
	{
		nextRound();
	}
}

void RoundSystem::playerAction()
{
	if (!Player::getInstance()->getcharacterPtr()->isActionAble())
	{
		KeyController::getInstance()->setBlock(true);
		nextRound();
	}
}