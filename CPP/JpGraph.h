 //编写于2016.4.7
//2016.4.9完成拓扑排序
#pragma once
#include<vector>
#include<deque>
#include<string>
#include<iostream>
#include <algorithm>
#include <map>
#include <stack>
using namespace std;
namespace CjpSTL
{




	template<typename T>
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

		void lowestCost(const Vertex &v)
		{
			vector<pair<bool, int>>status;
			for (int i = 0; i < vertexs.size();++i)
			{
				status.push_back(pair<bool,int>(false, INT32_MAX));
			}
			//建立与相应点集对应的集合。
			status[v.index ].second = 0;
			auto findMin = [&]()
			{
				int min = INT32_MAX;
				int minIndx = 0;
				for (int i = 0; i < status.size();++i)
					if(status[i].second<min&&status[i].first==false)
					{
						min = status[i].second;
						minIndx = i;
					}
				return minIndx;
			};
			auto isAllTrue = [&]()
			{
				
				for(const auto & i : status)
				{
					if (i.first == false)
						return false;
				}
				return true;
			};
			for (;;) {
				status[findMin()].first = true; //每次都将未知的点集中的最小值设为已知
				for (int i = 0; i < status.size(); ++i)
				{
					if (status[i].first == true)
					{
						for (const auto& adj : vertexs[i].degree)
						{
							auto desV = (*(adj.ptr)).index;
							if (status[i].second + adj.cost < status[desV].second) //对与已知点相连接的点的cost进行更行
								status[desV].second = status[i].second + adj.cost;


						}

					}


				}
				if (isAllTrue()) //如果所有点都已知，则退出循环
					break;

			}
			for (int i = 0; i < status.size();++i)
			{
				cout << "vertexIndex :" << i << "   cost: " << status[i].second << endl;
			}


		}
		static int getStaticVal();
		void buildGraph(vector<Vertex> vertexs);
		void BFS(int index);
		void DFS(int index);
		void topSort();
	private:
		vector<Vertex>vertexs;
	};

	template <typename T>
	int JpGraph<T>::getStaticVal()
	{
		static int val = 4;
		return val;

	}

	template <typename T>
	void JpGraph<T>::buildGraph(vector<Vertex> vertexs)
	{
		this->vertexs = vertexs;
	}

	template <typename T>
	void JpGraph<T>::BFS(int index)
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

	template <typename T>
	void JpGraph<T>::DFS(int index)
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

	template <typename T>
	void JpGraph<T>::topSort()
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
		sort(vec.begin(), vec.end(), less<int>());
		typedef JpGraph<string>::Vertex  vertex;
		typedef JpGraph<string>::AdjAcent adj;
		vertex v1(0, 0);
		vertex v2(1, 1);
		vertex v3(2, 1);
		vertex v4(3, 2);
		vertex v5(4, 2);
		vertex v6(5, 3);
		vertex v7(6, 2);
		v1.degree = vector<adj>{ adj(1,&v4),adj{ 2,&v2 } };
		v2.degree = vector<adj>{ adj{ 3,&v4 },adj{ 2,&v5 } };
		v3.degree = vector<adj>{ adj{ 5,&v6 },adj{4,&v1} };
		v4.degree = vector<adj>{ adj{ 8,&v6 },adj{ 2,&v3 },adj{2,&v5},adj{ 4,&v7 } };
		v5.degree = vector<adj>{ adj{ 6,&v7 },};
		v6.degree = vector<adj>();
		v7.degree = vector<adj>{ adj{ 1,&v6 } };
		JpGraph<string>graph;
		graph.buildGraph(vector<vertex>{v1, v2, v3, v4, v5, v6, v7});
		graph.topSort();
	}

	inline void testDijkstra()
	{
		std::cout << "testDijkstra :" << std::endl;
		vector<int>vec;
		sort(vec.begin(), vec.end(), less<int>());
		typedef JpGraph<string>::Vertex  vertex;
		typedef JpGraph<string>::AdjAcent adj;
		vertex v1(0, 0);
		vertex v2(1, 1);
		vertex v3(2, 2);
		vertex v4(3, 3);
		vertex v5(4, 1);
		vertex v6(5, 3);
		vertex v7(6, 2);
		v1.degree = vector<adj>{ adj(1,&v4),adj{ 2,&v2 } };
		v2.degree = vector<adj>{ adj{ 3,&v4 },adj{ 2,&v5 } };
		v3.degree = vector<adj>{ adj{ 5,&v6 },adj{ 4,&v1 } };
		v4.degree = vector<adj>{ adj{ 8,&v6 },adj{ 2,&v3 },adj{ 2,&v5 },adj{ 4,&v7 } };
		v5.degree = vector<adj>{ adj{ 6,&v7 }, };
		v6.degree = vector<adj>();
		v7.degree = vector<adj>{ adj{ 1,&v6 } };
		JpGraph<string>graph;
		graph.buildGraph(vector<vertex>{v1, v2, v3, v4, v5, v6, v7});
		graph.lowestCost(v1);


	}

	inline void testDFSAndBFS()
	{
		std::cout << "testDFS :" << std::endl;
		vector<int>vec;
		sort(vec.begin(), vec.end(), less<int>());
		typedef JpGraph<string>::Vertex  vertex;
		typedef JpGraph<string>::AdjAcent adj;
		vertex v1(0, 0);
		vertex v2(1, 1);
		vertex v3(2, 2);
		vertex v4(3, 3);
		vertex v5(4, 1);
		vertex v6(5, 3);
		vertex v7(6, 2);
		v1.degree = vector<adj>{ adj(1,&v4),adj{ 2,&v2 } };
		v2.degree = vector<adj>{ adj{ 3,&v4 },adj{ 2,&v5 } };
		v3.degree = vector<adj>{ adj{ 5,&v6 },adj{ 4,&v1 } };
		v4.degree = vector<adj>{ adj{ 8,&v6 },adj{ 2,&v3 },adj{ 2,&v5 },adj{ 4,&v7 } };
		v5.degree = vector<adj>{ adj{ 6,&v7 }, };
		v6.degree = vector<adj>();
		v7.degree = vector<adj>{ adj{ 1,&v6 } };
		JpGraph<string>graph;
		graph.buildGraph(vector<vertex>{v1, v2, v3, v4, v5, v6, v7});
		graph.DFS(0);
		cout << "test BFS" << endl;
		graph.BFS(0);
	}

}

