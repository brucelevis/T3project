#pragma once
#include "AIBase.h"

class AICommonEnemy :public AIBase
{
public:
	AICommonEnemy();
	virtual ~AICommonEnemy();
	virtual void update();
protected:
	//Σ������ֵ�ٷֱ�
	int deadLine;
	void seek(Character* target);
	void flee(Character* target);
	bool isDangerous();
	bool isInAttackArea(Character* target);
};

