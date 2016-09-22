#pragma once

#include"Singleton.h"
class HudMenuItem;
#include <vector>
#include"2d\CCSprite.h"


class HudMenu
{
public:
	HudMenu(cocos2d::Rect rect=cocos2d::Rect(0,0,0,0));
	~HudMenu();
	virtual void update();

	//������̰���
	virtual void handleUp();
	virtual void handleDown();
	virtual void handleLeft();
	virtual void handleRight();

	void show();
	void hide();

	void clear();

	void setWidth(int w);
	void setHeight(int h);
	int getWidth();
	int getHeight();

	void setPosition(int x,int y);

	void initCursor();
	virtual void addItem(HudMenuItem* item);

	void chooseItem(int index);
	void activeChildMenu(int index);
	void setParent(HudMenu* p);

	//************************************
	// Method:    closeMenu
	// FullName:  HudMenu::closeMenu
	// Access:    public 
	// Returns:   void
	// Qualifier: �رյ�ǰ�˵��������ϼ��˵�
	//************************************
	void closeMenu();

	cocos2d::Sprite* getSprite();
	int getMarginalWidth();
	int getMarginalHeight();
protected:
	void setCursorPosition(int index);
	void increaseIndex();
	void decreaseIndex();

	HudMenu* parent;
	//�ڱ߿��
	cocos2d::Vec2 marginal;
	cocos2d::Sprite* sprite;
	std::vector<HudMenuItem*> itemList;
	int itemIndex;
};

