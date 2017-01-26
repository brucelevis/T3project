#include "HudSysMenu.h"
#include "HudTrigRestart.h"
#include "HudTrigQuit.h"
#include "ToolFunction.h"
#include "HudMenuItem.h"
#include "HudLayout.h"



HudSysMenu::HudSysMenu()
	:HudMenu(cocos2d::Rect(
		0, 0,
		HudLayout::getInstance()->getMediumMenuSize().width,
		HudLayout::getInstance()->getMediumMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getMediumMenuPosition().x,
		HudLayout::getInstance()->getMediumMenuPosition().y);

	HudMenuItem* quitMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"�˳���Ϸ"));
	HudTrigQuit* quitTrigger = new HudTrigQuit();
	quitMenuItem->setTrigger(quitTrigger);

	HudMenuItem* restartMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"���¿�ʼ"));
	HudTrigRestart* restartTrigger = new HudTrigRestart();
	restartMenuItem->setTrigger(restartTrigger);



	this->addItem(quitMenuItem);
	this->addItem(restartMenuItem);
}


HudSysMenu::~HudSysMenu()
{
}

void HudSysMenu::addItem(HudMenuItem* item)
{
	HudMenu::addItem(item);
	item->setAliginment(cocos2d::TextHAlignment::LEFT);
}
