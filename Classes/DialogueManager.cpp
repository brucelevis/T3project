#include "DialogueManager.h"
#include "Statement.h"
#include "Question.h"
#include "ToolFunction.h"
#include "DialogueDriver.h"
#include "HudMenuSystem.h"
#include "HudStateSystem.h"
#include "KeyController.h"

USING_NS_CC;


DialogueManager::DialogueManager()
{
}


DialogueManager::~DialogueManager()
{
}

void DialogueManager::init()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("dialogue.xml");
	
	tinyxml2::XMLElement *dialogueBoxElement = doc.RootElement();
	tinyxml2::XMLElement *dialogueElement = dialogueBoxElement->FirstChildElement("dialogue");

	while (dialogueElement)
	{
		Dialogue* dialogue = new Dialogue();
		dialogue->setName(getChildElementStrAttr(dialogueElement, "name"));
		
		tinyxml2::XMLElement *sentenceElement = getChildElement(dialogueElement, "sentence");
		while (sentenceElement)
		{
			Sentence* sentence;
			std::string type = getChildElementStrAttr(sentenceElement, "type");
			if (type == "statement")
			{
				sentence = initStatement(sentenceElement);
			}
			else if(type=="question")
			{
				sentence = initQuestion(sentenceElement);
			}
			dialogue->addSentence(sentence);

			sentenceElement = sentenceElement->NextSiblingElement();
		}
		dialogueBox[dialogue->getName()] = dialogue;

		dialogueElement = dialogueBoxElement->NextSiblingElement();
	}

	DialogueDriver::getInstance()->init();
}

void DialogueManager::run(const std::string& dialogueName)
{
	KeyController::getInstance()->switchCtrlToDialog();

	DialogueDriver::getInstance()->startDialogue(dialogueBox[dialogueName]);
}

void DialogueManager::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	DialogueDriver::getInstance()->handleKeyPressed(keyCode);
}

Statement* DialogueManager::initStatement(tinyxml2::XMLElement *sentenceElement)
{
	Statement* sentence = new Statement();

	sentence->setActorSpriteName(getChildElementStrAttr(sentenceElement, "actorName"));
	sentence->setWord(getChildElementStrAttr(sentenceElement, "word"));
	sentence->setNextIndex(getChildElementIntAttr(sentenceElement, "next"));

	return sentence;
}

Question* DialogueManager::initQuestion(tinyxml2::XMLElement *sentenceElement)
{
	Question* sentence = new Question();

	sentence->setActorSpriteName(getChildElementStrAttr(sentenceElement, "actorName"));
	sentence->setWord(getChildElementStrAttr(sentenceElement, "word"));

	tinyxml2::XMLElement* optionListElement = getChildElement(sentenceElement,"optionList");

	tinyxml2::XMLElement* option = getChildElement(optionListElement, "option");
	int count = 0;
	while (option)
	{
		sentence->addOption(getChildElementStrAttr(option, "label"));
		sentence->addOptionMap(count,getChildElementIntAttr(option, "next"));

		option = option->NextSiblingElement();
		count++;
	}
	return sentence;
}

std::string DialogueManager::getChildElementStrAttr(tinyxml2::XMLElement* element, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(element, attrName);
	return childElement->GetText();
}

std::wstring DialogueManager::getChildElementWStrAttr(tinyxml2::XMLElement* element, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(element, attrName);
	std::string temp=childElement->GetText();
	return ToolFunction::string2wstring(childElement->GetText());
}

int DialogueManager::getChildElementIntAttr(tinyxml2::XMLElement* element, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(element, attrName);
	return ToolFunction::string2int(childElement->GetText());
}

tinyxml2::XMLElement* DialogueManager::getChildElement(tinyxml2::XMLElement* parent, std::string name)
{
	tinyxml2::XMLElement* element = parent->FirstChildElement(name.c_str());
	CCAssert(element, (std::string("unknow element type ") + name).c_str());
	return element;
}
