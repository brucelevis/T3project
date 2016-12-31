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
		if (characterPtr->getChantCount() >= 10
			&& characterPtr->getMP() >= 20)
		{
			//�Ѿ�������ħ������
			characterPtr->runSkill(
				ToolFunction::WStr2UTF8(
					L"Summon_�ٻ�slime_20_10_slime"
				)
			);
		}
		else if (RandomNumber::getInstance()->randomBool(0.8)
			&& characterPtr->getMP() >= 20)
		{
			//�����ħ��
			characterPtr->chant();
		}
		else
		{
			this->changeOrientationTo(targetCharacter);	
			{
				if (isInAttackArea(targetCharacter))
				{
					characterPtr->attack();
				}
				else
				{
					flee(targetCharacter);
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
