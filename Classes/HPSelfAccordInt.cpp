#include "HPSelfAccordInt.h"
#include "ToolFunction.h"
#include "Character.h"
#include "EffectManager.h"



Skill::HPSelfAccordInt::HPSelfAccordInt()
{
}


Skill::HPSelfAccordInt::~HPSelfAccordInt()
{
}

Skill::HPSelfAccordInt* Skill::HPSelfAccordInt::createPrototype()
{
	return new HPSelfAccordInt();
}

std::string Skill::HPSelfAccordInt::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"Ч��:\n")
		+ ToolFunction::WStr2UTF8(L"�ظ�:(")
		+ ToolFunction::int2string(valuePer) 
		+ ToolFunction::WStr2UTF8(L"% x [����])")
		+ ToolFunction::WStr2UTF8(L"����ֵ");
}

void Skill::HPSelfAccordInt::run()
{

	int value = double(valuePer)*double(caster->getIntellect()) / 100.0;

	caster->sufferHPEffect(value);

	EffectManager::getInstance()->showEffect(
		"HPRecovery",
		caster->getPosition(),
		1.0);

}

void Skill::HPSelfAccordInt::initExtraMessage(std::vector<std::string> extraMessage)
{
	valuePer = ToolFunction::string2int(extraMessage[0]);
}
