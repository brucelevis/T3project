#include "HudEquipMenu.h"
#include "Player.h"
#include "HudMenuItem.h"
#include "InventoryManager.h"
#include "InventoryInHand.h"
#include "Armor.h"
#include "Accessory.h"
#include "HudLayout.h"
#include "ToolFunction.h"



HudEquipMenu::HudEquipMenu()
	:HudMenu(cocos2d::Rect(
		0,0,
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

	HudMenuItem* leftInventoryItem = new HudMenuItem(leftInventoryLabel);
	HudMenuItem* rightInventoryItem = new HudMenuItem(rightInventoryLabel);
	HudMenuItem* armorInventoryItem = new HudMenuItem(armorLabel);
	HudMenuItem* accessoryInventoryItem = new HudMenuItem(accessoryLabel);

	this->addItem(leftInventoryItem);
	this->addItem(rightInventoryItem);
	this->addItem(armorInventoryItem);
	this->addItem(accessoryInventoryItem);
}

