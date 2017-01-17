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
	void handleDialogueResult(std::string dialogueName, int resultNumber);
protected:
	//�Ƿ��player�Ի�0����1���Ѿ��Ի����
	int talkFlag;

	void summonDemon();
	void castThunder();
};

