#pragma once

#include"Storey.h"
#include"platform\CCPlatformMacros.h"


namespace Field {

	class Dungeon
	{
	public:
		Dungeon();
		~Dungeon();

		int getFloorNum();
		void addStorey(Storey* storey);
		Storey* getStorey();
		void writeToFile();
		void changeFloor(int floor);
		void nextFloor();
		void addCharacter(Character* character);
		void characterMove(cocos2d::Point oriPosition, cocos2d::Point tarPosition);

		//���ص�ǰ�����character�����û�У�����nullPtr
		Character* getCharacter(int x,int y);
	protected:
		std::vector<Storey*> storeyVec;
		CC_SYNTHESIZE(int, curFloor, CurFloor);
	};

}

