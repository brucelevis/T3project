#include "HudNoteSystem.h"
#include "2d/CCAnimation.h"
#include "KeyController.h"
#include "ToolFunction.h"
#include "HudLayer.h"
#include "HudLayout.h"

HudNoteSystem::HudNoteSystem()
{
}

HudNoteSystem::~HudNoteSystem()
{
}

void HudNoteSystem::init()
{
	layout = cocos2d::ui::Layout::create();
	layout->setBackGroundImage("HUD/menu.png");
	layout->setBackGroundImageScale9Enabled(true);
	layout->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);

	layout->setSize(cocos2d::Size(300, 400));
	layout->setOpacity(180);
	layout->setPosition(cocos2d::Vec2(200, 500));

	HudLayer::getInstance()->addChild(layout);

	text = cocos2d::ui::Text::create("", "fonts/arialuni.ttf", 20);
	text->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	text->setPosition(cocos2d::Vec2(10, -30));
	text->setOpacity(255);
	text->ignoreContentAdaptWithSize(false);
	text->setContentSize(cocos2d::Size(270, 400));
	//	description->ignoreContentAdaptWithSize(false);
	//	description->setTextAreaSize(cocos2d::Size(150, 400));
	layout->addChild(text);

	footer = cocos2d::ui::Text::create("", "fonts/arialuni.ttf", 18);
	footer->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	footer->setPosition(cocos2d::Vec2(50, -65));
	footer->setOpacity(255);
	footer->ignoreContentAdaptWithSize(false);
	footer->setContentSize(cocos2d::Size(300, 100));
	//	description->ignoreContentAdaptWithSize(false);
	//	description->setTextAreaSize(cocos2d::Size(150, 400));
	layout->addChild(footer);

	leftArrow = cocos2d::Sprite::create("sys/noteArrowLeft.png");
	rightArrow = cocos2d::Sprite::create("sys/noteArrowRight.png");

	leftArrow->setPosition(175, 300);
	rightArrow->setPosition(525, 300);

	HudLayer::getInstance()->addChild(leftArrow);
	HudLayer::getInstance()->addChild(rightArrow);

	hide();
}

void HudNoteSystem::openNote(std::string noteID)
{
	curNote = NoteTextFactory::getInstance()->getNoteText(noteID);
	curPageIndex = 0;

	setText(curNote.getPage(curPageIndex));

	this->show();

	if (curNote.getSize() > 1)
	{
		showRightArrow();
	}

	hideLeftArrow();
	updateFooter();
	KeyController::getInstance()->switchCtrlToNote();
}

void HudNoteSystem::openNote(NoteText note)
{
	curNote = note;
	curPageIndex = 0;

	setText(curNote.getPage(curPageIndex));

	this->show();

	if (curNote.getSize() > 1)
	{
		showRightArrow();
	}

	hideLeftArrow();
	updateFooter();
	KeyController::getInstance()->switchCtrlToNote();
}

void HudNoteSystem::nextPage()
{
	curPageIndex++;

	if (curPageIndex >= curNote.getSize() - 1)
	{
		curPageIndex = curNote.getSize() - 1;
		if (curNote.getSize() > 1)
		{
			showLeftArrow();
		}

		hideRightArrow();
	}
	else
	{
		if (curNote.getSize() > 1)
		{
			showLeftArrow();
			showRightArrow();
		}
	}

	setText(curNote.getPage(curPageIndex));
	updateFooter();
}

void HudNoteSystem::previousPage()
{
	curPageIndex--;

	if (curPageIndex <= 0)
	{
		curPageIndex = 0;

		if (curNote.getSize() > 1)
		{
			showRightArrow();
		}

		hideLeftArrow();
	}
	else
	{
		if (curNote.getSize() > 1)
		{
			showLeftArrow();
			showRightArrow();
		}
	}
	setText(curNote.getPage(curPageIndex));
	updateFooter();
}

void HudNoteSystem::hide()
{
	layout->setVisible(false);
	leftArrow->setVisible(false);
	rightArrow->setVisible(false);
}

void HudNoteSystem::show()
{
	layout->setVisible(true);
}

void HudNoteSystem::setText(std::string str)
{
	text->setText(str);
}

void HudNoteSystem::updateFooter()
{
	footer->setText(
		ToolFunction::WStr2UTF8(L"[���ҷ�ҳ|Esc�˳�] page: ") +

		ToolFunction::int2string(curPageIndex + 1) +
		"/" +
		ToolFunction::int2string(curNote.getSize()));
}

void HudNoteSystem::showLeftArrow()
{
	leftArrow->setVisible(true);
	leftArrow->stopAllActions();
	leftArrow->setPosition(175, 300);
	leftArrow->runAction(
		cocos2d::RepeatForever::create(
			cocos2d::Sequence::create(
				cocos2d::MoveBy::create(1, cocos2d::Vec2(-5, 0)),
				cocos2d::MoveBy::create(0.1, cocos2d::Vec2(5, 0)),
				NULL
			)
		)
	);
}

void HudNoteSystem::showRightArrow()
{
	rightArrow->setVisible(true);
	rightArrow->setVisible(true);
	rightArrow->stopAllActions();
	rightArrow->setPosition(525, 300);
	rightArrow->runAction(
		cocos2d::RepeatForever::create(
			cocos2d::Sequence::create(
				cocos2d::MoveBy::create(1, cocos2d::Vec2(5, 0)),
				cocos2d::MoveBy::create(0.1, cocos2d::Vec2(-5, 0)),
				NULL
			)
		)
	);
}

void HudNoteSystem::hideLeftArrow()
{
	leftArrow->setVisible(false);
}

void HudNoteSystem::hideRightArrow()
{
	rightArrow->setVisible(false);
}

void HudNoteSystem::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		this->hide();
		KeyController::getInstance()->switchCtrlToPlayer();
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		previousPage();
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		nextPage();
	}
}