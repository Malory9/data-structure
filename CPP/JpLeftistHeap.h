//±‡–¥”Î2016.4.7

#pragma once
namespace CjpSTL {
	template<typename ComparableT>
	class JpLeftistHeap
	{
		class Node;
		typedef Node* NodePtr;
	private:
		class Node
		{
		public:
			ComparableT data;
			NodePtr left;
			NodePtr right;
			int npl;

			explicit Node(const ComparableT& newData, NodePtr newLeft = nullptr, NodePtr newRight = nullptr,int newNpl = 0 );

		};



	public:
		JpLeftistHeap();
		JpLeftistHeap(const JpLeftistHeap& rhs);
		~JpLeftistHeap();


		const JpLeftistHeap & operator = (const JpLeftistHeap& rhs);

		bool isEmpty()const;
		const ComparableT& findMin()const;
		
		void insert(const ComparableT& val);
		void deleteMin();

		void clear();

		void Merge(JpLeftistHeap& rhs);

	};

	template <typename ComparableT>
	JpLeftistHeap<ComparableT>::Node::Node(const ComparableT& newData, NodePtr newLeft, NodePtr newRight int newNpl):
		data(newData),left(newLeft),right(newRight),npl(newNpl)
	{
	}
}
