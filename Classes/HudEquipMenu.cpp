#include "HudEquipMenu.h"
#include "HudDescriptionMenu.h"
#include "HudUnequipAccessoryMenu.h"
#include "HudUnequipArmorMenu.h"
#include "Player.h"
#include "HudMenuItem.h"
#include "InventoryFactory.h"
#include "InventoryInHand.h"
#include "Armor.h"
#include "Accessory.h"
#include "HudLayout.h"
#include "ToolFunction.h"
#include "HudTrigActChildMenu.h"
#include "HudUnequipLeftMenu.h"
#include "HudUnequipRightMenu.h"
#include "HudCursor.h"

HudEquipMenu::HudEquipMenu()
	:HudMenu(cocos2d::Rect(
		0, 0,
		HudLayout::getInstance()->getMediumMenuSize().width,
		HudLayout::getInstance()->getMediumMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getMediumMenuPosition().x,
		HudLayout::getInstance()->getMediumMenuPosition().y);
}

HudEquipMenu::~HudEquipMenu()
{
}

void HudEquipMenu::init()
{
}

void HudEquipMenu::addItem(HudMenuItem* item)
{
	HudMenu::addItem(item);
	item->setAliginment(cocos2d::TextHAlignment::LEFT);
}

void HudEquipMenu::update()
{
	clear();

	Character* characterPtr = Player::getInstance()->getcharacterPtr();

	InventoryInHand* leftInventory = characterPtr->getLeftHand();
	InventoryInHand* rightInventory = characterPtr->getRightHand();
	Armor* armor = characterPtr->getArmor();
	Accessory* accessory = characterPtr->getAccessory();

	std::string leftInventoryLabel = leftInventory ? leftInventory->getCname() : "empty";
	std::string rightInventoryLabel = rightInventory ? rightInventory->getCname() : "empty";
	std::string armorLabel = armor ? armor->getCname() : "empty";
	std::string accessoryLabel = accessory ? accessory->getCname() : "empty";

	leftInventoryLabel = ToolFunction::WStr2UTF8(L"����:") + leftInventoryLabel;
	rightInventoryLabel = ToolFunction::WStr2UTF8(L"����:") + rightInventoryLabel;
	armorLabel = ToolFunction::WStr2UTF8(L"����:") + armorLabel;
	accessoryLabel = ToolFunction::WStr2UTF8(L"����:") + accessoryLabel;

	//////////////////////////////////////////////////////////////////////////

	HudMenuItem* leftInventoryItem = new HudMenuItem(leftInventoryLabel);

	HudUnequipLeftMenu* unequipLeftInventoryMenu = new HudUnequipLeftMenu();
	unequipLeftInventoryMenu->setParent(this);
	HudTrigActChildMenu* leftInventoryTrigger = new HudTrigActChildMenu(unequipLeftInventoryMenu);
	leftInventoryItem->setTrigger(leftInventoryTrigger);

	//////////////////////////////////////////////////////////////////////////

	HudMenuItem* rightInventoryItem = new HudMenuItem(rightInventoryLabel);

	HudUnequipRightMenu* unequipRightInventoryMenu = new HudUnequipRightMenu();
	unequipRightInventoryMenu->setParent(this);
	HudTrigActChildMenu* rightInventoryTrigger = new HudTrigActChildMenu(unequipRightInventoryMenu);
	rightInventoryItem->setTrigger(rightInventoryTrigger);

	//////////////////////////////////////////////////////////////////////////

	HudMenuItem* armorInventoryItem = new HudMenuItem(armorLabel);

	HudUnequipArmorMenu* unequipArmorMenu = new HudUnequipArmorMenu();
	unequipArmorMenu->setParent(this);
	HudTrigActChildMenu* armorTrigger = new HudTrigActChildMenu(unequipArmorMenu);
	armorInventoryItem->setTrigger(armorTrigger);

	//////////////////////////////////////////////////////////////////////////

	HudMenuItem* accessoryInventoryItem = new HudMenuItem(accessoryLabel);

	HudUnequipAccessoryMenu* unequipAccessoryMenu = new HudUnequipAccessoryMenu();
	unequipAccessoryMenu->setParent(this);
	HudTrigActChildMenu* accessoryTrigger = new HudTrigActChildMenu(unequipAccessoryMenu);
	accessoryInventoryItem->setTrigger(accessoryTrigger);

	//////////////////////////////////////////////////////////////////////////

	this->addItem(leftInventoryItem);
	this->addItem(rightInventoryItem);
	this->addItem(armorInventoryItem);
	this->addItem(accessoryInventoryItem);

	HudCursor::getInstance()->setCurMenu(this);
}

void HudEquipMenu::chooseItem(int index)
{
	HudMenu::chooseItem(index);

	Inventory* curInventory;

	switch (index)
	{
	case 0:
		curInventory = Player::getInstance()->getcharacterPtr()->getLeftHand();
		break;
	case 1:
		curInventory = Player::getInstance()->getcharacterPtr()->getRightHand();
		break;
	case 2:
		curInventory = Player::getInstance()->getcharacterPtr()->getArmor();
		break;
	case 3:
		curInventory = Player::getInstance()->getcharacterPtr()->getAccessory();
		break;
	default:
		break;
	}

	if (curInventory == nullptr)
	{
		HudDescriptionMenu::getInstance()->setDescription(L"empty");
	}
	else
	{
		HudDescriptionMenu::getInstance()->setDescription(
			curInventory->getDescription()
		);
	}

	if (layout->isVisible())
	{
		HudDescriptionMenu::getInstance()->show();
	}
}

void HudEquipMenu::show()
{
	HudMenu::show();
	HudDescriptionMenu::getInstance()->show();
}

void HudEquipMenu::hide()
{
	HudMenu::hide();
	HudDescriptionMenu::getInstance()->hide();
}