#pragma once

#include <string>


struct CharacterAttr
{
	CharacterAttr();

	//base attr
	int strength;
	int intellect;
	int agility;
	int luck;
	int viewSize;
	int maxHP;
	int maxMP;

	//battle attr
	//calculate from AGI,STR,INT
	int evadePoint;//����ֵ
	int accuracyPoint;//������
	int criticalPro;//��������
	int criticalPoint;//��������ֵ
	int criticalPer;//��������
	int blockPro;//��ֵ����
	int blockPoint;//�񵲵���
	int comboPro;//��������
	int weight;//����

	void calculateBattleAttr();
};
