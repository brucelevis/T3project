#include "BlinkSelf.h"
#include "ToolFunction.h"
#include "Dungeon.h"
#include "LinerSelector.h"
#include "MyCamera.h"

Skill::BlinkSelf::BlinkSelf()
{
}

Skill::BlinkSelf::~BlinkSelf()
{
}

Skill::BlinkSelf* Skill::BlinkSelf::createPrototype()
{
	return new Skill::BlinkSelf();
}

std::string Skill::BlinkSelf::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"效果:\n")
		+ ToolFunction::WStr2UTF8(L"向前方跳跃")
		+ ToolFunction::int2string(distance)
		+ ToolFunction::WStr2UTF8(L"单位距离");
}

void Skill::BlinkSelf::run()
{
	LinerSelector selector;
	selector.setImpactNumber(-1);
	selector.setMaxLength(distance);

	std::vector<cocos2d::Point > coords = selector.select(caster);
	if (coords.empty())
	{
		return;
	}
	cocos2d::Point targetCoord = coords[coords.size() - 1];

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	storey->changeCharacterCoord(caster, targetCoord);

	MyCamera::getInstance()->moveCameraTo(
		storey->getTilePosition(targetCoord), 0.1
	);
}

void Skill::BlinkSelf::initExtraMessage(std::vector<std::string> extraMessage)
{
	distance = ToolFunction::string2int(extraMessage[0]);
}