#pragma once

#include "AIBase.h"


class AIVampire:public AIBase
{
public:
	AIVampire();
	~AIVampire();
	void update();
	void feedback(Character* character);
protected:
	//Σ������ֵ�ٷֱ�
	int deadLine;
	bool isDangerous();
};

