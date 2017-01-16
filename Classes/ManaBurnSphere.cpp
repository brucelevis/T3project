#include "ManaBurnSphere.h"
#include "Character.h"
#include "ToolFunction.h"



Sphere::ManaBurnSphere::ManaBurnSphere()
{
}


Sphere::ManaBurnSphere::~ManaBurnSphere()
{
}

void Sphere::ManaBurnSphere::run(Character* a, Character* b, int damage)
{
	double mpDamageValue = -double(damage)*(double(mpDamagePer) / 100.0);
	b->sufferMPEffect(int(mpDamageValue));
}

Sphere::ManaBurnSphere* Sphere::ManaBurnSphere::createProtoType()
{
	return new ManaBurnSphere();
}

std::string Sphere::ManaBurnSphere::getDescription()
{
	return ToolFunction::WStr2UTF8(L"����ȼ��:\n")
		+ ToolFunction::WStr2UTF8(L"ÿ�ι������:(")
		+ToolFunction::int2string(mpDamagePer)
		+"%x [Damage])"
		+ ToolFunction::WStr2UTF8(L"ħ��ֵ�˺�");
}

void Sphere::ManaBurnSphere::initExtraMessage(std::vector<std::string> extraMessage)
{
	setMpDamagePer(ToolFunction::string2int(extraMessage[0]));
}
