#pragma once

#include <string>


struct CharacterAttr
{
	CharacterAttr();

	int strength;
	int intellect;
	int agility;
	int luck;
	int viewSize;
	int maxHP;
	int maxMP;

	int evadePro;//����ֵ
	int accuracyPro;//������
	int criticalPro;//��������
	int criticalPoint;//��������ֵ
	int blockPro;//��ֵ����
	int blockPoint;//�񵲵���
	int comboPro;//��������
};
