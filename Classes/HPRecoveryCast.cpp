#include "HPRecoveryCast.h"
#include "ToolFunction.h"
#include "FixedSelector.h"
#include "Dungeon.h"
#include "Character.h"
#include "EffectManager.h"




Skill::HPRecoveryCast::HPRecoveryCast()
{
}


Skill::HPRecoveryCast::~HPRecoveryCast()
{
}

Skill::HPRecoveryCast* Skill::HPRecoveryCast::createPrototype()
{
	return new HPRecoveryCast();
}

std::string Skill::HPRecoveryCast::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"Ч��:\n")
		+ ToolFunction::WStr2UTF8(L"��ǰ��λ�ظ�")
		+ ToolFunction::int2string(value) + ToolFunction::WStr2UTF8(L"����ֵ");
}

void Skill::HPRecoveryCast::run()
{
	FixedSelector selector;
	selector.addRelativeCoord(cocos2d::Point(0, 1));
	std::vector<cocos2d::Point > coords=selector.select(caster);
	cocos2d::Point targetCoord = coords[0];

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	Character* target = storey->getCharacter(targetCoord);
	cocos2d::Point targetPosition = storey->getTilePosition(targetCoord);

	EffectManager::getInstance()->showEffect("HPRecovery", targetPosition, 1.0);

	if (target)
	{
		target->sufferHPEffect(value);
	}
}

void Skill::HPRecoveryCast::initExtraMessage(std::vector<std::string> extraMessage)
{
	value = ToolFunction::string2int(extraMessage[0]);
}
