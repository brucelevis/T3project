#pragma once

#include "AIBase.h"

class AIVergil :public AIBase
{
public:
	AIVergil();
	~AIVergil();
	void update();
	void feedback(Character* character);
	void handleDialogueResult(std::string dialogueName, int resultNumber);
	void lastWords();
protected:
	//״̬:
	//0:���ܸ���
	//1:���ɻ
	int curState;

	//���ܸ����ai
	void stayCloseAI();
	//���ɻ��ai
	void freeAI();

	//���player��Χ��enemy
	std::vector<Character* > getEnemyAroundPlayer();

	//�Ƚ�����character���characterPtr�ľ���
	bool cmpDistance(Character* a, Character* b);
	
};
