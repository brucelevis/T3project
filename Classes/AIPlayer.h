#pragma once

#include "AIBase.h"

//����player����
class AIPlayer:public AIBase
{
public:
	AIPlayer();
	~AIPlayer();
	void update();
	void lastWords();
	void handleDialogueResult(std::string dialogueName, int resultNumber);
	void levelUp();
};

