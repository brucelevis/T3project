#include "AISummonWizard.h"
#include "RandomNumber.h"
#include "ToolFunction.h"

AISummonWizard::AISummonWizard()
{
}

AISummonWizard::~AISummonWizard()
{
}

void AISummonWizard::update()
{
	if (!characterPtr)
	{
		return;
	}

	int viewSize = characterPtr->getViewSize();
	Character* targetCharacter = searchTargetBFS(Character::Good);
	if (targetCharacter)
	{
		if (characterPtr->getChantCount() >= 20
			&& characterPtr->getMP() >= 60)
		{
			//�Ѿ�������ħ������
			characterPtr->runSkill(
				ToolFunction::WStr2UTF8(
					L"Summon_�ٻ�slime_60_10_slime"
				)
			);
		}
		else if (RandomNumber::getInstance()->randomBool(0.4)
			&& characterPtr->getMP() >= 60)
		{
			//�����ħ��
			characterPtr->chant();
		}
		else
		{
			if (!flee(targetCharacter))
			{
				this->changeOrientationTo(targetCharacter);
				if (isInAttackArea(targetCharacter))
				{
					characterPtr->attack();
				}
				else
				{
					characterPtr->idle();
				}
			}
		}
	}
	else
	{
		characterPtr->idle();
	}
}

void AISummonWizard::feedback(Character* character)
{
}