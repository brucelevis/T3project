#include "AIVergil.h"
#include "BuffHandler.h"
#include "Supply.h"
#include "Armor.h"
#include "Accessory.h"
#include "NoteTextFactory.h"
#include "HudNoteSystem.h"
#include "InventoryInHand.h"
#include "InventoryFactory.h"
#include "InventoryHandler.h"
#include "HudNoteSystem.h"
#include "HudExchangeInventorySystem.h"
#include <algorithm>
#include "Dungeon.h"
#include "ToolFunction.h"
#include "Player.h"
#include "Character.h"
#include "HudMessageBox.h"
#include "DialogueSystem.h"

using std::placeholders::_1;
using std::placeholders::_2;

AIVergil::AIVergil()
{
	//Ĭ��Ϊ���ܸ���
	curState = 0;
}

AIVergil::~AIVergil()
{
}

void AIVergil::update()
{
	characterPtr->idle();
	return;

	if (tidyInventory())
	{
		return;
	}
	if (characterPtr->getHP() < characterPtr->getMaxHP() / 2)
	{
		if (tryUseHPSupply())
		{
			return;
		}
	}
	if (characterPtr->getMP() < characterPtr->getMaxMP() / 2)
	{
		if (tryUseMPSupply())
		{
			return;
		}
	}
	switch (curState)
	{
	case 0:
		stayCloseAI();
		break;
	case 1:
		freeAI();
		break;
	default:
		break;
	}
}

void AIVergil::feedback(Character* character)
{
	DialogueSystem::getInstance()->runDialogue("vergilTalk", this->characterPtr);
}

void AIVergil::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	if (dialogueName == "vergilTalk"
		&& resultNumber == -2)
	{
		curState = 0;
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -3)
	{
		curState = 1;
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -4)
	{
		//����
		Character* playerCharacter = Player::getInstance()->getcharacterPtr();
		if (characterPtr->getMP() > 20)
		{
			changeOrientationTo(playerCharacter);
			characterPtr->runSkill(
				ToolFunction::WStr2UTF8(L"HPRecoveryCast_�����ָ�_20_0_40")
			);
			HudMessageBox::getInstance()->addMessage(L"Vergil�����ͷ���һ�����Ʒ���");
			return;
		}
		else
		{
			DialogueSystem::getInstance()->runDialogue("vergilNoMagic");
		}
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -5)
	{
		//������
		HudExchangeInventorySystem::getInstance()->exchangeInventory(Player::getInstance()->getcharacterPtr(),
			characterPtr);
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -6)
	{
		//Ҫ����
		HudExchangeInventorySystem::getInstance()->exchangeInventory(characterPtr,
			Player::getInstance()->getcharacterPtr());
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -7)
	{
		//��ʾ��ǰ״̬
		showCurState();
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -8)
	{
		//����
		smallTalk();
	}
	else if (dialogueName == "vergilAddBuff"
		&& resultNumber == -1)
	{
		//��buff
		addBuffToPlayer();
	}
}

void AIVergil::lastWords()
{
	DialogueSystem::getInstance()->runDialogue("vergilDie");
	HudMessageBox::getInstance()->addMessage(L"Vergil��ʧ��");
}

void AIVergil::stayCloseAI()
{
	//״̬
	//0Ϊplayer��Χû��enemy������
	//1Ϊplayer��Χ��enemy������player
	static int stateFlag = 0;

	std::vector<Character* > allEnemy = getEnemyAroundPlayer();
	if (allEnemy.size() == 0)
	{
		//��ȫ
		stateFlag = 0;
	}
	else
	{
		stateFlag = 1;
	}

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();
	cocos2d::Point playerCoord = playerCharacter->getMapCoord();

	if (ToolFunction::isNear4(characterPtr->getMapCoord(), playerCoord))
	{
		//playerѪ������vergil��ħ��,��������
		if (playerCharacter->getHP() < playerCharacter->getMaxHP()/2
			&& characterPtr->getMP() > 20)
		{
			changeOrientationTo(playerCharacter);
			characterPtr->runSkill(
				ToolFunction::WStr2UTF8(L"HPRecoveryCast_�����ָ�_20_0_40")
			);
			HudMessageBox::getInstance()->addMessage(L"Vergil�����ͷ���һ�����Ʒ���");
			return;
		}
	}

	if (stateFlag == 0)
	{
		if (ToolFunction::isNear4(characterPtr->getMapCoord(), playerCoord))
		{
			//����Ѿ�������,�������ܵĿɹ���enemy
			Character* targetCharacter = searchTargetBFS(Character::Bad, 1);
			if (targetCharacter)
			{
				changeOrientationTo(targetCharacter);
				characterPtr->attack();
			}
			else
			{
				characterPtr->idle();
			}
		}
		else
		{
			seek(Player::getInstance()->getcharacterPtr());
		}
	}
	else
	{
		auto bound_cmp = bind(&AIVergil::cmpDistance, this, _1, _2);
		sort(allEnemy.begin(), allEnemy.end(), bound_cmp);

		Character* enemy = allEnemy[0];

		if (ToolFunction::isNear4(enemy->getMapCoord(),
			characterPtr->getMapCoord()))
		{
			changeOrientationTo(enemy);
			characterPtr->attack();
			return;
		}
		else
		{
			if (isAccessAble(enemy->getMapCoord()))
			{
				seek(enemy);
			}
			else
			{
				std::vector<Character*> enemyAround = getEnemyAround();
				if (!enemyAround.empty())
				{
					changeOrientationTo(enemyAround[0]);
					characterPtr->attack();
				}
				else
				{
					seek(playerCharacter);
				}
			}

			return;
		}
	}
}

void AIVergil::freeAI()
{
	int viewSize = characterPtr->getViewSize();

	Character* enemyTarget = searchTargetBFS(Character::Bad);

	if (enemyTarget)
	{
		if (getManhattanDistance(Player::getInstance()->getcharacterPtr()) > 5)
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

		if (ToolFunction::isNear4(characterPtr->getMapCoord(), playerCoord))
		{
			characterPtr->idle();
		}
		else
		{
			seek(Player::getInstance()->getcharacterPtr());
		}
	}
}

std::vector<Character* > AIVergil::getEnemyAround()
{
	std::vector<Character*> allEnemy;

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	cocos2d::Point oriCoord = characterPtr->getMapCoord();

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i != 0 && j != 0)
			{
				continue;
			}

			cocos2d::Point tempCoord = oriCoord;
			tempCoord.x += i;
			tempCoord.y += j;

			Character* target = storey->getCharacter(tempCoord);

			if (target
				&& target->getCharacterType() == Character::Bad)
			{
				allEnemy.push_back(target);
			}
		}
	}
	return allEnemy;
}

std::vector<Character* > AIVergil::getEnemyAroundPlayer()
{
	std::vector<Character*> allEnemy;

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	cocos2d::Point oriCoord = Player::getInstance()->getcharacterPtr()->getMapCoord();

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			cocos2d::Point tempCoord = oriCoord;
			tempCoord.x += i;
			tempCoord.y += j;

			Character* target = storey->getCharacter(tempCoord);

			if (target
				&& target->getCharacterType() == Character::Bad)
			{
				allEnemy.push_back(target);
			}
		}
	}
	return allEnemy;
}

bool AIVergil::cmpDistance(Character* a, Character* b)
{
	return ToolFunction::getManhattanDistance(a->getMapCoord(), characterPtr->getMapCoord())
		< ToolFunction::getManhattanDistance(b->getMapCoord(), characterPtr->getMapCoord());
}
bool AIVergil::tidyInventory()
{
	if (chooseBetterLefthand())
	{
		return true;
	}
	//	if (chooseBetterRighthand())
	//	{
	//		return true;
	//	}
	if (chooseBetterArmor())
	{
		return true;
	}
	if (chooseBetterAccessory())
	{
		return true;
	}
	return false;
}

bool AIVergil::tryUseHPSupply()
{
	bool flag = false;
	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	std::map<std::string, int> allInventory = inventoryHandler->getAllInventory();
	std::map<std::string, int>::iterator iter = allInventory.begin();

	while (iter != allInventory.end())
	{
		if (InventoryFactory::getInstance()->queryInventoryType(iter->first) == Inventory::Supply)
		{
			Supply* supply = static_cast<Supply*>(InventoryFactory::getInstance()->getInventory(iter->first));
			if (supply->getSupplyType() == Supply::HPSupply)
			{
				characterPtr->removeInventory(iter->first);
				supply->use(characterPtr);
				HudMessageBox::getInstance()->addMessage(L"Vergil�����Żظ����Լ���HP");
				flag = true;
			}
			delete supply;

			if (flag)
			{
				break;
			}
		}
		iter++;
	}
	return flag;
}

bool AIVergil::tryUseMPSupply()
{
	bool flag = false;
	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	std::map<std::string, int> allInventory = inventoryHandler->getAllInventory();
	std::map<std::string, int>::iterator iter = allInventory.begin();

	while (iter != allInventory.end())
	{
		if (InventoryFactory::getInstance()->queryInventoryType(iter->first) == Inventory::Supply)
		{
			Supply* supply = static_cast<Supply*>(InventoryFactory::getInstance()->getInventory(iter->first));
			if (supply->getSupplyType() == Supply::MPSupply)
			{
				characterPtr->removeInventory(iter->first);
				supply->use(characterPtr);
				HudMessageBox::getInstance()->addMessage(L"Vergil�����Żظ����Լ���MP");
				flag = true;
			}
			delete supply;
			if (flag)
			{
				break;
			}
		}
		iter++;
	}
	return flag;
}

bool AIVergil::chooseBetterLefthand()
{
	bool flag = false;
	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	std::map<std::string, int> allInventory = inventoryHandler->getAllInventory();

	std::map<std::string, int>::iterator iter = allInventory.begin();

	int curLeftHandLevel = characterPtr->getLeftHand() ? characterPtr->getLeftHand()->getLevel() : 0;
	std::string curLeftHandName = characterPtr->getLeftHand() ? characterPtr->getLeftHand()->getName() : "NULL";

	int maxLevel = curLeftHandLevel;
	std::string maxInventory = curLeftHandName;

	while (iter != allInventory.end())
	{
		Inventory::Type invType = InventoryFactory::getInstance()->queryInventoryType(iter->first);
		int invLevel = InventoryFactory::getInstance()->queryInventoryLevel(iter->first);

		if (invType == Inventory::OneHandWeapon && invLevel > maxLevel)
		{
			maxLevel = invLevel;
			maxInventory = iter->first;
		}

		iter++;
	}
	if (maxInventory != curLeftHandName)
	{
		characterPtr->removeInventory(maxInventory);
		Inventory* inventory = InventoryFactory::getInstance()->getInventory(maxInventory);
		characterPtr->equipLeftHand(inventory);
		HudMessageBox::getInstance()->addMessage(L"Vergil����һ�����õ�����");
		return true;
	}
	return false;
}

bool AIVergil::chooseBetterRighthand()
{
	bool flag = false;
	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	std::map<std::string, int> allInventory = inventoryHandler->getAllInventory();

	std::map<std::string, int>::iterator iter = allInventory.begin();

	int curRightHandLevel = characterPtr->getRightHand() ? characterPtr->getRightHand()->getLevel() : 0;
	std::string curRightHandName = characterPtr->getRightHand() ? characterPtr->getRightHand()->getName() : "NULL";

	int maxLevel = curRightHandLevel;
	std::string maxInventory = curRightHandName;

	while (iter != allInventory.end())
	{
		Inventory::Type invType = InventoryFactory::getInstance()->queryInventoryType(iter->first);
		int invLevel = InventoryFactory::getInstance()->queryInventoryLevel(iter->first);

		if (invType == Inventory::OneHandWeapon && invLevel > maxLevel)
		{
			maxLevel = invLevel;
			maxInventory = iter->first;
		}

		iter++;
	}
	if (maxInventory != curRightHandName)
	{
		characterPtr->removeInventory(maxInventory);
		Inventory* inventory = InventoryFactory::getInstance()->getInventory(maxInventory);
		characterPtr->equipRightHand(inventory);
		HudMessageBox::getInstance()->addMessage(L"Vergil������һ����������");
		return true;
	}
	return false;
}

bool AIVergil::chooseBetterArmor()
{
	bool flag = false;
	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	std::map<std::string, int> allInventory = inventoryHandler->getAllInventory();

	std::map<std::string, int>::iterator iter = allInventory.begin();

	int curArmorLevel = characterPtr->getArmor() ? characterPtr->getArmor()->getLevel() : 0;
	std::string curArmorName = characterPtr->getArmor() ? characterPtr->getArmor()->getName() : "NULL";

	int maxLevel = curArmorLevel;
	std::string maxInventory = curArmorName;

	while (iter != allInventory.end())
	{
		Inventory::Type invType = InventoryFactory::getInstance()->queryInventoryType(iter->first);
		int invLevel = InventoryFactory::getInstance()->queryInventoryLevel(iter->first);

		if (invType == Inventory::Armor && invLevel > maxLevel)
		{
			maxLevel = invLevel;
			maxInventory = iter->first;
		}

		iter++;
	}
	if (maxInventory != curArmorName)
	{
		characterPtr->removeInventory(maxInventory);
		Inventory* inventory = InventoryFactory::getInstance()->getInventory(maxInventory);
		characterPtr->equipArmor(inventory);
		HudMessageBox::getInstance()->addMessage(L"Vergil������һ������");
		return true;
	}
	return false;
}

bool AIVergil::chooseBetterAccessory()
{
	bool flag = false;
	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	std::map<std::string, int> allInventory = inventoryHandler->getAllInventory();

	std::map<std::string, int>::iterator iter = allInventory.begin();

	int curAccessoryLevel = characterPtr->getAccessory() ? characterPtr->getAccessory()->getLevel() : 0;
	std::string curAccessoryName = characterPtr->getAccessory() ? characterPtr->getAccessory()->getName() : "NULL";

	int maxLevel = curAccessoryLevel;
	std::string maxInventory = curAccessoryName;

	while (iter != allInventory.end())
	{
		Inventory::Type invType = InventoryFactory::getInstance()->queryInventoryType(iter->first);
		int invLevel = InventoryFactory::getInstance()->queryInventoryLevel(iter->first);

		if (invType == Inventory::Accessory && invLevel > maxLevel)
		{
			maxLevel = invLevel;
			maxInventory = iter->first;
		}

		iter++;
	}
	if (maxInventory != curAccessoryName)
	{
		characterPtr->removeInventory(maxInventory);
		Inventory* inventory = InventoryFactory::getInstance()->getInventory(maxInventory);
		characterPtr->equipAccessory(inventory);
		HudMessageBox::getInstance()->addMessage(L"Vergil������һ������");
		return true;
	}
	return false;
}

void AIVergil::showCurState()
{
	NoteText note;

	std::string  characterLevel = ToolFunction::int2string(characterPtr->getLevel());
	std::string characterHP = ToolFunction::int2string(characterPtr->getHP()) + "/" +
		ToolFunction::int2string(characterPtr->getMaxHP());
	std::string characterMP = ToolFunction::int2string(characterPtr->getMP()) + "/" +
		ToolFunction::int2string(characterPtr->getMaxMP());

	std::string characterInt = ToolFunction::int2string(characterPtr->getIntellect());
	std::string characterStr = ToolFunction::int2string(characterPtr->getStrength());
	std::string characterAgi = ToolFunction::int2string(characterPtr->getAgility());

	std::string leftHandName = characterPtr->getLeftHand() ? characterPtr->getLeftHand()->getCname() : "NULL";
	std::string rightHandName = characterPtr->getRightHand() ? characterPtr->getRightHand()->getCname() : "NULL";;
	std::string armorName = characterPtr->getArmor() ? characterPtr->getArmor()->getCname() : "NULL";;
	std::string accessoryName = characterPtr->getAccessory() ? characterPtr->getAccessory()->getCname() : "NULL";

	note.addPage(
		"Vergil\n" +
		ToolFunction::WStr2UTF8(L"��ǰ�ȼ�:") + characterLevel + "\n" +
		ToolFunction::WStr2UTF8(L"HP:") + characterHP + "\n" +
		ToolFunction::WStr2UTF8(L"MP:") + characterMP + "\n" +
		ToolFunction::WStr2UTF8(L"����:") + characterStr + "\n" +
		ToolFunction::WStr2UTF8(L"����:") + characterAgi + "\n" +
		ToolFunction::WStr2UTF8(L"����:") + characterInt + "\n" +
		ToolFunction::WStr2UTF8(L"����:") + leftHandName + "\n" +
		ToolFunction::WStr2UTF8(L"����:") + rightHandName + "\n" +
		ToolFunction::WStr2UTF8(L"����:") + armorName + "\n" +
		ToolFunction::WStr2UTF8(L"����:") + accessoryName + "\n"
	);

	HudNoteSystem::getInstance()->openNote(note);
}

void AIVergil::smallTalk()
{
	Buff::BuffHandler* targetBuffHandler = Player::getInstance()->getcharacterPtr()->getBuffHandler();

	if ((!getEnemyAround().empty() || !getEnemyAroundPlayer().empty())
		&& characterPtr->getMP() >= 20
		&& !targetBuffHandler->exist(
			ToolFunction::WStr2UTF8(L"ChantBuff_Vergil������ף��_OnRoundStart_Good_10_20_100"))
		)
	{
		DialogueSystem::getInstance()->runDialogue("vergilAddBuff", characterPtr);
	}
	else
	{
		DialogueSystem::getInstance()->runDialogue("vergilSmallTalk", characterPtr);
	}
}


void AIVergil::addBuffToPlayer()
{
	changeOrientationTo(Player::getInstance()->getcharacterPtr());
	characterPtr->runSkill(
		ToolFunction::WStr2UTF8(L"BuffCast_����ף��_20_0_ChantBuff_Vergil������ף��_OnRoundStart_Good_10_20_100")
	);
	HudMessageBox::getInstance()->addMessage(L"VergilΪ�㸽��������ף��");
}
