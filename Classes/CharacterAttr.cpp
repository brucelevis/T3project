#include "CharacterAttr.h"

CharacterAttr::CharacterAttr()
{
	physicalImmune = false;
	magicImmune = false;

	moveAble = true;
	attackAble=true;
	chantAble=true;
	skillAble=true;
	actionAble=true;

	strength = 0;
	intellect = 0;
	agility = 0;
	luck = 0;
	viewSize = 1;
	maxHP = 0;
	maxMP = 0;

	evadePoint = 0;//����ֵ
	accuracyPoint = 0;//������
	criticalPro = 0;//��������
	criticalPoint = 0;//��������ֵ
	criticalPer = 0;//��������
	blockPro = 0;//��ֵ����
	blockPoint = 0;//�񵲵���
	comboPro = 0;//��������
	weight = 0;//����

}

void CharacterAttr::calculateBattleAttr()
{
	evadePoint = agility;

	accuracyPoint = agility + 70;

	criticalPro = agility*1;
	criticalPro = criticalPro > 90 ? 90 : criticalPro;

	criticalPer = strength + 100;

	criticalPoint = strength*0.6;

	blockPro = agility*0.2;
	blockPro = blockPro > 90 ? 90 : blockPro;

	blockPoint = strength*0.2 + 5;

	comboPro = agility;
	comboPro = comboPro > 90 ? 90 : comboPro;

	weight = strength * 2;
}
