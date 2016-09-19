#pragma once
#include "Sentence.h"
#include <vector>
#include <map>
#include <string>

class Question :
	public Sentence
{
public:
	Question();
	~Question();
	void addOptionMap(int optionIndex,int sentenceIndex);
	void addOption(std::string option);
	void changeOption(int index);
	void run();
	std::vector<std::string>& getAllOption();
	int getSize();
protected:
	int curIndex;
	//ѡ��index����һ��index��ӳ��
	std::map<int, int> optionMap;
	std::vector<std::string> options;
};

