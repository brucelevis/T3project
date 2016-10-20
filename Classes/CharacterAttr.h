#pragma once


#include <string>


struct CharacterAttr
{
	enum CharacterType
	{
		Good, Neutral, Bad
	};

	int strength;
	int intellect;
	int agility;
	int luck;
	CharacterType characterType;
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

	bool moveAble;
	bool attackAble;
	bool castAble;
	bool phyImmu;
	bool magicImmu;
};

