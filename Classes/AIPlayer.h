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
};

