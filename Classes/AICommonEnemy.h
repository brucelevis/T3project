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
	void seek(Character* character);
	void flee(Character* character);
	bool isDangerous();
};

