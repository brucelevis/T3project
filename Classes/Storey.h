#pragma once

#include<tinyxml2\tinyxml2.h>
#include"cocos2d.h"
#include <list>

class Character;
class StoreyInventoryHandler;


namespace Field {

	class Storey
	{
	public:
		Storey(int w, int h);
		~Storey();
		cocos2d::Point getTilePosition(cocos2d::Point coord);
		void setPositionByCoord(Character* character,cocos2d::Point coord);
		int getTile(int x, int y);
		int getTile(cocos2d::Point coord);
		void setTile(int x, int y, int tile);

		Character* getCharacter(int x, int y);
		Character* getCharacter(cocos2d::Point mapCoord);
		std::list<Character* >& getAllCharacter();

		void moveUp(Character* character);
		void moveDown(Character* character);
		void moveLeft(Character* character);
		void moveRight(Character* character);

		void addCharacter(int x, int y, Character* character);
		void addCharacter(cocos2d::Point coord, Character* character);
		void removeCharacter(int x, int y);
		void removeCharacter(Character* character);
		void changeCharacterCoord(Character* character, cocos2d::Point targetCoord);

		StoreyInventoryHandler* getInventoryHandler();

		//严格可到达
		bool isMoveAble(cocos2d::Point mapCoord);
		//忽略队友
		bool isMoveAble_v2(cocos2d::Point mapCoord);
		//忽略路径上所有character
		bool isMoveAble_v3(cocos2d::Point mapCoord);
		bool isMoveAble(int tile);
		bool isPartner(cocos2d::Point mapCoord);
		bool isWall(cocos2d::Point mapCoord);
		bool isFloor(cocos2d::Point mapCoord);
		bool isValid(cocos2d::Point mapCoord);
		bool isIce(cocos2d::Point mapCoord);
		bool isTrap(cocos2d::Point mapCoord);

		bool isPlayer(Character* character);

		int getHeight();
		int getWidth();
		void writeToFile(std::string floor);
		std::string getFileContent();
		tinyxml2::XMLDocument* getPDoc();
		cocos2d::TMXTiledMap *getTileMap();
		std::vector<Character*>& getCharacterMap();
	protected:
		void characterMoveUp(Character* character);
		void characterMoveDown(Character* character);
		void characterMoveLeft(Character* character);
		void characterMoveRight(Character* character);

		void exchangeCoordUp(Character* character);
		void exchangeCoordDown(Character* character);
		void exchangeCoordLeft(Character* character);
		void exchangeCoordRight(Character* character);

		int height;
		int width;
		CC_SYNTHESIZE(cocos2d::Point, upCoord, UpCoord);
		CC_SYNTHESIZE(cocos2d::Point, downCoord, DownCoord);
		std::string picturePath;
		//逻辑地图
		std::vector<int> tiles;
		//所有角色位置地图
		std::vector<Character*> characterMap;
		//所有角色列表
		std::list<Character*> characterList;
		//用于显示
		cocos2d::TMXTiledMap *tileMap;

		StoreyInventoryHandler* inventoryHandler;
	};
}

