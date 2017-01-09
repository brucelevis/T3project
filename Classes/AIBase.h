#pragma once

#include "Character.h"

class AIBase
{
public:
	AIBase();
	virtual ~AIBase();
	virtual void update();
	virtual void feedback(Character* character);
	virtual void handleDialogueResult(std::string dialogueName,int resultNumber);
	void setCharacter(Character* character);
	Character* searchTargetBFS(Character::Type type);
	Character* searchTargetBFS(Character::Type type,int distance);


	virtual void levelUp();
	//��������
	virtual void lastWords();
protected:
	Character* characterPtr;
	//����character��target֮�������پ���
	int getManhattanDistance(Character* target);
	void seek(Character* target);
	void changeOrientationTo(Character* target);
	//���ܣ�����ɹ��ƶ�������true�����򷵻�false
	bool flee(Character* target);
	bool isInAttackArea(Character* target);
	bool isNear(cocos2d::Point coord);


	//ĳ��λ���Ƿ���Ե���
	bool isAccessAble(cocos2d::Point coord);
	
	//��targetCoord�ƽ�
	void seek(cocos2d::Point targetCoord);


	//�й�
	void wander();
	bool isPlayerNear();
};

