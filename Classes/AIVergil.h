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

	//���Իָ�
	bool recovery();



	//״̬:
	//0:���ܸ���
	//1:վ�Ų���
	//2:��·
	int curState;

	//�ж�
	void followAI();

	//�ȴ�
	void waitAI();

	//��·
	void leadAI();


	//���Ա������
	void protectPlayer();


	//����������ߵ�player
	bool healPlayer();
	

	//�����Χ��enemy
	std::vector<Character* > getEnemyAround();
	//���player��Χ��enemy
	std::vector<Character* > getEnemyAroundPlayer();


	//�����Ұ��Χ��enemy
	std::vector<Character* > getEnemyInView();
	//���player��Ұ��Χ�ڵ�enemy
	std::vector<Character* > getEnemyInPlayerView();



	//�ж���Χ�Ƿ���enemy
	bool isSafe();

	//�Ƚ�����character���characterPtr�ľ���
	bool cmpDistance(Character* a, Character* b);
	//������Ʒ,���װ��ĳ����Ʒ������true
	bool tidyInventory();

	//����ɹ��ظ�������true
	bool tryUseHPSupply();
	bool tryUseMPSupply();

	bool tryAddAttr();

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

	void updateSmallTalkCount();


	int smallTalkCount;

	//9���ʱ���²�
	bool level9Word;
};

