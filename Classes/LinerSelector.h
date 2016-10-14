#pragma once

#include "SelectorBase.h"

namespace Skill
{
	class LinerSelector:public SelectorBase
	{
	public:
		// 5 | 1 | 6		
		//-----------
		// 3 | 0 | 4
		//-----------
		// 7 | 2 | 8
		enum LinerOrientation
		{
			ZERO,UP,DOWN,LEFT,RIGHT,UPLEFT,UPRIGHT,DOWNLEFT,DOWNRIGHT
		};
		LinerSelector();
		~LinerSelector();
		std::vector<cocos2d::Point> select(Character* caster);
		void setOrientation(LinerOrientation ori);
		void setImpactNumber(int number);
		void setMaxLength(int length);
	protected:
		cocos2d::Point getOffset(Character* caster);
		//������caster����Ϊ��׼��Ĭ������
		LinerOrientation orientation;
		//Ӱ�쵥λ������Ĭ��Ϊ1,-1Ϊ�������ڻ���
		int impactNumber;
		//���ȣ�Ĭ��Ϊ5
		int maxLength;
	};
}
