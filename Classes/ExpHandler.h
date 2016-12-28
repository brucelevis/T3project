#pragma once

class Character;

class ExpHandler
{
public:
	//��������ֵ����
	static const int expRequire[27];

	static const int skillExpAdd;
public:
	ExpHandler(Character* character);
	~ExpHandler();
	bool isLevelUp();
	void addExp(const int e);
	void useAttrPoint();
	int getCurLevel();
	int getCurExp();
	int getCurAttrPoint();


protected:
	void levelUp();


	Character* characterPtr;
	 
	int exp;
	int level;
	//���Ե�
	int attrPoint;
};

