//2016.3.6第一次重构，此次重构除更改内部实现外，还添加了迭代器
//编写时间： 2016.3.5
//2016.3.20第二次重构，并添加了swap、reverse
//代码仍有冗余，待第二次重构

#pragma once
//上机所需代码是直接写在我自己写的list里的


namespace CjpSTL
{
	template <typename T>
	class JpList
	{
		class iterator;
		class const_iterator;
		class Node;

		typedef unsigned int size_t;
		typedef Node* NodePtr;
		typedef T value_type;
	private:
#pragma region Node
		class Node
		{
			friend class JpList;
		private:
#pragma region Fields
			NodePtr next;
			NodePtr previous;
			T data;

#pragma endregion
		public:
#pragma region Constrctors and Destrctors
			Node();

			explicit Node(const T& theData, NodePtr theNext = nullptr, NodePtr thePre = nullptr);
			~Node() = default;

		};


#pragma endregion

#pragma endregion
#pragma region PrivateMethods


		static void setLink(NodePtr preNode, NodePtr cur, NodePtr nextNode);
		void addSize()
		{
			++quanties;
		}

		void desSize()
		{
			--quanties;
		}

		NodePtr locateIndex(size_t index);

		void initial()
		{
			head = new Node();
			tail = new Node();
			quanties = 0;
			head->next = tail;
			tail->previous = head;
		}

		
#pragma endregion 

#pragma region Fields

		size_t quanties;
		NodePtr head;
		NodePtr tail;
#pragma endregion

	public:


#pragma region Constrctors and Destrctor

		JpList()
		{
			initial();
		}

		JpList(size_t amount, const T& val);

		JpList(const std::initializer_list<T>& lis)
		{
			initial();
			for (const T& i : lis)
			{
				this->push_back(i);
			}
		}

		~JpList()
		{
			clear();
			delete head;
			delete tail;
		}

#pragma endregion

#pragma region Operators and Copy Constrctors


		JpList& operator =(const JpList& rhs);

		JpList(const JpList& rhs)
		{
			head = new Node();
			tail = new Node();

			head->next = tail;
			tail->previous = head;
			for (auto rhsFirstPtr = (rhs.head)->next; rhsFirstPtr->next != nullptr; rhsFirstPtr = rhsFirstPtr->next)
			{
				push_back(rhsFirstPtr->data);
			}
		}


		const T& operator [](size_t index) const
		{
			return locateIndex(index)->data;
		}

		T& operator [](size_t index)
		{
			return locateIndex(index)->data;
		}


		bool operator ==(const JpList<T>& rhs) const
		{
			if (this == &rhs)
				return true;
			else if (this->size() != rhs.size())
				return false;
			else
			{
				auto tempLhs = head->next;
				auto tempRhs = (rhs.head)->next;
				while (tempLhs->next != this->tail)
				{
					if (tempLhs->data == tempRhs->data)
						return true;
					tempLhs = tempLhs->next;
					tempRhs = tempRhs->next;
				}
				return false;
			}
		}

		bool operator !=(const JpList<T>& rhs)
		{
			return !this->operator==(rhs);
		}

#pragma endregion

#pragma region Methods
		void swap(JpList& rhs);

		void reverse() {
			auto tempNode = head;
			while(tempNode!=nullptr)
			{
				auto next = tempNode->next;
				std::swap(tempNode->previous, tempNode->next);
				tempNode = next;

			}
			
			std::swap(head, tail);
			tempNode = head->next;
		
		}
	

		void clear();


		bool contains(const T& val)
		{
			for (auto tempPtr = head; tempPtr->next != nullptr; tempPtr = tempPtr->next)
			{
				if (tempPtr->data == val)
					return true;
			}
			return false;
		}

		void push_back(const T& val)
		{
			auto tempNode = new Node(val);
			setLink(tail->previous, tempNode, tail);


			addSize();
		}
		
		void push_front(const T& val)
		{
			auto tempNode = new Node(val);
			setLink(head, tempNode, head->next);
			addSize();
		}

		NodePtr insert(const T& val)
		{
			auto after = tail->previous;
			NodePtr newNode = new Node(val);
			setLink(after, newNode, tail);
			return newNode;
		}


		iterator insert(const T& val, iterator iter)
		{
			auto tempNode = new Node(val);

			auto theNext = iter.current;
			auto thePre = theNext->previous;
			thePre->next = tempNode;
			tempNode->previous = thePre;

			return iterator(&tempNode);
		}

		size_t size() const
		{
			return quanties;
		}

		bool isEmpty() const
		{
			return head->next == tail;
		}

		iterator erase(size_t index)
		{
			auto tempHead = locateIndex(index);
			auto thePrePtr = tempHead->previous;
			auto theNextPtr = tempHead->next;
			thePrePtr->next = theNextPtr;
			theNextPtr->previous = thePrePtr;
			delete tempHead;
			desSize();
			return theNextPtr;
		}

		iterator erase(iterator iter)
		{
			NodePtr temp = iter.current;
			auto next = temp->next;
			auto pre = temp->previous;
			pre->next = next;
			next->previous = pre;
			delete temp;
			desSize();
			return next;
		}

		iterator erase(iterator beg, iterator end)
		{
			for (auto i = beg; i != end;)
				i = erase(i);
			return end;
		}

		void remove(const T& val)
		{
			auto tempH = head;
			while (tempH->next != nullptr)
			{
				if (*tempH == val)
					tempH = erase(tempH);
				else
					tempH = tempH->next;
			}
		}

		const_iterator begin() const
		{
			return const_iterator(head->next);
		}

		const_iterator end() const
		{
			return const_iterator(tail);
		}

		iterator begin()
		{
			return iterator(head->next);
		}

		iterator end()
		{
			return iterator(tail);
		}
#pragma endregion

		class const_iterator
		{
		protected:
			friend class JpList<T>;

			NodePtr current;

			T& retrieve() const
			{
				if (current == nullptr)
					throw std::exception("it's dereferable");
				else
				return current->data;
			}

			explicit const_iterator(NodePtr newDes) : current(newDes)
			{
			}

		public:


			const_iterator() : current(nullptr)
			{
			}

			const T& operator *() const
			{
				return retrieve();
			}
#pragma region Operators


			const_iterator& operator++()
			{
				current = current->next;
				return *this;
			}

			const_iterator& operator++(int)
			{
				const_iterator theOld = *this;
				current = current->next;
				return theOld;
			}

			bool operator ==(const const_iterator& rhs) const
			{
				return current == rhs.current;
			}

			bool operator !=(const const_iterator& rhs) const
			{
				return current != rhs.current;
			}

			const_iterator operator +(int index)
			{
				auto cur = const_iterator::current;
				for (int i = 0; i < index; ++i)
				{
					cur = cur->next;
				}
				return const_iterator(cur);
			}

#pragma endregion
		};

		class iterator :public const_iterator
		{
		protected:
			friend class JpList;

			explicit iterator(NodePtr newDes) : const_iterator(newDes)
			{
			}

		public:
			iterator() : const_iterator()
			{
			}

			iterator(const iterator& rhs)
			{
				const_iterator::current = rhs.current;
			}

			T& operator *()
			{
				return const_iterator::retrieve();
			}

			iterator operator++()
			{
				const_iterator::current = const_iterator::current->next;
				return *this;
			}

			iterator operator++(int)
			{
				iterator theOld = *this;
				const_iterator::current = const_iterator::current->next;
				return theOld;
			}

			bool operator ==(const iterator& rhs) const
			{
				return const_iterator::current == rhs.current;
			}

			bool operator !=(const iterator& rhs) const
			{
				return const_iterator::current != rhs.current;
			}

			iterator operator +(int index);
		};

		class Solution {
		public:
			NodePtr reverseList(NodePtr head) {
				if (head == nullptr)
					return head;
				NodePtr nextNode = head->next;
				if (nextNode == nullptr)
					return head;

				NodePtr thirdNode = nextNode->next;

				if (thirdNode == nullptr) {
					head->next = nullptr;
					nextNode->next = head;
					return nextNode;
				}
				else {
					head->next = nullptr;
					while (thirdNode != nullptr) {

						nextNode->next = head;
						head = nextNode;
						nextNode = thirdNode;
						thirdNode = thirdNode->next;

					}
					nextNode->next = head;
				}
				return nextNode;
			}
		};


	};

	template <typename T>
	JpList<T>::Node::Node(): next(nullptr), previous(nullptr)
	{
	}

	template <typename T>
	JpList<T>::Node::Node(const T& theData, NodePtr theNext, NodePtr thePre): data(theData), next(theNext), previous(thePre)
	{
	}

	template <typename T>
	void JpList<T>::setLink(NodePtr preNode, NodePtr cur, NodePtr nextNode)
	{
		preNode->next = cur;
		cur->next = nextNode;
		nextNode->previous = cur;
		cur->previous = preNode;
	}

	template <typename T>
	typename JpList<T>::NodePtr JpList<T>::locateIndex(size_t index)
	{
		if (index + 1 > quanties)
			throw new std::exception("out of range,check your index");

		auto tempHead = head;

		for (size_t i = 0; i < index + 1; ++i)
		{
			tempHead = tempHead->next;
		}
		return tempHead;
	}

	template <typename T>
	JpList<T>::JpList(size_t amount, const T& val)
	{
		initial();
		for (size_t i = 0; i < amount; ++i)
			this->push_back(val);
	}

	template <typename T>
	JpList<T>& JpList<T>::operator=(const JpList& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		clear();
		auto tempRhsPtr = (rhs.head)->next;
		while (tempRhsPtr->next != nullptr)
		{
			this->push_back(tempRhsPtr->data);
			tempRhsPtr = tempRhsPtr->next;
		}
		this->quanties = rhs.quanties;
		return *this;
	}

	template <typename T>
	void JpList<T>::swap(JpList& rhs)
	{
		using std::swap;
		swap(head, rhs.head);
		swap(tail, rhs.tail);
		swap(quanties, rhs.quanties);
	}

	template <typename T>
	void JpList<T>::clear()
	{
		auto tempHead = head->next;
		while (tempHead->next != nullptr)
		{
			auto next = tempHead->next;
			delete tempHead;
			tempHead = next;
		}
	}

	template <typename T>
	typename JpList<T>::iterator JpList<T>::iterator::operator+(int index)
	{
		auto cur = const_iterator::current;
		for (int i = 0; i < index; ++i)
		{
			cur = cur->next;
		}
		return iterator(cur);
	}

	template <typename T>
	void swap(JpList<T> lhs, JpList<T> rhs)
	{
		lhs.swap(rhs);
	}








}
inline void testReverse() //双向链表逆转测试数据
{
	std::cout << "testReverse :" << std::endl;
	CjpSTL::JpList<int>lis{ 1,2,3,4,5,6,7,8,9,10 };
	for (const auto& i : lis)
		std::cout << i << " ";
	std::cout << std::endl;
	lis.reverse();
	for (const auto& i : lis)
		std::cout << i << " ";
	std::cout << std::endl;
}


 struct ListNode {
     int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
 };
 //此代码来自我做的leetcode题目，因为以上JpList内部实现是双链表
 //测试单链表逆转
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		ListNode* pre = nullptr;
		while (head != nullptr) {
			ListNode* next = head->next;
			head->next = pre;
			pre = head;
			head = next;

		}
		return pre;
	}
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == nullptr || head->next == nullptr)
			return head;

		ListNode* newList = new ListNode(head->val);
		ListNode* toReturn = newList;
		ListNode* next = head->next;
		while (next != nullptr) {
			if (newList->val == next->val)
				next = next->next;
			else {
				newList->next = new ListNode(next->val);
				newList = newList->next;
				next = next->next;
			}
		}
		return toReturn;

	}
};
