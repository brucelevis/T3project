#pragma once

#include<string>
#include"base\ccUtils.h"
#include<vector>
#include"Storey.h"

class ToolFunction
{
public:
	ToolFunction();
	~ToolFunction();
	static int string2int(const std::string& str);
	static std::string int2string(int i);
	static std::wstring string2wstring(std::string str);
	static std::string wstring2string(std::wstring wstr);
	static std::string WStr2UTF8(const std::wstring& src);

	
	//�Ƿ�ʮ��λ����
	static bool isNear4(cocos2d::Point oriCoord,cocos2d::Point targetCoord);
	//�Ƿ�����
	static bool isNear8(cocos2d::Point oriCoord,cocos2d::Point targetCoord);

	static long getCurmTime();





	//�ҵ�ԭ�㸽����Ч�ĵ�(��character),�������ʧ�ܷ���ori
	static cocos2d::Point findValidPlace(
		Field::Storey* storey,
		cocos2d::Point ori
	);

	static cocos2d::Point findValidPlaceWithoutTrap(
		Field::Storey* storey,
		cocos2d::Point ori
	);

	//A*Ѱ·��������һ��Ҫ�ߵ�λ��
	static cocos2d::Point nextStep(
		cocos2d::Point src,
		cocos2d::Point dest
	);
	static std::vector<cocos2d::Point> findPath(
		cocos2d::Point src,
		cocos2d::Point dest
	);
	static std::vector<cocos2d::Point> findPath(
		Field::Storey* s,
		cocos2d::Point src,
		cocos2d::Point dest
	);
};

