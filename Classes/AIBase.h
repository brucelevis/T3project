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
	
	void goNextStep(
		cocos2d::Point startPoint,
		cocos2d::Point endPoint,
		cocos2d::Point nextStep
	);



	void changeOrientationTo(Character* target);
	//���ܣ�����ɹ��ƶ�������true�����򷵻�false
	bool flee(Character* target);
	bool isInAttackArea(Character* target);
	bool isNear(cocos2d::Point coord);

	//���ԭ����Χ�����ж�ӦĿ��
	std::vector<Character* > getTargetAround(
		cocos2d::Point ori,
		Character::Type type,
		int searchSize
	);


	//ĳ��λ���Ƿ���Ե���
	bool isAccessAble(cocos2d::Point coord);
	
	//��targetCoord�ƽ�
	void approach(cocos2d::Point targetCoord);


	//�й�
	void wander();
	bool isPlayerNear();
};

