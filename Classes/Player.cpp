#include "Player.h"
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
	characterPtr = CharacterFactory::getInstance()->getCharacter("Actor0");

	characterPtr->addSkill(L"fireBall_���ٻ���_20_20_20_5");
	characterPtr->addSkill(L"HPRecoverySelf_�����ָ�_20_20_20");
	characterPtr->addSkill(L"MPRecoverySelf_ħ���ָ�_20_20_100");
	characterPtr->addSkill(L"HPRecoveryCast_����_20_20_100");
	characterPtr->addSkill(L"MPRecoveryCast_ħ������_20_20_100");
	characterPtr->addSkill(L"ChantSelf_����ʩ��_20_0_100");
	characterPtr->addSkill(L"BuffSelf_����buff_20_20_EvadeBuff_����buff_ATTR_Good_4_100_100");
	characterPtr->addSkill(L"BuffCast_����buffף��_20_20_EvadeBuff_����buff_ATTR_Good_4_100_100");
	characterPtr->addSkill(L"Summon_�ٻ�Slime_20_20_Slime");
	characterPtr->addSkill(L"BlinkSelf_��˸_20_10_3");
	characterPtr->addSkill(L"Repel_����_20_10_3_10");
	characterPtr->addSkill(L"Thunder_����_20_10_30");

	setName("qwerty");

	controlMode = NormalMode;

	characterPtr->setHP(100);
	characterPtr->setMaxHP(100);
	characterPtr->setMP(100);
	characterPtr->setMaxMP(100);

	characterPtr->setStrength(10);
	characterPtr->setAgility(10);
	characterPtr->setIntellect(10);
	characterPtr->setLuck(10);
	characterPtr->setViewSize(5);
	characterPtr->setCharacterType(Character::Good);
	characterPtr->setPlayType(Character::Player);

	//testInventory......

	Inventory* woodSword = InventoryFactory::getInstance()->getInventory("sword000");
	woodSword->equipLeftHand(characterPtr);

	Inventory* ironSword = InventoryFactory::getInstance()->getInventory("sword001");
	ironSword->equipRightHand(characterPtr);

	Inventory* testItem0 = InventoryFactory::getInstance()->getInventory("sword001");
	Inventory* testItem1 = InventoryFactory::getInstance()->getInventory("sword001");
	Inventory* testItem2 = InventoryFactory::getInstance()->getInventory("sword001");
	Inventory* testItem3 = InventoryFactory::getInstance()->getInventory("sword001");

	characterPtr->addInventory(testItem0);
	characterPtr->addInventory(testItem1);
	characterPtr->addInventory(testItem2);
	characterPtr->addInventory(testItem3);

	characterPtr->addInventory("bigSword000");
	characterPtr->addInventory("sword002");
	characterPtr->addInventory("torch000");
	characterPtr->addInventory("torch000");
	characterPtr->addInventory("supply000");

	//////////////////////////////////////////////////////////////////////////
	std::wstring buffname0 = L"WeightBuff_�������_ATTR_Good_4_20_100";
	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname0));

	std::wstring buffname1 = L"ChantBuff_�Զ�����_OnRoundStart_Good_10_20_1";
	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname1));

	std::wstring buffname2 = L"BlockProBuff_������_ATTR_Good_4_100_100";
	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname2));

	std::wstring buffname3 = L"AccuracyBuff_����buff_ATTR_Good_4_100_100";
	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname3));

	//	std::wstring buffname2 = L"VertigoBuff_ѣ��_ATTR_Bad_2_10";
	//	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname2));

	characterPtr->speak(L"�²۲����²۲����²۲����²۲����²۲����²۲����²۲����²۲����²۲���");
}

void Player::initMission()
{
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	characterPtr->setMapCoord(storey->getUpCoord());
	storey->addCharacter(storey->getUpCoord(), characterPtr);
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
	return Dungeon::getInstance()->getStorey()->isMoveAble(position);
}

void Player::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (controlMode)
	{
	case NormalMode:
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			playerAttack(keyCode);
			break;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_CTRL)
		{
			controlMode = HaltMode;
			showAtkArea();
			break;
		}
		playerMove(keyCode);
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

void Player::playerAttack(cocos2d::EventKeyboard::KeyCode keyCode)
{
	characterPtr->attack();
}

void Player::playerMove(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (!isMoveAble(keyCode))
	{
		playerSetOrientation(keyCode);
		return;
	}
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

std::string Player::getName()
{
	return characterPtr->getName();
}

void Player::setName(const std::string& name)
{
	CCAssert(characterPtr, "characterPtr is null");
	characterPtr->setName(name);
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