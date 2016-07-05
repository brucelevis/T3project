#include "StoreyBuilder.h"
#include<tinyxml2\tinyxml2.h>
#include"FieldEnum.h"
#include"RandomNumber.h"
#include"cocos2d.h"

using namespace Field;

USING_NS_CC;

StoreyBuilder::StoreyBuilder()
{
	storey = NULL;
}


StoreyBuilder::~StoreyBuilder()
{
}

void StoreyBuilder::init()
{
}

Storey* StoreyBuilder::generate()
{
	if (storey)
	{
		delete storey;
	}
	storey = new Storey(100,100);

	int maxFeatures=50;
	// place the first room in the center
	if (!makeRoom(storey->getWidth() / 2, storey->getHeight() / 2, static_cast<Direction>(RandomNumber::instance()->randomInt(4), true)))
	{
		CCLOG("Unable to place the first room\n");
		exit(-1);
	}

	// we already placed 1 feature (the first room)
	for (int i = 1; i < maxFeatures; ++i)
	{
		if (!createFeature())
		{
			CCLOG("Unable to place more features(place %d)\n", i);
			exit(-1);
		}
	}

	if (!placeObject(UpStairs))
	{
		CCLOG("Unable to place up stairs\n");
		exit(-1);
	}

	if (!placeObject(DownStairs))
	{
		CCLOG("Unable to place down stairs\n");
		exit(-1);
	}

//	for (int& tile : tiles)
//	{
//		if (tile == Unused)
//			tile = 1;
//		else if (tile == Floor || tile == Corridor)
//			tile = 2;
//	}
}


bool StoreyBuilder::createFeature()
{
	for (int i = 0; i < 1000; ++i)
	{
		if (exits.empty())
			break;

		//�ӵ�ǰ���еĿ��ܳ��ھ��������ѡһ�����������������ѡһ�������xy����
		int r =RandomNumber::instance()->randomInt(exits.size());
		int x =RandomNumber::instance()->randomInt(exits[r].x, exits[r].x + exits[r].width - 1);
		int y =RandomNumber::instance()->randomInt(exits[r].y, exits[r].y + exits[r].height - 1);

		//�����xy�����4�����ܷ�������
		for (int j = 0; j < DirectionCount; ++j)
		{
			if (createFeature(x, y, static_cast<Direction>(j)))
			{
				exits.erase(exits.begin() + r);
				return true;
			}
		}
	}

	return false;
}

bool StoreyBuilder::createFeature(int x, int y, Direction dir)
{
	static const int roomChance = 50; // corridorChance = 100 - roomChance

	int dx = 0;
	int dy = 0;

	if (dir == North)
		dy = 1;
	else if (dir == South)
		dy = -1;
	else if (dir == West)
		dx = 1;
	else if (dir == East)
		dx = -1;

	if (storey->getTile(x + dx, y + dy) != Floor && storey->getTile(x + dx, y + dy) != Corridor)
		return false;

	if (RandomNumber::instance()->randomInt(100) < roomChance)
	{
		if (makeRoom(x, y, dir))
		{
			storey->setTile(x, y, ClosedDoor);

			return true;
		}
	}
	else
	{
		if (makeCorridor(x, y, dir))
		{
			if (storey->getTile(x + dx, y + dy) == Floor)
				storey->setTile(x, y, ClosedDoor);
			else // don't place a door between corridors
				storey->setTile(x, y, Corridor);

			return true;
		}
	}

	return false;
}

bool StoreyBuilder::makeRoom(int x, int y, Direction dir, bool firstRoom /*= false*/)
{
	static const int minRoomSize = 6;
	static const int maxRoomSize = 15;

	Rect room;
	room.width = RandomNumber::instance()->randomInt(minRoomSize, maxRoomSize);
	room.height = RandomNumber::instance()->randomInt(minRoomSize, maxRoomSize);

	//room������xyΪ�������ɣ����Ǹ��ݳ���ƫ��һ���width����heigh
	if (dir == North)
	{
		room.x = x - room.width / 2;
		room.y = y - room.height;
	}

	else if (dir == South)
	{
		room.x = x - room.width / 2;
		room.y = y + 1;
	}

	else if (dir == West)
	{
		room.x = x - room.width;
		room.y = y - room.height / 2;
	}

	else if (dir == East)
	{
		room.x = x + 1;
		room.y = y - room.height / 2;
	}

	if (placeRect(room, Floor))
	{
		rooms.emplace_back(room);

		//����ĳ����ڷǳ����������������ǵ�һ�����䣬��ô4�����򶼿���Ϊ����
		//����ǰ�������ɵĿ��ܵ����г��ڷ���exits����
		if (dir != South || firstRoom) // north side
			exits.emplace_back(Rect{ room.x, room.y - 1, room.width, 1 });
		if (dir != North || firstRoom) // south side
			exits.emplace_back(Rect{ room.x, room.y + room.height, room.width, 1 });
		if (dir != East || firstRoom) // west side
			exits.emplace_back(Rect{ room.x - 1, room.y, 1, room.height });
		if (dir != West || firstRoom) // east side
			exits.emplace_back(Rect{ room.x + room.width, room.y, 1, room.height });

		return true;
	}

	return false;
}

bool StoreyBuilder::makeCorridor(int x, int y, Direction dir)
{
	static const int minCorridorLength = 3;
	static const int maxCorridorLength = 6;

	Rect corridor;
	corridor.x = x;
	corridor.y = y;

	if (RandomNumber::instance()->randomBool()) // horizontal corridor
	{
		corridor.width = RandomNumber::instance()->randomInt(minCorridorLength, maxCorridorLength);
		corridor.height = 1;

		if (dir == North)
		{
			corridor.y = y - 1;

			if (RandomNumber::instance()->randomBool()) // west
				corridor.x = x - corridor.width + 1;
		}

		else if (dir == South)
		{
			corridor.y = y + 1;

			if (RandomNumber::instance()->randomBool()) // west
				corridor.x = x - corridor.width + 1;
		}

		else if (dir == West)
			corridor.x = x - corridor.width;

		else if (dir == East)
			corridor.x = x + 1;
	}

	else // vertical corridor
	{
		corridor.width = 1;
		corridor.height = RandomNumber::instance()->randomInt(minCorridorLength, maxCorridorLength);

		if (dir == North)
			corridor.y = y - corridor.height;

		else if (dir == South)
			corridor.y = y + 1;

		else if (dir == West)
		{
			corridor.x = x - 1;

			if (RandomNumber::instance()->randomBool()) // north
				corridor.y = y - corridor.height + 1;
		}

		else if (dir == East)
		{
			corridor.x = x + 1;

			if (RandomNumber::instance()->randomBool()) // north
				corridor.y = y - corridor.height + 1;
		}
	}

	if (placeRect(corridor, Corridor))
	{
		if (dir != South && corridor.width != 1) // north side
			exits.emplace_back(Rect{ corridor.x, corridor.y - 1, corridor.width, 1 });
		if (dir != North && corridor.width != 1) // south side
			exits.emplace_back(Rect{ corridor.x, corridor.y + corridor.height, corridor.width, 1 });
		if (dir != East && corridor.height != 1) // west side
			exits.emplace_back(Rect{ corridor.x - 1, corridor.y, 1, corridor.height });
		if (dir != West && corridor.height != 1) // east side
			exits.emplace_back(Rect{ corridor.x + corridor.width, corridor.y, 1, corridor.height });

		return true;
	}

	return false;
}

bool StoreyBuilder::placeRect(const Field::Rect& rect, int tile)
{
	if (rect.x < 1 || rect.y < 1 || rect.x + rect.width > storey->getWidth() - 1 || rect.y + rect.height > storey->getHeight() - 1)
		return false;

	for (int y = rect.y; y < rect.y + rect.height; ++y)
		for (int x = rect.x; x < rect.x + rect.width; ++x)
		{
			if (storey->getTile(x, y) != Unused)
				return false; // the area already used
		}

	for (int y = rect.y - 1; y < rect.y + rect.height + 1; ++y)
		for (int x = rect.x - 1; x < rect.x + rect.width + 1; ++x)
		{
			if (x == rect.x - 1 || y == rect.y - 1 || x == rect.x + rect.width || y == rect.y + rect.height)
				storey->setTile(x, y, Wall);
			else
				storey->setTile(x, y, tile);
		}

	return true;
}

bool StoreyBuilder::placeObject(int tile)
{
	if (rooms.empty())
		return false;

	int r = RandomNumber::instance()->randomInt(rooms.size()); // choose a random room
	int x = RandomNumber::instance()->randomInt(rooms[r].x + 1, rooms[r].x + rooms[r].width - 2);
	int y = RandomNumber::instance()->randomInt(rooms[r].y + 1, rooms[r].y + rooms[r].height - 2);

	if (storey->getTile(x, y) == Floor)
	{
		storey->setTile(x, y, tile);

		// place one object in one room (optional)
		rooms.erase(rooms.begin() + r);

		return true;
	}

	return false;
}

void StoreyBuilder::writeToFile()
{
	std::string filePath = FileUtils::getInstance()->getWritablePath() + "tile.tmx";
	std::string picturePath = FileUtils::getInstance()->fullPathForFilename("tile.png");

	tinyxml2::XMLDocument *pDoc=new tinyxml2::XMLDocument();
	//xml ������������ѡ��
	tinyxml2::XMLDeclaration *pDel = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	pDoc->LinkEndChild(pDel);

	//���map�ڵ�
	tinyxml2::XMLElement *mapElement = pDoc->NewElement("map");
	mapElement->SetAttribute("version", "1.0");
	mapElement->SetAttribute("orientation", "orthogonal");
	mapElement->SetAttribute("renderorder", "right-down");
	mapElement->SetAttribute("width", storey->getWidth());
	mapElement->SetAttribute("height", storey->getHeight());
	mapElement->SetAttribute("tilewidth", "32");
	mapElement->SetAttribute("tileheight", 32);
	mapElement->SetAttribute("nextobjectid", "1");
	pDoc->LinkEndChild(mapElement);

	//���tileset�ڵ�
	tinyxml2::XMLElement *tilesetElement = pDoc->NewElement("tileset");
	tilesetElement->SetAttribute("firstgid", "1");
	tilesetElement->SetAttribute("name", "tiled");
	tilesetElement->SetAttribute("tilewidth", "32");
	tilesetElement->SetAttribute("tileheight", "32");
	tilesetElement->SetAttribute("tilecount", "128");
	tilesetElement->SetAttribute("clumns", 64);
	mapElement->LinkEndChild(tilesetElement);

	//��tileset�ڵ������image�ڵ�
	tinyxml2::XMLElement *imageElement = pDoc->NewElement("image");
	imageElement->SetAttribute("source", picturePath.c_str());
	imageElement->SetAttribute("width", "256");
	imageElement->SetAttribute("height", "512");
	tilesetElement->LinkEndChild(imageElement);

	//���layer�ڵ�
	tinyxml2::XMLElement *layerElement = pDoc->NewElement("layer");
	layerElement->SetAttribute("name", "bk");
	layerElement->SetAttribute("width" , storey->getWidth());
	layerElement->SetAttribute("height", storey->getHeight());
	mapElement->LinkEndChild(layerElement);

	//���layer�е�bk data�ڵ�
	tinyxml2::XMLElement *bkdataElement = pDoc->NewElement("data");
	layerElement->LinkEndChild(bkdataElement);

	//bk data ����
	for (int i = 0; i < storey->getWidth(); i++)
	{
		for (int j = 0; j < storey->getHeight(); j++)
		{
			tinyxml2::XMLElement *tempElement = pDoc->NewElement("tile");
			tempElement->SetAttribute("gid", "1");
			bkdataElement->LinkEndChild(tempElement);
		}
	}


	//���terrain layer�ڵ�
	tinyxml2::XMLElement *terrainlayerElement = pDoc->NewElement("layer");
	terrainlayerElement->SetAttribute("name", "terrain");
	terrainlayerElement->SetAttribute("width", storey->getWidth());
	terrainlayerElement->SetAttribute("height", storey->getHeight());
	mapElement->LinkEndChild(terrainlayerElement);

	//���terrain layer��data
	tinyxml2::XMLElement *terraindataElement = pDoc->NewElement("data");
	terrainlayerElement->LinkEndChild(terraindataElement);

	//���data����
	for (int i = 0; i < storey->getWidth(); i++)
	{
		for (int j = 0; j < storey->getHeight(); j++)
		{
			tinyxml2::XMLElement *tempElement = pDoc->NewElement("tile");
			tempElement->SetAttribute("gid", storey->getTile(i,j));
			terraindataElement->LinkEndChild(tempElement);
		}
	}

	pDoc->SaveFile(filePath.c_str());
	pDoc->Print();
	delete pDoc;
}