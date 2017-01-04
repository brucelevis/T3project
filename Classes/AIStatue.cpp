#include "AIStatue.h"
#include "HudMessageBox.h"
#include "RandomNumber.h"
#include "BuffFactory.h"
#include "ToolFunction.h"
#include "Player.h"
#include "DialogueSystem.h"
#include "ExpHandler.h"

AIStatue::AIStatue()
{
	count = 1;
}

AIStatue::~AIStatue()
{
}

void AIStatue::feedback(Character* character)
{
	if (count)
	{
		characterPtr->speak(L"����");

		character->addBuff(
			ToolFunction::WStr2UTF8(
				L"ViewSizeBuff_Ů��ף��_ATTR_Good_1_20_3"
			)
		);
		character->sufferHPEffect(100);
		character->sufferMPEffect(100);
		count--;
	}
	Character * playerCharacterPtr = Player::getInstance()->getcharacterPtr();
	ExpHandler* expHandler = playerCharacterPtr->getExphandler();
	DialogueSystem::getInstance()->runDialogue("talkStatue", this->characterPtr);
}

void AIStatue::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	Character * playerCharacterPtr = Player::getInstance()->getcharacterPtr();
	ExpHandler* expHandler = playerCharacterPtr->getExphandler();

	if (dialogueName == "talkStatue"
		&& resultNumber == -1)
	{
		handlePray();
	}
	else if (dialogueName == "talkStatue"
		&& resultNumber == -2)
	{
		handleLevelUp();
	}
	else if (dialogueName == "levelUp"
		&& resultNumber == -1)
	{
		//��������
		playerCharacterPtr->setStrength(
			playerCharacterPtr->getOriStrength() + 1
		);
		expHandler->useAttrPoint();
	}
	else if (dialogueName == "levelUp"
		&& resultNumber == -2)
	{
		//��������
		playerCharacterPtr->setAgility(
			playerCharacterPtr->getOriAgility() + 1
		);
		expHandler->useAttrPoint();
	}
	else if (dialogueName == "levelUp"
		&& resultNumber == -3)
	{
		//��������
		playerCharacterPtr->setIntellect(
			playerCharacterPtr->getOriIntellect() + 1
		);
		expHandler->useAttrPoint();
	}
}

void AIStatue::handlePray()
{
	//��
	if (Player::getInstance()->getFaithValue() < 10)
	{
		characterPtr->speak(L"��������");
	}
	else
	{
		Player::getInstance()->reduceFaith(10);

		int roll = RandomNumber::getInstance()->randomInt(1, 100);
		Player::getInstance()->getcharacterPtr()->addExp(200);
		HudMessageBox::getInstance()->addMessage(L"������200�㾭��");
	}
}

void AIStatue::handleLevelUp()
{
	ExpHandler* expHandler = Player::getInstance()->getcharacterPtr()->getExphandler();

	if (expHandler->getCurAttrPoint() > 0)
	{
		DialogueSystem::getInstance()->runDialogue("levelUp", this->characterPtr);
	}
	else
	{
		characterPtr->speak(L"û�����Ե�");
	}
	
}