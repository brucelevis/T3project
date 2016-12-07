#pragma once

#include <map>
#include <string>
#include "base/ccTypes.h"

class Inventory;

class InventoryHandler
{
public:
	InventoryHandler();
	~InventoryHandler();
	void addInventory(const std::string& inventoryName,int count=1);
	//************************************
	// Method:    addInventory
	// FullName:  InventoryHandler::addInventory
	// Access:    public 
	// Returns:   void
	// Qualifier: ������ inventory ָ��
	// Parameter: Inventory * inventory
	//************************************
	void addInventory(Inventory* inventory,int count=1);
	void removeInventory(std::string inventoryName, int count=1);
	void removeInventory(int index, int count=1);
	std::map<std::string, int>& getAllInventory();
	int queryInventoryCountByName(const std::string& inventoryName);
	std::string queryInventoryNameByIndex(int index);



	void clear();

	//����������
	int calculateSumWeight();



	//************************************
	// Method:    drop
	// FullName:  InventoryHandler::drop
	// Access:    public 
	// Returns:   void
	// Qualifier: character����ʱ���ã�����ǰ������Ʒ����������
	//************************************
	void drop(cocos2d::Point coord);
protected:
	//��¼ÿ��inventory�ĸ���
	std::map<std::string, int> inventoryBox;


};

