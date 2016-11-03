#include "BuffFactory.h"
#include "BuffBase.h"
#include "HPBuff.h"
#include "MPBuff.h"
#include "BaseAttrBuff.h"
#include "ToolFunction.h"



Buff::BuffFactory::BuffFactory()
{
}

Buff::BuffFactory::~BuffFactory()
{
	std::map<std::string, BuffBase*>::iterator iter = buffPrototypeBox.begin();
	while (iter != buffPrototypeBox.end())
	{
		delete iter->second;
		iter++;
	}
}

void Buff::BuffFactory::init()
{
	HPBuff* hpBuffPrototype = new HPBuff();
	MPBuff* mpBuffPrototype = new MPBuff();
	BaseAttrBuff* attrBuffPrototype = new BaseAttrBuff();
	buffPrototypeBox["HPBuff"] = hpBuffPrototype;
	buffPrototypeBox["MPBuff"] = mpBuffPrototype;
	buffPrototypeBox["BaseAttrBuff"] = attrBuffPrototype;
}

Buff::BuffBase* Buff::BuffFactory::getBuff(std::string b)
{
//	std::string b=ToolFunction::WStr2UTF8(buffName);
	std::vector<std::string> buffMessage;
	split(b, '_', buffMessage);

	if (buffMessage.empty())
	{
		return nullptr;
	}

	BuffBase* buff = getBuffPrototype(buffMessage[0]);
	buffMessage.erase(buffMessage.begin());//remove buff name
	buff->init(buffMessage);
	buff->setID(b);
	return buff;
}

Buff::BuffBase* Buff::BuffFactory::getBuffPrototype(const std::string& buffName)
{
	return buffPrototypeBox[buffName]->createPrototype();
}

void Buff::BuffFactory::split(std::string s, char splitchar, std::vector<std::string>& vec)
{
	if (vec.size() > 0)//��֤vec�ǿյ�
		vec.clear();
	int length = s.length();
	int start = 0;
	for (int i = 0; i < length; i++)
	{
		if (s[i] == splitchar && i == 0)//��һ���������ָ��
		{
			start += 1;
		}
		else if (s[i] == splitchar)
		{
			vec.push_back(s.substr(start, i - start));
			start = i + 1;
		}
		else if (i == length - 1)//����β��
		{
			vec.push_back(s.substr(start, i + 1 - start));
		}
	}
}