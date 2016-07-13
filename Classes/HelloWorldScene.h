#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"Character.h"
#include"Dungeon.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void setViewPointCenter(cocos2d::Point position);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	void movePlayer(cocos2d::EventKeyboard::KeyCode keyCode);
	void movePlayer(cocos2d::Point position);
	cocos2d::TMXTiledMap *tileMap;
	Field::Dungeon* dungeon;
	Character* player;
	bool isMoveAble(cocos2d::EventKeyboard::KeyCode keyCode);
};

#endif // __HELLOWORLD_SCENE_H__
