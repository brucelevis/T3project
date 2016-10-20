#include "CharacterAttr.h"

CharacterAttr::CharacterAttr()
{
	strength = 1;
	intellect = 1;
	agility = 1;
	luck = 0;
	characterType = Neutral;
	viewSize = 5;
	maxHP = 10;
	maxMP = 10;

	evadePro = 0;//����ֵ
	accuracyPro = 10;//������
	criticalPro = 0;//��������
	criticalPoint = 0;//��������ֵ
	blockPro = 0;//��ֵ����
	blockPoint = 0;//�񵲵���
	comboPro = 0;//��������

	moveAble = true;
	attackAble = true;
	castAble = true;
	phyImmu = false;
	magicImmu = false;
}