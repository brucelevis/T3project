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
	void levelUp();
protected:


	//״̬:
	//0:���ܸ���
	//1:վ�Ų���
	int curState;

	//�ж�
	void followAI();

	//�ȴ�
	void waitAI();

	

	//�����Χ��enemy
	std::vector<Character* > getEnemyAround();
	//���player��Χ��enemy
	std::vector<Character* > getEnemyAroundPlayer();

	//�Ƚ�����character���characterPtr�ľ���
	bool cmpDistance(Character* a, Character* b);
	//������Ʒ,���װ��ĳ����Ʒ������true
	bool tidyInventory();

	//����ɹ��ظ�������true
	bool tryUseHPSupply();
	bool tryUseMPSupply();

	bool chooseBetterLefthand();
	bool chooseBetterRighthand();
	bool chooseBetterArmor();
	bool chooseBetterAccessory();
	void showCurState();
	//����
	void smallTalk();
	void tryBuffToPlayer();
	void castBuffToPlayer();
	void healCast();
	void healSelf();
};
