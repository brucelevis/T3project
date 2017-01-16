#include "AntiChantSphere.h"
#include "RandomNumber.h"
#include "Character.h"
#include "ToolFunction.h"

Sphere::AntiChantSphere::AntiChantSphere()
{
}

Sphere::AntiChantSphere::~AntiChantSphere()
{
}

void Sphere::AntiChantSphere::run(Character* a, Character* b, int damage)
{

	int roll = RandomNumber::getInstance()->randomInt(1, 100);

	if (roll <= chantClearPro)
	{
		b->clearChant();
	}
}

Sphere::AntiChantSphere* Sphere::AntiChantSphere::createProtoType()
{
	return  new AntiChantSphere();
}

std::string Sphere::AntiChantSphere::getDescription()
{
	return ToolFunction::WStr2UTF8(L"������:\n")
		+ ToolFunction::WStr2UTF8(L"ÿ�ι�����:")
		+ ToolFunction::int2string(chantClearPro)
		+ "%"
		+ ToolFunction::WStr2UTF8(L"���������Է���������");
}

void Sphere::AntiChantSphere::initExtraMessage(std::vector<std::string> extraMessage)
{
	setChantClearPro(ToolFunction::string2int(extraMessage[0]));
}
