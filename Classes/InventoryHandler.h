#pragma once

#include <map>
#include <string>

class Inventory;

class InventoryHandler
{
public:
	InventoryHandler();
	~InventoryHandler();
	void addInventory(const std::string& inventoryName,int count);
	void addInventory(Inventory* inventory);
	void removeInventory(const std::string& inventoryName, int count);
	std::map<std::string, int>& getAllInventory();
	int getCount(const std::string& inventoryName);
	Inventory* getInventory(const std::string& inventoryName);
protected:
	//��¼ÿ��inventory�ĸ���
	std::map<std::string, int> inventoryBox;
};

