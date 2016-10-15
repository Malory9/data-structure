//编写时间：2016.3.7
//尚需实现remove功能.
//以及前缀和后缀表达式向树的转换
//2016.3.7完成remove及printAll
//但是对于树的编写仍不熟练，需多加练习
//2016.3.28
//添加了拷贝构造函数以及equals方法
//添加了swap
//应考虑怎么样实现迭代器
#pragma once
#include<initializer_list>

namespace CjpSTL
{
	template <typename ComparableT>
	class JpBinarySearchTree
	{
		class Node;
		typedef Node* NodePtr;
		typedef ComparableT value_type;
	private:
		NodePtr root;

		class Node
		{
			friend class JpBinarySearchTree;
		private:
			NodePtr left;
			NodePtr right;
			ComparableT data;
		public:
			

			explicit Node(const ComparableT& theData, NodePtr theLeft = nullptr, NodePtr theRight = nullptr): data(theData), left(theLeft), right(theRight)
			{
			}

			Node() = delete;
		};

#pragma region PrivateMethods
		void insert(const ComparableT& val, NodePtr& node);


		bool contains(const ComparableT& val, NodePtr& node) const;

		NodePtr findMax(const NodePtr& node);

		NodePtr findMin(const NodePtr& node);

		void remove(const ComparableT& val, NodePtr& node);

		static bool equals(NodePtr nodeLeft, NodePtr nodeRight);
		bool equals(NodePtr obj) const;;

	

	

		void clear(NodePtr node);

		NodePtr clone(const NodePtr node);
#pragma region Travel
		void travelPre(NodePtr root);

		void travelInorder(NodePtr root)
		{
			if (root != nullptr)
			{
				travelInorder(root->left);
				std::cout << root->data << " ";
				travelInorder(root->right);
			}
		}

		void travelPost(NodePtr root)
		{
			if (root != nullptr)
			{
				travelPost(root->left);
				travelPost(root->right);
				std::cout << root->data << " ";
			}
		}
#pragma endregion
#pragma endregion


	public:
		enum TravelModEnum
		{
			PreOrder = 1,
			InOrder,
			PostOrder
		};
#pragma region Constrctors Destrctor and Operator
		explicit JpBinarySearchTree(const ComparableT& data): root(new Node(data))
		{
		}

		JpBinarySearchTree(const std::initializer_list<ComparableT>& lis);

		~JpBinarySearchTree();

		JpBinarySearchTree(const JpBinarySearchTree& obj);

		JpBinarySearchTree& operator ==(const JpBinarySearchTree& obj);

		JpBinarySearchTree& operator =(const JpBinarySearchTree& obj);

#pragma endregion
#pragma region Methods
		void swap(JpBinarySearchTree obj);

		bool equals(const JpBinarySearchTree& obj) const;

		void clear();

		void insert(const ComparableT& val);

		bool contains(const ComparableT& val);

		void remove(const ComparableT& val);

		void travel(TravelModEnum model);
		NodePtr findMax() const;

		NodePtr findMin() const
		{
			return findMin(root);
		}
#pragma endregion
	};


	template <typename ComparableT>
	void JpBinarySearchTree<ComparableT>::insert(const ComparableT& val, NodePtr& node)
	{
		if (node == nullptr)
			node = new Node(val);
		else if (node->data > val)
			insert(val, node->left);
		else if (node->data < val)
			insert(val, node->right);
	}

	template <typename ComparableT>
	bool JpBinarySearchTree<ComparableT>::contains(const ComparableT& val, NodePtr& node) const
	{
		if (node == nullptr)
			return false;
		if (node->data > val)
			return contains(val, node->left);
		if (node->data < val)
			return contains(val, node->right);
		return true;
	}

	template <typename ComparableT>
	typename JpBinarySearchTree<ComparableT>::NodePtr JpBinarySearchTree<ComparableT>::findMax(const NodePtr& node)
	{
		if (node == nullptr)
			return nullptr;
		if (node->right == nullptr)
			return node;
		else return findMax(node->right);
	}

	template <typename ComparableT>
	typename JpBinarySearchTree<ComparableT>::NodePtr JpBinarySearchTree<ComparableT>::findMin(const NodePtr& node)
	{
		if (node == nullptr)
			return nullptr;
		if (node->left == nullptr)
			return node;
		else return findMin(node->left);
	}

	template <typename ComparableT>
	void JpBinarySearchTree<ComparableT>::remove(const ComparableT& val, NodePtr& node)
	{
		if (node == nullptr)
			return;
		if (val > node->data)
			remove(val, node->right);
		else if (val < node->data)
			remove(val, node->left);
		else if (node->left != nullptr && node->right != nullptr)
		{
			node->data = findMin(node->right)->data;
			remove(node->data, node->right);
		}
		else
		{
			NodePtr tempNode = node;
			node = (node->left != nullptr) ? node->left : node->right;
			delete tempNode;
		}
	}

	template <typename ComparableT>
	bool JpBinarySearchTree<ComparableT>::equals(NodePtr nodeLeft, NodePtr nodeRight)
	{
		if (!(nodeLeft == nullptr && nodeRight == nullptr))

			return nodeLeft->data == nodeRight->data ? true : false;


		return false;
	}

	template <typename ComparableT>
	bool JpBinarySearchTree<ComparableT>::equals(NodePtr obj) const
	{
		if (!equals(root, obj))
			return false;
		equals(root->left, obj->left);
		equals(root->right, obj->right);
		return true;
	}

	template <typename ComparableT>
	void JpBinarySearchTree<ComparableT>::travel(TravelModEnum model)
	{
		switch (model)
		{
		case PreOrder:
			travelPre(root);
			break;
		case InOrder:
			travelInorder(root);
			break;
		case PostOrder:
			travelPost(root);
			break;
		default: break;
		}
	}


	template <typename ComparableT>
	void JpBinarySearchTree<ComparableT>::clear(NodePtr node)
	{
		if (node != nullptr)
		{
			
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

	template <typename ComparableT>
	typename JpBinarySearchTree<ComparableT>::NodePtr JpBinarySearchTree<ComparableT>::clone(const NodePtr node)
	{
		if (node == nullptr)
			return nullptr;
		else return new Node(node->data, clone(node->left), clone(node->right));
	}

	template <typename ComparableT>
	void JpBinarySearchTree<ComparableT>::travelPre(NodePtr root)
	{
		if (root != nullptr)
		{
			std::cout << root->data << " ";
			travelPre(root->left);
			travelPre(root->right);
		}
	}

	template <typename ComparableT>
	JpBinarySearchTree<ComparableT>::JpBinarySearchTree(const std::initializer_list<ComparableT>& lis)
	{
		for (const ComparableT& i : lis)
			this->insert(i);
	}

	template <typename ComparableT>
	JpBinarySearchTree<ComparableT>::~JpBinarySearchTree()
	{
		clear();
	}

	template <typename ComparableT>
	JpBinarySearchTree<ComparableT>::JpBinarySearchTree(const JpBinarySearchTree& obj)
	{
		NodePtr temp = obj.root;
		root = clone(obj.root);
	}

	template <typename ComparableT>
	JpBinarySearchTree<ComparableT>& JpBinarySearchTree<ComparableT>::operator==(const JpBinarySearchTree& obj)
	{
		return this->equals(obj);
	}

	template <typename ComparableT>
	JpBinarySearchTree<ComparableT>& JpBinarySearchTree<ComparableT>::operator=(const JpBinarySearchTree& obj)
	{
		if (this == &obj)
			return *this;


		clear(root);
		clone(root);
		return *this;
	}

	template <typename ComparableT>
	void JpBinarySearchTree<ComparableT>::swap(JpBinarySearchTree obj)
	{
		using std::swap;
		swap(root, obj.root);
	}

	template <typename ComparableT>
	bool JpBinarySearchTree<ComparableT>::equals(const JpBinarySearchTree& obj) const
	{
		return equals(obj.root);
	}

	template <typename ComparableT>
	void JpBinarySearchTree<ComparableT>::clear()
	{
		clear(root);
	}

	template <typename ComparableT>
	void JpBinarySearchTree<ComparableT>::insert(const ComparableT& val)
	{
		insert(val, root);
	}

	template <typename ComparableT>
	bool JpBinarySearchTree<ComparableT>::contains(const ComparableT& val)
	{
		return contains(val, root);
	}

	template <typename ComparableT>
	void JpBinarySearchTree<ComparableT>::remove(const ComparableT& val)
	{
		remove(val, root);
	}


	template <typename ComparableT>
	typename JpBinarySearchTree<ComparableT>::NodePtr JpBinarySearchTree<ComparableT>::findMax() const
	{
		return findMax(root);
	}
	template <typename T>
	void swap(CjpSTL::JpBinarySearchTree<T>& lhs, CjpSTL::JpBinarySearchTree<T>& rhs)
	{
		lhs.swap(rhs);
	}

	

}

inline void testTravel() //测试代码，同时测试了遍历与二叉搜索树的建立
{
	std::cout << "testTravel :" << std::endl;
	CjpSTL::JpBinarySearchTree<int>tree{ 1,4,5,2,3 };
	tree.travel(CjpSTL::JpBinarySearchTree<int>::PreOrder);
	std::cout << std::endl;
	tree.travel(CjpSTL::JpBinarySearchTree<int>::InOrder);
	std::cout << std::endl;
	tree.travel(CjpSTL::JpBinarySearchTree<int>::PostOrder);
	std::cout << std::endl;




}

