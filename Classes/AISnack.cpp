#include "AISnack.h"
#include "HudMessageBox.h"
#include "RandomNumber.h"
#include "ToolFunction.h"
#include "BuffHandler.h"

AISnack::AISnack()
{
}

AISnack::~AISnack()
{
}

void AISnack::update()
{
	if (!characterPtr)
	{
		return;
	}
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
			Buff::BuffHandler* targetBuffHandler = targetCharacter->getBuffHandler();
			if (!targetBuffHandler->exist(
				ToolFunction::WStr2UTF8(L"HPBuff_��Һ_OnRoundStart_Bad_10_10_-4")))
			{
				//������
				if (characterPtr->getChantCount() >= 1)
				{
					characterPtr->runSkill(
						ToolFunction::WStr2UTF8(L"BuffCast_��Һ_0_0_HPBuff_��Һ_OnRoundStart_Bad_10_10_-4")
					);
					HudMessageBox::getInstance()->addMessage(
						targetCharacter->getName()+
						ToolFunction::WStr2UTF8(L"�ж���")
					);
				}
				else if (RandomNumber::getInstance()->randomBool(0.5))
				{
					if (characterPtr->getChantCount() == 0)
					{
						characterPtr->chant();
					}
					else
					{
						characterPtr->attack();
					}
				}
				else
				{
					characterPtr->attack();
				}
			}
			else
			{
				characterPtr->attack();
			}
		}
	}
	else
	{
		characterPtr->idle();
	}
}

void AISnack::feedback(Character* character)
{
}