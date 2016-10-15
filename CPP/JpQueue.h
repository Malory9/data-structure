//编写时间： 2016.3.7
//queues似乎不需要迭代器
//待重构
//c++queue内部实现为deque
#pragma once
#include<initializer_list>
#include<exception>
namespace CjpSTL
{
	template<typename T>
	class JpQueue
	{
		

		class Node;
		typedef Node* NodePtr;
		typedef unsigned int size_t;
		typedef T value_type;
	private:
		class Node
		{
			friend class JpQueue;
		private:
			NodePtr next;
			NodePtr previous;
			T data;

		public:
			Node() :data(0), next(nullptr), previous(nullptr) {}
			Node(const T& newData):data(newData),next(nullptr),previous(nullptr){}


		};
		size_t theSize =0;
		NodePtr head;
		NodePtr tail;
		
		void initial()
		{
			head = new Node;
			tail = new Node;
			head->next = tail;
			tail->previous = head;

		}

		

	public:
		JpQueue()
		{
			initial();
		}

		JpQueue(std::initializer_list<T>lis)
		{
			initial();
			for (const T& i : lis)
				this->push_back(i);
		}
		~JpQueue()
		{
			clear();
			delete head;
			delete tail;
		}

		void push_back(const T& val){
			{
				auto tempPre = tail->previous;
				auto tempNode = new Node(val);
				tempNode->next = tail;
				tempNode->previous = tempPre;
				tail->previous = tempNode;
				tempPre->next = tempNode;
				++theSize;
			} }

		T pop_front()
		{if(head->next==tail)
		{
			throw new std::exception("empty queue");
		}
		else {

			auto preToDelete = head->next;
			auto popData = preToDelete->data;

			auto newNext = preToDelete->next;
			head->next = newNext;
			newNext->previous = head;
			delete preToDelete;
			return popData;
		}
		}

		T &back()const
		{
			if (tail->previous == head)
				throw new std::exception("empty queue");
			else
			return (tail->previous)->data;
		}

		T &front()const
		{
			if (head->next == tail)
				throw new std::exception("empty queue");
			return (head->next)->data;
		}

		size_t size()const
		{
			return theSize;
		}

		void clear()
		{
			auto tempHead = head->next;
			while (tempHead != tail)
			{
				auto deletePtr = tempHead;
				tempHead = tempHead->next;
				delete deletePtr;

			}
		}

	};




}