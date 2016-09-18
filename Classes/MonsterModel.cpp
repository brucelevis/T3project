#include "MonsterModel.h"
#include"CharacterManager.h"
#include "AICommonEnemy.h"
#include "InventoryManager.h"



MonsterModel::MonsterModel()
{
}


MonsterModel::~MonsterModel()
{
}

Character * MonsterModel::makeMonster()
{
	Character* monster = CharacterManager::getInstance()->getCharacter(characterName);

	monster->setStrength(strength);
	monster->setIntellect(intellect);
	monster->setAgility(agility);
	monster->setHP(HP);
	monster->setMP(MP);
	monster->setMaxHP(HP);
	monster->setMaxMP(MP);
	monster->setViewSize(viewSize);
	monster->setCharacterType(Character::Bad);
	AICommonEnemy* ai = new AICommonEnemy();
	monster->setAI(ai);

	Inventory* woodSword = InventoryManager::getInstance()->getInventory("sword000");
	woodSword->equipLeftHand(monster);

	return monster;
}
