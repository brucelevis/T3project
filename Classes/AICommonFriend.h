#pragma once

#include "AIBase.h"

class AICommonFriend:public AIBase
{
public:
	AICommonFriend();
	~AICommonFriend();
	void update();
protected:
	//�Ƚ�����character���characterPtr�ľ���
	bool cmpDistance(Character* a, Character* b);
	//���player��Χ��enemy
	std::vector<Character* > getEnemyAroundPlayer();


};

