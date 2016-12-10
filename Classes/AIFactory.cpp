#include "AIFactory.h"
#include "AICommonEnemy.h"
#include "AIVergil.h"
#include "AIShrine.h"



AIFactory::AIFactory()
{
}


AIFactory::~AIFactory()
{
}

AIBase* AIFactory::getAI(const std::string& AIName)
{
	if (AIName=="AICommonEnemy")
	{
		return new AICommonEnemy();
	}
	else if (AIName=="AIVergil")
	{
		return new AIVergil;
	}
	else if (AIName == "AIShrine")
	{
		return new AIShrine;
	}
	else
	{
		return nullptr;
	}
}
