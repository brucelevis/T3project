#pragma once

#include<vector>
#include<tinyxml2\tinyxml2.h>
#include"cocos2d.h"

class Character;


namespace Field {

	class Storey
	{
	public:
		Storey(int w, int h);
		~Storey();
		int getTile(int x, int y);
		int getTile(cocos2d::Point position);
		void setTile(int x, int y, int tile);

		Character* getCharacter(int x, int y);
		Character* getCharacter(cocos2d::Point position);
		void setCharacter(int x, int y, Character* character);
		void removeCharacter(int x, int y);
		void characterMove(cocos2d::Point oriPosition, cocos2d::Point tarPosition);

		int getHeight();
		int getWidth();
		void writeToFile(std::string floor);
		std::string getFileContent();
		tinyxml2::XMLDocument* getPDoc();
		cocos2d::TMXTiledMap *getTileMap();
		std::vector<Character*>& getAllCharacter();
	protected:
		int height;
		int width;
		CC_SYNTHESIZE(cocos2d::Point, upCoord, UpCoord);
		CC_SYNTHESIZE(cocos2d::Point, downCoord, DownCoord);
		std::string picturePath;
		//�߼���ͼ
		std::vector<int> tiles;
		//���н�ɫ�б�
		std::vector<Character*> characterMap;
		//������ʾ
		cocos2d::TMXTiledMap *tileMap;
	};
}

