#include "Player.h"
#include "SkillHandler.h"
#include "ExpHandler.h"
#include "HudMessageBox.h"
#include "ToolFunction.h"
#include"CharacterFactory.h"
#include"Dungeon.h"
#include"FieldEnum.h"
#include"InventoryFactory.h"
#include"ToolFunction.h"
#include "InventoryInHand.h"
#include "Accessory.h"
#include "Armor.h"
#include "RoundSystem.h"
#include "MainLayer.h"
#include "BuffFactory.h"
#include "SkillFactory.h"
#include "MyCamera.h"

USING_NS_CC;
using namespace Field;

Player::Player()
{
}

Player::~Player()
{
}

void Player::init()
{
	faithValue = 0;
	historySize = 10;
	characterPtr = CharacterFactory::getInstance()->getCharacter("player");
	characterPtr->setAI("AIPlayer");

	configPlayer();
}

void Player::initMission()
{
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	cocos2d::Point tempCoord = storey->getUpCoord();
	if (storey->getCharacter(tempCoord))
	{
		tempCoord = ToolFunction::findValidPlace(
			Field::Dungeon::getInstance()->getStorey(),
			tempCoord
		);
	}

	characterPtr->setMapCoord(tempCoord);

	storey->addCharacter(tempCoord, characterPtr);
}

void Player::restart()
{
	delete characterPtr;
	characterPtr = CharacterFactory::getInstance()->getCharacter("player");
	characterPtr->setAI("AIPlayer");

	configPlayer();
}

void Player::configPlayer()
{
	//	characterPtr->addSkill(L"FireBall_���ٻ���_20_20_20_5");
	//	characterPtr->addSkill(L"HPRecoverySelf_�����ָ�_20_20_20");
	//	characterPtr->addSkill(L"MPRecoverySelf_ħ���ָ�_20_20_100");
	//	characterPtr->addSkill(L"HPRecoveryCast_����_20_20_100");
	//	characterPtr->addSkill(L"MPRecoveryCast_ħ������_20_20_100");
	//	characterPtr->addSkill(L"ChantSelf_����ʩ��_20_0_100");
	//	characterPtr->addSkill(L"BuffSelf_����buff_20_20_EvadeBuff_����buff_ATTR_Good_4_100_100");
	//	characterPtr->addSkill(L"BuffCast_����buffף��_20_20_EvadeBuff_����buff_ATTR_Good_4_100_100");
	//	characterPtr->addSkill(L"Summon_�ٻ�slime_20_20_slime");
	//	characterPtr->addSkill(L"BlinkSelf_��˸_20_10_3");
	//	characterPtr->addSkill(L"Repel_����_20_10_3_10");
	//	characterPtr->addSkill(L"Thunder_����_20_10_-30");
	//	characterPtr->addSkill(L"ExpAdd_��������_0_0_100");
	//	characterPtr->addSkill(L"LearnSkill_ѧϰ������_0_0_FireBall_������_5_5_-20_5");
	//	characterPtr->addSkill(L"BuffSelf_��Һ_0_0_HPBuff_��Һ_OnRoundStart_Bad_10_10_-3");
	//	characterPtr->addSkill(L"RandomDirectDamage_����һָ_10_10_-30_5_2");

	setName(ToolFunction::WStr2UTF8(L"��"));

	controlMode = NormalMode;

	characterPtr->setHP(100);
	characterPtr->setMaxHP(100);
	characterPtr->setMP(100);
	characterPtr->setMaxMP(100);

	characterPtr->setStrength(10);
	characterPtr->setAgility(10);
	characterPtr->setIntellect(10);
	characterPtr->setLuck(10);
	characterPtr->setViewSize(1);
	characterPtr->setCharacterType(Character::Good);
	characterPtr->setPlayType(Character::Player);

	//testInventory......

	Inventory* woodSword1 = InventoryFactory::getInstance()->getInventory("sword000");
	characterPtr->initLeftHand(woodSword1);

	Inventory* woodSword2 = InventoryFactory::getInstance()->getInventory("sword000");
	characterPtr->initRightHand(woodSword2);

	Inventory* armor = InventoryFactory::getInstance()->getInventory("armor000");
	characterPtr->initArmor(armor);

	characterPtr->addInventory("note000");
//	characterPtr->addInventory("skillBook000");
//	characterPtr->addInventory("skillBook001");
//	characterPtr->addInventory("skillBook002");
//	characterPtr->addInventory("scroll000");
//	characterPtr->addInventory("scroll001");
//	characterPtr->addInventory("scroll002");

//����װ��
//	characterPtr->addInventory("armor009");
//	characterPtr->addInventory("sword022");
//	characterPtr->addInventory("sword027");

//	characterPtr->addInventory("armor012");
//	characterPtr->addInventory("sword022");
//	characterPtr->addInventory("sword027");

//	for (int i=0;i<5;i++)
//	{
//		characterPtr->addInventory("supply009");
//	}



}

void Player::autoNextStep()
{
	cocos2d::Point startPoint = characterPtr->getMapCoord();
	cocos2d::Point endPoint = Dungeon::getInstance()->getStorey()->getDownCoord();
	cocos2d::Point nextStep = ToolFunction::nextStep(startPoint, endPoint);

	if (nextStep.x == startPoint.x + 1
		&& nextStep.y == startPoint.y)
	{
		handleKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
	}
	else if (nextStep.x == startPoint.x - 1
		&& nextStep.y == startPoint.y)
	{
		handleKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW);
	}
	else if (nextStep.x == startPoint.x
		&& nextStep.y == startPoint.y - 1)
	{
		handleKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW);
	}
	else if (nextStep.x == startPoint.x
		&& nextStep.y == startPoint.y + 1)
	{
		handleKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW);
	}
}

void Player::addFaith(int value)
{
	HudMessageBox::getInstance()->addMessage(
		L"������" +
		ToolFunction::string2wstring(ToolFunction::int2string(value)) +
		L"����ֵ"
	);
	faithValue += value;
}

void Player::reduceFaith(int value)
{
	HudMessageBox::getInstance()->addMessage(
		L"��ʧȥ��" +
		ToolFunction::string2wstring(ToolFunction::int2string(value)) +
		L"����ֵ"
	);
	faithValue -= value;
}

bool Player::isInViewSize(cocos2d::Point coord)
{
	cocos2d::Point playerCoord = characterPtr->getMapCoord();
	int dx = abs(coord.x - playerCoord.x);
	int dy = abs(coord.y - playerCoord.y);
	int d = dx + dy;
	return d < characterPtr->getViewSize();
}

bool Player::isMoveAble(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (!characterPtr->isMoveAble())
	{
		return false;
	}
	if (characterPtr->getWeight() < characterPtr->getSumWeight())
	{
		showCannotMoveReason();
		return false;
	}

	cocos2d::Point position = characterPtr->getMapCoord();
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		position.y -= 1;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		position.y += 1;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		position.x -= 1;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		position.x += 1;
		break;
	default:
		return false;
	}

	Storey* storey = Dungeon::getInstance()->getStorey();
	//Dungeon::getInstance()->getStorey()->isMoveAble(position);

	if (storey->isMoveAble(position))
	{
		return true;
	}
	else if (storey->isPartner(position))
	{
		return true;
	}
	return false;
}

void Player::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (controlMode)
	{
	case NormalMode:
		playerAction(keyCode);
		break;
	case HaltMode:
		playerSetOrientation(keyCode);
		hideAtkArea();
		showAtkArea();
		break;
	}
}

void Player::handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (controlMode)
	{
	case HaltMode:
		if (keyCode == EventKeyboard::KeyCode::KEY_CTRL)
		{
			controlMode = NormalMode;
			hideAtkArea();
		}
		break;
	}
}

void Player::playerAttack()
{
	characterPtr->attack();
}

void Player::playerRunSkill(cocos2d::EventKeyboard::KeyCode keyCode)
{
	int curIndex;

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_0:
		curIndex = 9;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_1:
		curIndex = 0;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_2:
		curIndex = 1;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_3:
		curIndex = 2;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_4:
		curIndex = 3;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_5:
		curIndex = 4;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_6:
		curIndex = 5;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_7:
		curIndex = 6;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_8:
		curIndex = 7;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_9:
		curIndex = 8;
		break;
	default:
		curIndex = -1;
		break;
	}

	if (curIndex == -1)
	{
		return;
	}

	Skill::SkillHandler* skillHandler = characterPtr->getSkillHandler();
	std::string skillID = skillHandler->getSkillID(curIndex);
	if (skillID != "")
	{
		characterPtr->runSkill(skillID);
	}
}

void Player::playerMove(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (!isMoveAble(keyCode))
	{
		playerSetOrientation(keyCode);
		return;
	}
	recodePath(characterPtr->getMapCoord());
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		characterPtr->moveUp();
		MyCamera::getInstance()->moveCameraBy(cocos2d::Vec2(0, 32), 0.2);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		characterPtr->moveDown();
		MyCamera::getInstance()->moveCameraBy(cocos2d::Vec2(0, -32), 0.2);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		characterPtr->moveLeft();
		MyCamera::getInstance()->moveCameraBy(cocos2d::Vec2(-32, 0), 0.2);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		characterPtr->moveRight();
		MyCamera::getInstance()->moveCameraBy(cocos2d::Vec2(32, 0), 0.2);
		break;
	}
}

void Player::playerSetOrientation(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		characterPtr->setOrientationUp();
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		characterPtr->setOrientationDown();
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		characterPtr->setOrientationLeft();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		characterPtr->setOrientationRight();
		break;
	}
}

void Player::playerInteraction(cocos2d::EventKeyboard::KeyCode keyCode)
{
	characterPtr->interaction();
}

std::string Player::getName()
{
	return characterPtr->getName();
}

void Player::setName(const std::string& name)
{
	CCAssert(characterPtr, "characterPtr is null");
	characterPtr->setName(name);
}

std::vector<cocos2d::Point>& Player::getpathHistory()
{
	return pathHistory;
}

void Player::playerAction(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		playerAttack();
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_E)
	{
		playerInteraction(keyCode);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_CTRL)
	{
		controlMode = HaltMode;
		showAtkArea();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_C)
	{
		playerChant();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_T)
	{
		playerIdle();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW
		|| keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW
		|| keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW
		|| keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		playerMove(keyCode);
	}
	else
	{
		playerRunSkill(keyCode);
	}
}

void Player::playerChant()
{
	characterPtr->chant();
}

void Player::playerIdle()
{
	characterPtr->idle();
//	HudMessageBox::getInstance()->addMessage(
//		ToolFunction::int2string(
//			ToolFunction::getCurTime()
//		)
//	);
}

void Player::showCannotMoveReason()
{
	if (characterPtr->getWeight() < characterPtr->getSumWeight())
	{
		HudMessageBox::getInstance()->addMessage(
			L"���ز�����"
		);
	}
}

void Player::showAtkArea()
{
	std::vector<cocos2d::Point> atkCoords = characterPtr->getAtkArea();
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	for each (cocos2d::Point atkCoord in atkCoords)
	{
		cocos2d::Point atkPosition = storey->getTilePosition(atkCoord);
		cocos2d::Sprite* atkSprite = cocos2d::Sprite::create("sys/targetArea.png");
		targetSprites.push_back(atkSprite);
		atkSprite->setPosition(atkPosition);
		MainLayer::getInstance()->addChild(atkSprite, 20);
	}
}

void Player::hideAtkArea()
{
	for each (cocos2d::Sprite* targetSprite in targetSprites)
	{
		targetSprite->removeFromParent();
	}
	targetSprites.clear();
}

void Player::recodePath(cocos2d::Point coord)
{
	pathHistory.push_back(coord);

	if (pathHistory.size() > historySize)
	{
		pathHistory.erase(pathHistory.begin());
	}
}