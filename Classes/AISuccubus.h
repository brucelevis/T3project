#pragma once

#include "AIBase.h"

class AISuccubus:public AIBase
{
public:
	AISuccubus();
	~AISuccubus();
	void update();
	void feedback(Character* character);
	void handleDialogueResult(std::string dialogueName, int resultNumber);
protected:
	bool isFirst;

	//�����Χ��enemy
	std::vector<Character* > getEnemyAround();
	//���player��Χ��enemy
	std::vector<Character* > getEnemyAroundPlayer();

	//�Ƚ�����character���characterPtr�ľ���
	bool cmpDistance(Character* a, Character* b);
	
};

