 //编写于2016.4.7
//2016.4.9完成拓扑排序
//2017.10.7对Dijkstra算法进行更新
#pragma once
#include<vector>
#include<deque>
#include<string>
#include<iostream>
#include<memory>
#include <algorithm>
#include <map>
#include <stack>
using namespace std;
namespace CjpSTL
{




	class JpGraph
	{
	public:

		class Vertex;
		class AdjAcent
		{
		public:
			int cost;
			Vertex* ptr;

			explicit AdjAcent(int newCost = 0,Vertex* newPtr = nullptr):cost(newCost),ptr(newPtr){}
		};


		class Vertex
		{
		public:
			int index;
			int inDegree;
			vector<AdjAcent>degree;


			Vertex(int data, int in_degree)
				: index(data),
				  inDegree(in_degree)				  
			{
			}
		};

		
		JpGraph(){}

		void lowestCost(const Vertex& v);
		
		void buildGraph(vector<Vertex> vertexs);
		void BFS(int index);
		void DFS(int index);
		void topSort();
	private:
		vector<Vertex>vertexs;
	};


	inline void JpGraph::lowestCost(const Vertex& v)
	{
		vector<pair<bool, int>> status;
		for (int i = 0; i < vertexs.size(); ++i)
		{
			status.push_back(pair<bool, int>(false, INT32_MAX));
		}
		//建立与相应点集对应的集合。
		status[v.index].second = 0;
		auto findMin = [&]()
		{
			int min = INT32_MAX;
			int minIndx = 0;
			for (int i = 0; i < status.size(); ++i)
				if (status[i].second < min && status[i].first == false)
				{
					min = status[i].second;
					minIndx = i;
				}
			return minIndx;
		};
		auto isAllTrue = [&]()
		{
			for (const auto& i : status)
			{
				if (i.first == false)
					return false;
			}
			return true;
		};
		//for (;;)
		//{
		//	status[findMin()].first = true; //每次都将未知的点集中的最小值设为已知
		//	for (int i = 0; i < status.size(); ++i)
		//	{
		//		if (status[i].first == true)
		//		{
		//			for (const auto& adj : vertexs[i].degree)
		//			{
		//				auto desV = (*(adj.ptr)).index;
		//				if (status[i].second + adj.cost < status[desV].second) //对与已知点相连接的点的cost进行更新
		//					status[desV].second = status[i].second + adj.cost;
		//			}
		//		}
		//	}
		//	if (isAllTrue()) //如果所有点都已知，则退出循环
		//		break;
		//}
		while(!isAllTrue())
		{
			auto minIndex = findMin();
			status[minIndex].first = true; //每次都将未知的点集中的最小值设为已知
		
					for (const auto& adj : vertexs[minIndex].degree)
					{
						auto desV = (*(adj.ptr)).index;
						if (status[minIndex].second + adj.cost < status[desV].second) //对与已知点相连接的点的cost进行更新
							status[desV].second = status[minIndex].second + adj.cost;
					}
			
		
		}

		for (int i = 0; i < status.size(); ++i)
		{
			cout << "vertexIndex :" << i << "   cost: " << status[i].second << endl;
		}
	}





	inline void JpGraph::buildGraph(vector<Vertex> vertexs)
	{
		this->vertexs = vertexs;
	}


	inline void JpGraph::BFS(int index)
	{
		map<int, bool>hasVisited;
		deque<int>checkLine;
		for (int i = 0; i < vertexs.size(); ++i)
			hasVisited[i] = false;

		checkLine.push_back(index);
		while(!checkLine.empty())
		{
			int toTravel = checkLine.front();
			checkLine.pop_front();
			if (!hasVisited[toTravel])
			{
				hasVisited[toTravel] = true;
				cout << vertexs[toTravel].index + 1 << " ";

				for(const auto& i : vertexs[toTravel].degree)
				{
					auto toPAt = *(i.ptr);
					if(!hasVisited[toPAt.index])
					{
						checkLine.push_back(toPAt.index);

					}
				}
			}
			else;


		}


	}


	inline void JpGraph::DFS(int index)
	{
		map<int, bool>hasVisited;
		for (int i = 0; i < vertexs.size(); ++i)
		{
			hasVisited[i] = false;
		}
		stack<int>stk;
		stk.push(index);
		while (!stk.empty())
		{
			int toTravel = stk.top();
			stk.pop();
			if (hasVisited[toTravel] == false) 
			{
				hasVisited[toTravel] = true;
				cout << vertexs[toTravel].index + 1 << " ";

				for (const auto& i : vertexs[toTravel].degree)
				{
					auto toPAt = *(i.ptr);
					if (!hasVisited[toPAt.index])
					{
						stk.push(toPAt.index);

					}

				}

			}
			else;

		}
	}


	inline void JpGraph::topSort()
	{
		deque<Vertex>q;
		for(const Vertex& vertex : vertexs)
		{
			if (vertex.inDegree == 0)
				q.push_back(vertex);
		}
		while(q.size()!=0)
		{
			auto i = q.front(); q.pop_front();
			cout<<i.index << " ";
			for(auto& adj : i.degree)
			{
				auto ptr = adj.ptr;
				--(ptr->inDegree);
				if (ptr->inDegree == 0)
					q.push_back(*ptr);
			}


		}

	}

	inline void testTopSort()
	{
		vector<int>vec;
		//sort(vec.begin(), vec.end(), less<int>());
		typedef JpGraph::Vertex  vertex;
		typedef JpGraph::AdjAcent adj;
		vertex v0(0, 0);
		vertex v1(1, 1);
		vertex v2(2, 1);
		vertex v3(3, 2);
		vertex v4(4, 2);
		vertex v5(5, 3);
		vertex v6(6, 2);
		v0.degree = vector<adj>{ adj(1,&v3),adj{ 2,&v1 } };
		v1.degree = vector<adj>{ adj{ 3,&v3 },adj{ 2,&v4 } };
		v2.degree = vector<adj>{ adj{ 5,&v5 },adj{4,&v0} };
		v3.degree = vector<adj>{ adj{ 8,&v5 },adj{ 2,&v2 },adj{2,&v4},adj{ 4,&v6 } };
		v4.degree = vector<adj>{ adj{ 6,&v6 },};
		v5.degree = vector<adj>();
		v6.degree = vector<adj>{ adj{ 1,&v5 } };
		JpGraph graph;
		graph.buildGraph(vector<vertex>{v0, v1, v2, v3, v4, v5, v6});
		graph.topSort();
	}

	inline void testDijkstra()
	{
		std::cout << "testDijkstra :" << std::endl;
		vector<int>vec;
		//sort(vec.begin(), vec.end(), less<int>());
		typedef JpGraph::Vertex  vertex;
		typedef JpGraph::AdjAcent adj;
		vertex v0(0, 0);
		vertex v1(1, 1);
		vertex v2(2, 1);
		vertex v3(3, 2);
		vertex v4(4, 2);
		vertex v5(5, 3);
		vertex v6(6, 2);
		v0.degree = vector<adj>{ adj(1,&v3),adj{ 2,&v1 } };
		v1.degree = vector<adj>{ adj{ 3,&v3 },adj{ 2,&v4 } };
		v2.degree = vector<adj>{ adj{ 5,&v5 },adj{ 4,&v0 } };
		v3.degree = vector<adj>{ adj{ 8,&v5 },adj{ 2,&v2 },adj{ 2,&v4 },adj{ 4,&v6 } };
		v4.degree = vector<adj>{ adj{ 6,&v6 }, };
		v5.degree = vector<adj>();
		v6.degree = vector<adj>{ adj{ 1,&v5 } };
		JpGraph graph;
		graph.buildGraph(vector<vertex>{v0, v1, v2, v3, v4, v5, v6});
		graph.lowestCost(v0);


	}

	inline void testDFSAndBFS()
	{
		
		vector<int>vec;
		//sort(vec.begin(), vec.end(), less<int>());
		typedef JpGraph:: Vertex  vertex;
		typedef JpGraph:: AdjAcent adj;
		vertex v0(0, 0);
		vertex v1(1, 1);
		vertex v2(2, 1);
		vertex v3(3, 2);
		vertex v4(4, 2);
		vertex v5(5, 3);
		vertex v6(6, 2);
		v0.degree = vector<adj>{ adj(1,&v3),adj{ 2,&v1 } };
		v1.degree = vector<adj>{ adj{ 3,&v3 },adj{ 2,&v4 } };
		v2.degree = vector<adj>{ adj{ 5,&v5 },adj{ 4,&v0 } };
		v3.degree = vector<adj>{ adj{ 8,&v5 },adj{ 2,&v2 },adj{ 2,&v4 },adj{ 4,&v6 } };
		v4.degree = vector<adj>{ adj{ 6,&v6 }, };
		v5.degree = vector<adj>();
		v6.degree = vector<adj>{ adj{ 1,&v5 } };
		JpGraph graph;
		graph.buildGraph(vector<vertex>{v0, v1, v2, v3, v4, v5, v6});
		std::cout << "testDFS :" << std::endl;
		graph.DFS(0);
		cout << "test BFS" << endl;
		graph.BFS(0);
	}

}

