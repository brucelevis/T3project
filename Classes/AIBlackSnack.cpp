#include "AIBlackSnack.h"
#include "HudMessageBox.h"
#include "ToolFunction.h"
#include "RandomNumber.h"
#include "BuffHandler.h"

AIBlackSnack::AIBlackSnack()
{
}

AIBlackSnack::~AIBlackSnack()
{
}

void AIBlackSnack::update()
{
	if (!characterPtr)
	{
		return;
	}

	//�����ƻ�����������
	if (tryDestroyShrine())
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
				ToolFunction::WStr2UTF8(L"ViewSizeBuff_��ä_ATTR_Bad_1_10_-3")))
			{
				//�����ǰĿ��û����ä
				//������
				if (characterPtr->getChantCount() >= 1)
				{
					characterPtr->runSkill(
						ToolFunction::WStr2UTF8(L"BuffCast_��ä_0_0_ViewSizeBuff_��ä_ATTR_Bad_1_10_-3")
					);
					HudMessageBox::getInstance()->addMessage(
						targetCharacter->getName() +
						ToolFunction::WStr2UTF8(L"������äbuff")
					);
				}
				else if (RandomNumber::getInstance()->randomBool(0.9))
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

void AIBlackSnack::feedback(Character* character)
{
}

bool AIBlackSnack::tryDestroyShrine()
{
	Character* targetCharacter = searchTargetBFS(Character::Neutral);

	//up�������
	if (targetCharacter
		&& targetCharacter->getName() == "shrine"
		&& targetCharacter->getOrientation() == Character::Orientation::UP)
	{
		if (!isInAttackArea(targetCharacter))
		{
			seek(targetCharacter);
		}
		else
		{
			characterPtr->attack();
		}
		return true;
	}
	return false;
}