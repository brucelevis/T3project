#pragma once

#include "AIBase.h"

class AIPersephone:public AIBase
{
public:
	AIPersephone();
	~AIPersephone();
	void update();
	void feedback(Character* character);
	void lastWords();
protected:
	//�Ƿ��player�Ի�0����1���Ѿ��Ի����
	int talkFlag;
};

