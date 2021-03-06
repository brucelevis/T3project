#include "Dungeon.h"
#include<sstream>
#include"Character.h"
#include"StoreyBuilder.h"


using namespace Field;

Dungeon::Dungeon()
{
	curFloor = 0;
}


Dungeon::~Dungeon()
{
}


void Field::Dungeon::generate(int floorNum)
{
	clear();
	Storey* tempStorey=StoreyBuilder::getInstance()->generate(floorNum);
	this->addStorey(tempStorey);
}

int Field::Dungeon::getFloorNum()
{
	return storeyVec.size();
}

void Field::Dungeon::addStorey(Storey * storey)
{
	storeyVec.push_back(storey);
}

Storey * Field::Dungeon::getStorey()
{
	return storeyVec[curFloor];
}

void Field::Dungeon::writeToFile()
{
	for (int i = 0; i < getFloorNum(); i++)
	{
		Storey* tempStorey = storeyVec[i];
		std::stringstream stream;
		stream << i;
		std::string f;
		stream >> f;
		tempStorey->writeToFile(f);
	}
}

void Field::Dungeon::changeFloor(int floor)
{
	if (floor >= 0 && floor < storeyVec.size())
	{
		curFloor = floor;
	}

}

void Field::Dungeon::nextFloor()
{
	if (curFloor < storeyVec.size() - 1)
	{
		curFloor++;
	}
}

void Field::Dungeon::addCharacter(Character * character)
{
	cocos2d::Point position = character->getMapCoord();
	storeyVec[curFloor]->addCharacter(position.x,position.y,character);
}


void Field::Dungeon::clear()
{
	for (size_t i = 0; i < storeyVec.size(); i++)
	{
		delete storeyVec[i];
	}
	storeyVec.clear();
}

Character * Field::Dungeon::getCharacter(int x,int y)
{
	return storeyVec[curFloor]->getCharacter(x,y);
}

Character* Field::Dungeon::getCharacter(cocos2d::Point mapCoord)
{
	return storeyVec[curFloor]->getCharacter(mapCoord);
}
