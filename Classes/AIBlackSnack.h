#pragma once

#include "AIBase.h"


class AIBlackSnack:public AIBase
{
public:
	AIBlackSnack();
	~AIBlackSnack();
	void update();
	void feedback(Character* character);
protected:
	//�����Χ�е����������������ƻ�
	//����ж�����true�����򷵻�false
	bool tryDestroyShrine();
};

