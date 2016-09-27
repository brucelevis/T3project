#include "HudEquipableInventoryMenu.h"
#include "HudMenuItem.h"
#include "ToolFunction.h"
#include "HudTrigEquipLeft.h"



HudEquipableInventoryMenu::HudEquipableInventoryMenu(cocos2d::Rect rect)
	:HudMenu(rect)
{
	HudMenuItem* equipMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"װ��"));
	HudTrigEquipLeft* equipLeftTrig = new HudTrigEquipLeft();
	equipMenuItem->setTrigger(equipLeftTrig);

	this->addItem(equipMenuItem);
	HudMenuItem* dropMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"����"));
	this->addItem(dropMenuItem);
	HudMenuItem* throwMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"Ͷ��"));
	this->addItem(throwMenuItem);

	hide();
}


HudEquipableInventoryMenu::~HudEquipableInventoryMenu()
{
}
