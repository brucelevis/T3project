#pragma once
#include <list>
#include <iostream>
#include <fstream>
#include <vector>
#include"base\ccUtils.h"
#include"Storey.h"
using namespace std;


class AStar
{
public:
	struct AStarPoint
	{
		int x;
		int y;
		int f;//f=g+h
		int g;//����㵽�Լ��Ĵ���
		int h;//���Լ����յ�Ĵ���
		struct AStarPoint *parent;//ָ���׵�ָ��
		struct AStarPoint *self;//��¼�Լ��ĵ�ַ

						   //���صȺŲ�����
		bool operator==(const AStarPoint &point)
		{
			return this->x == point.x &&
				this->y == point.y;
		}

		//����<������
		bool operator<(const AStarPoint &point)
		{
			return this->f < point.f;
		}

		friend ostream& operator<<(ostream &os, const AStarPoint &point)
		{
			os << "Point(x=" << point.x << ",y=" << point.y << ",f=" << point.f
				<< ",g=" << point.g << ",h=" << point.g
				<< ",parent=" << point.parent << ",self="
				<< point.self << ")" << endl;
			return os;
		}
	};

	struct Coordinate
	{
		int x;
		int y;
	};

	AStar();
	~AStar();
	AStar(cocos2d::Point start, cocos2d::Point end,
		Field::Storey* s);
	std::vector<cocos2d::Point> findPath();
	std::vector<cocos2d::Point> findPath_v2();
	std::vector<cocos2d::Point> findPath_v3();
	cocos2d::Point nextStep();
	cocos2d::Point nextStep_v2();
	cocos2d::Point nextStep_v3();
private:
	list<AStarPoint> opened_list;//�����б�
	list<AStarPoint> closed_list;//�ر��б�

	Field::Storey* storey;
	cocos2d::Point startPoint;
	cocos2d::Point endPoint;

	vector<AStarPoint*> malloc_space;//�洢new�����Ŀռ�

	ofstream _log;

	//����������֮��ľ���,���õ��������پ���
	int _get_distance(int start_x, int start_y, int end_x, int end_y);

	bool _is_shorter(const AStarPoint &point1, const AStarPoint &point2);//�Ƚ�����Point�Ĵ�С������������

	void _print(const list<AStarPoint> &point);
};
