#include "AStar.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include"FieldEnum.h"
using namespace std;
AStar::AStar()
{
}

AStar::~AStar()
{
	_log.close();
	//�����ڴ�й¶���ͷŷ�����ڴ�
	for (unsigned int i = 0; i < malloc_space.size(); ++i)
		delete(malloc_space[i]);
}

AStar::AStar(cocos2d::Point start, cocos2d::Point end, Field::Storey * s)
{
	storey = s;
	startPoint = start;
	endPoint = end;
}

std::vector<cocos2d::Point> AStar::findPath()
{
	//g��ʾ����㵽�Լ��Ĵ��ۣ�h��ʾ���Լ����յ�Ĵ���
	//����ʼ����뵽�����б���
	AStarPoint *start_point = new AStarPoint();
	malloc_space.push_back(start_point);
	start_point->x = startPoint.x;
	start_point->y = startPoint.y;
	start_point->g = 0;
	start_point->h = _get_distance(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	start_point->f = start_point->h + start_point->g;
	start_point->parent = NULL;//��ʼ��ĸ��ڵ�Ϊ��
	start_point->self = start_point;//�Լ��ĵ�ַ

	opened_list.push_back(*start_point);//����ʼ��Ž������б���

	while (0 != opened_list.size())
	{
		opened_list.sort();//�ѿ����б��е���������

		list<AStarPoint>::iterator first = opened_list.begin();
		AStarPoint first_point = *first;//��ȡ�б��еĵ�һ������

		closed_list.push_back(first_point);//��������ݷ���ر��б���
		opened_list.erase(first);//ɾ�����Ԫ��

		if (first_point.x == endPoint.x && first_point.y == endPoint.y)//�����ǰ���������յ㣬�����
			break;
		//�ѵ�ǰ��������ڵĵ�ȫ�����뿪���б���
		int top_left_x = first_point.x == 0 ? 0 : first_point.x - 1;
		int top_left_y = first_point.y == 0 ? 0 : first_point.y - 1;
		int bottom_right_x = first_point.x >= storey->getWidth() - 1 ? first_point.x : first_point.x + 1;
		int bottom_right_y = first_point.y >= storey->getHeight() - 1 ? first_point.y : first_point.y + 1;

		for (int i = top_left_x; i <= bottom_right_x; ++i)
		{
			for (int j = top_left_y; j <= bottom_right_y; ++j)
			{
				//б������
				if (i != first_point.x && j != first_point.y)
				{
					continue;
				}
				if (i != first_point.x || j != first_point.y)
				{
					//���ϰ���
					if (storey->isMoveAble(cocos2d::Point(i, j))
						|| cocos2d::Point(i,j)==endPoint)
//					if(storey->isMoveAble(storey->getTile(i,j)))
					{
						AStarPoint point;
						point.x = i;
						point.y = j;

						list<AStarPoint>::iterator iter = find(opened_list.begin(), opened_list.end(), point);
						if (iter != opened_list.end())
						{
							//�Ѿ��ڿ����б���
							AStarPoint pp = *iter;
							int d1 = _get_distance(first_point.x, first_point.y,
								startPoint.x, startPoint.y);
							int d2 = _get_distance(first_point.x, first_point.y, i, j);
							if (d1 + d2 < pp.g)
							{
								pp.parent = first_point.self;
								pp.g = d1 + d2;
							}
							continue;
						}

						iter = find(closed_list.begin(), closed_list.end(), point);
						if (iter != closed_list.end())
						{
							//�Ѿ��ڹر��б���
							AStarPoint pp = *iter;
							int d1 = _get_distance(first_point.x, first_point.y,
								startPoint.x, startPoint.y);
							int d2 = _get_distance(first_point.x, first_point.y, i, j);
							if (d1 + d2 < pp.g)
							{
								pp.parent = first_point.self;
								pp.g = d1 + d2;
							}
							continue;
						}

						//�Ȳ��ڿ����б���Ҳ���ڹر��б���
						AStarPoint *p = new AStarPoint();
						p->x = i;
						p->y = j;
						p->h = _get_distance(i, j, endPoint.x, endPoint.y);
						p->g = _get_distance(startPoint.x, startPoint.y, i, j);
						p->f = p->g + p->h;
						p->parent = first_point.self;
						p->self = p;
						//���뵽 �����б� ��ȥ
						opened_list.push_back(*p);

						malloc_space.push_back(p);
					}
				}
			}
		}
	}

	std::vector<cocos2d::Point> result;
	std::vector<cocos2d::Point> temp;
	list<AStarPoint>::const_iterator iter = --closed_list.end();
	AStarPoint p = *iter;
	while (p.parent != NULL)
	{
		cocos2d::Point position;
		position.x = p.x;
		position.y = p.y;
		temp.push_back(position);
		p = *(p.parent);
	}
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		result.push_back(temp[i]);
	}
	return result;
}

cocos2d::Point AStar::nextStep()
{
	std::vector<cocos2d::Point> path = findPath();
	return path[0];
}

/*
* ����������֮ǰ�ľ��룬���õ��������پ���
* distance = |start.x-end.x| + |start.y-end.y|
*/
int AStar::_get_distance(int start_x, int start_y, int end_x, int end_y)
{
	return abs(end_x - start_x) + abs(end_y - start_y);
}

bool AStar::_is_shorter(const AStarPoint &point1, const AStarPoint &point2)
{
	return point1.f < point2.f;
}

void AStar::_print(const list<AStarPoint> &point)
{
	list<AStarPoint>::const_iterator i = point.begin();
	while (i != point.end())
	{
		_log << *i;
		++i;
	}
	_log << endl;
}