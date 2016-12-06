#include "MPRecoverySelf.h"
#include "ToolFunction.h"
#include "Character.h"



Skill::MPRecoverySelf::MPRecoverySelf()
{
}


Skill::MPRecoverySelf::~MPRecoverySelf()
{
}

Skill::MPRecoverySelf* Skill::MPRecoverySelf::createPrototype()
{
	return new MPRecoverySelf();
}

std::string Skill::MPRecoverySelf::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"Ч��:\n")
		+ ToolFunction::WStr2UTF8(L"�ظ�")
		+ ToolFunction::int2string(value) + ToolFunction::WStr2UTF8(L"ħ��ֵ");
}

void Skill::MPRecoverySelf::run()
{
	caster->sufferMPEffect(value);
}

void Skill::MPRecoverySelf::initExtraMessage(std::vector<std::string> extraMessage)
{
	value = ToolFunction::string2int(extraMessage[0]);
}
