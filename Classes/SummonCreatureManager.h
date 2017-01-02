#pragma once

#include "Singleton.h"
#include <vector>


class Character;


//�����ٻ��������Դ���������
class SummonCreatureManager:public Singleton<SummonCreatureManager>
{
public:
	SummonCreatureManager();
	~SummonCreatureManager();
	void init();
	void initMission();
	void addCharacter(Character* creature);
protected:
	std::vector<Character*> creatureList;
};

