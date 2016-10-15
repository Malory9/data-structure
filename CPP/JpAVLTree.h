//2016.3.8±‡–¥
// Ï¡∑∂»ªπÃ´µÕ
#pragma once
#include <initializer_list>

namespace CjpSTL
{
	template <typename ComparableT>
	class JpAVLTree
	{
		class Node;
		typedef Node* NodePtr;
		typedef ComparableT value_type;

		friend class JpSet;
	private:
		NodePtr root;

		class Node
		{
			friend class JpAVLTree;
		private:
			NodePtr left;
			NodePtr right;
			int height;
			ComparableT data;
		public:


			explicit Node(const ComparableT& theData) : data(theData), height(0), left(nullptr), right(nullptr)
			{
			}

			Node() = delete;
		};

#pragma region PrivateMethods
		NodePtr insert(const ComparableT& val, NodePtr& node)
		{
			if (node == nullptr)
				node = new Node(val);
			else if (node->data > val)
			{
				insert(val, node->left);
				if (height(node->left) - height(node->right) == 2)
				{
					if (val < node->left->data)
						rotateWithLeftChild(node);
					else
						doubleWithLeftChild(node);
				}
			}
			else if (node->data <= val)
				{
					insert(val, node->right);
					if (height(node->right) - height(node->left) == 2)
					{
						if (val > node->right->data)
							rotateWithRightChild(node);
						else
							doubleWithRightChild(node);
					}
				}
				else; //do nothing

			node->height = max(height(node->left), height(node->right)) + 1;

			return node;
		}
#pragma region Rotate methods
		void rotateWithLeftChild(NodePtr& node)
		{
			NodePtr preToMoveNode = node->left;
			node->left = preToMoveNode->right;
			preToMoveNode->right = node;
			node->height = max(height(node->left), height(node->right)) + 1;
			preToMoveNode->height = max(height(preToMoveNode->left), height(preToMoveNode->right)) + 1;
			node = preToMoveNode;
		}

		void rotateWithRightChild(NodePtr& node)
		{
			NodePtr preToMoveNode = node->right;
			node->right = preToMoveNode->left;
			preToMoveNode->left = node;
			node->height = max(height(node->left), height(node->right)) + 1;
			preToMoveNode->height = max(height(preToMoveNode->left), height(preToMoveNode->right)) + 1;
			node = preToMoveNode;
		}

		void doubleWithLeftChild(NodePtr& node)
		{
			rotateWithRightChild(node->left);
			rotateWithLeftChild(node);
		}

		void doubleWithRightChild(NodePtr& node)
		{
			rotateWithLeftChild(node->right);
			rotateWithRightChild(node);
		}

#pragma endregion

		static int max(int left, int right)
		{
			return left > right ? left : right;
		}

		bool contains(const ComparableT& val, NodePtr& node) const
		{
			if (node == nullptr)
				return false;
			if (node->data > val)
				return contains(val, node->left);
			if (node->data<val)
			               return contains(val, node->right);
			return true;
		}

		NodePtr findMax(const NodePtr& node)
		{
			if (node == nullptr)
				return nullptr;
			if (node->right == nullptr)
				return node;
			else return findMax(node->right);
		}

		NodePtr findMin(const NodePtr& node)
		{
			if (node == nullptr)
				return nullptr;
			if (node->left == nullptr)
				return node;
			else return findMin(node->left);
		}

		void remove(const ComparableT& val, NodePtr& node)
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
#pragma region Travel
		void travelPre(NodePtr root)
		{
			if (root != nullptr)
			{
				std::cout << root->data << " ";
				travelPre(root->left);
				travelPre(root->right);
			}
		}

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


		static int height(const NodePtr& t)
		{
			return t == nullptr ? -1 : t->height;
		}

		void clear(NodePtr node)
		{
			if (node != nullptr)
			{
				clear(node->left);
				clear(node->right);
				delete node;
			}
		}

#pragma endregion


	public:
#pragma region Constrctors and Destrctor
		explicit JpAVLTree(const ComparableT& data) : root(new Node(data))
		{
		}

		JpAVLTree(const std::initializer_list<ComparableT>& lis)
		{
			for (const ComparableT& i : lis)
			{
				this->insert(i);
			}
		}

		JpAVLTree(): root(nullptr)
		{
		}

		~JpAVLTree()
		{
			clear();
		}

#pragma endregion
#pragma region Methods


		void clear()
		{
			clear(root);
		}

		void insert(const ComparableT& val)
		{
			insert(val, root);
		}

		bool contains(const ComparableT& val)
		{
			return contains(val, root);
		}

		void remove(const ComparableT& val)
		{
			remove(val, root);
		}


		NodePtr findMax() const
		{
			return findMax(root);
		}

		NodePtr findMin() const
		{
			return findMin(root);
		}

		enum TravelModEnum
		{
			PreOrder = 1,
			InOrder,
			PostOrder
		};

		void travel(TravelModEnum model)
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

#pragma endregion
	};
}
