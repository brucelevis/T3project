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
	bool isDangerous();
};

