#include "ExpAdd.h"
#include "ToolFunction.h"
#include "Character.h"



Skill::ExpAdd::ExpAdd()
{
}


Skill::ExpAdd::~ExpAdd()
{
}

Skill::ExpAdd* Skill::ExpAdd::createPrototype()
{
	return new Skill::ExpAdd();
}

void Skill::ExpAdd::run()
{
	caster->addExp(value);
}

void Skill::ExpAdd::initExtraMessage(std::vector<std::string> extraMessage)
{
	value = ToolFunction::string2int(extraMessage[0]);
}

std::string Skill::ExpAdd::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"Ч��:\n") +
		ToolFunction::WStr2UTF8(L"���Ӿ���")+
		ToolFunction::int2string(value)+"\n";
}
