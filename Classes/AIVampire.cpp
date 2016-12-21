#include "AIVampire.h"
#include "ToolFunction.h"
#include "RandomNumber.h"

AIVampire::AIVampire()
{
	deadLine = 50;
}

AIVampire::~AIVampire()
{
}

void AIVampire::update()
{
	if (!characterPtr)
	{
		return;
	}

	if (isDangerous()
		&& characterPtr->getMP() >= 20
		&& characterPtr->getChantCount() == 0)
	{
		//��Σ����ħ��������δ����
		characterPtr->chant();
	}
	else if (isDangerous()
		&& characterPtr->getMP() >= 20
		&& characterPtr->getChantCount() >= 1)
	{
		//��Σ����ħ���������Ѿ�����
		characterPtr->runSkill(
			ToolFunction::WStr2UTF8(L"HPRecoverySelf_�����ָ�_20_1_30")
		);
	}
	else
	{
		int viewSize = characterPtr->getViewSize();
		Character* targetCharacter = searchTargetBFS(Character::Good);
		if (targetCharacter)
		{
			if (!isInAttackArea(targetCharacter))
			{
				seek(targetCharacter);
			}
			else
			{
				characterPtr->attack();
			}
		}
		else
		{
			characterPtr->idle();
		}
	}
}

void AIVampire::feedback(Character* character)
{
}

bool AIVampire::isDangerous()
{
	double HP = characterPtr->getHP();

	double maxHP = characterPtr->getMaxHP();
	if (HP * 100 / maxHP < deadLine)
	{
		return true;
	}
	return false;
}