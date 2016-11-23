#include "HudLayer.h"
#include"HudMenuItem.h"
#include"HudCursor.h"
#include "HudMenuSystem.h"
#include "HudPlayerStateMenu.h"
#include "DialogueSystem.h"
#include "HudLayout.h"
#include "HudBar.h"
#include "HudMessageBox.h"

USING_NS_CC;

HudLayer::HudLayer()
{
}


HudLayer::~HudLayer()
{
}

bool HudLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	HudLayout::getInstance()->init();
	HudMenuSystem::getInstance()->init();
	HudPlayerStateMenu::getInstance()->init();
	DialogueSystem::getInstance()->init();
	HudBar::getInstance()->init();
	HudMessageBox::getInstance()->init();
	
	HudMessageBox::getInstance()->addMessage(L"��Ϣ0");
	HudMessageBox::getInstance()->addMessage(L"��Ϣ1");
	HudMessageBox::getInstance()->addMessage(L"��Ϣ2");
	HudMessageBox::getInstance()->addMessage(L"��Ϣ3");
	HudMessageBox::getInstance()->addMessage(L"��Ϣ4");
	HudMessageBox::getInstance()->addMessage(L"��Ϣ5");
	HudMessageBox::getInstance()->addMessage(L"��Ϣ6");
	HudMessageBox::getInstance()->addMessage(L"��Ϣ7");
	HudMessageBox::getInstance()->addMessage(L"��Ϣ8");
	HudMessageBox::getInstance()->addMessage(L"��Ϣ9");


//	DialogueSystem::getInstance()->runDialogue("testDialogue");

	return true;
}

void HudLayer::update()
{
	HudMenuSystem::getInstance()->update();
	HudPlayerStateMenu::getInstance()->update();
	HudBar::getInstance()->update();
}

void HudLayer::show()
{
	HudMenuSystem::getInstance()->show();
}

void HudLayer::hide()
{
	HudMenuSystem::getInstance()->hide();
}
