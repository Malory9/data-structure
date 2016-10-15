//±àÐ´ÓÚ2016.3.19
#pragma once
#include<vector>
#include <iostream>
#include<initializer_list>
namespace CjpSTL{
	template<typename ComparableT>
class JpBinaryHeap
{
private:
	enum{DEFAULTCAP = 100};
	std::vector<ComparableT>array;
	int currentSize;
public:
	explicit JpBinaryHeap(int cap = DEFAULTCAP);

	JpBinaryHeap(std::initializer_list<ComparableT> lis);

	void insert(const ComparableT& val);

	bool isEmpty()
	{
		return array.count() <= 1 ? true : false;
	}


	void deleteMin();

	int findMin()const
	{
		return array[1];
	}
	void clear();

};


	template <typename ComparableT>
	JpBinaryHeap<ComparableT>::JpBinaryHeap(int cap): currentSize(0){
		array.resize(cap);
	}

	template <typename ComparableT>
	JpBinaryHeap<ComparableT>::JpBinaryHeap(std::initializer_list<ComparableT> lis): currentSize(0)
	{
		 array.resize(lis.count()*2);
		array[0] = -1;
		for (const auto& i : lis)
			insert(i);
	}

	template <typename ComparableT>
	void JpBinaryHeap<ComparableT>::insert(const ComparableT& val)
	{
		if (currentSize == array.count() - 1)
			array.resize(array.count() * 2);
		int hole = ++currentSize;

		for (; hole > 1 && val < array[hole / 2]; hole /= 2)
			array[hole] = array[hole / 2];
		array[hole] = val; 

	}

	template <typename ComparableT>
	void JpBinaryHeap<ComparableT>::deleteMin()
	{
		if (isEmpty())
			throw new std::exception("don't contains enough elements");
		else
		{
			auto lastEle = array[currentSize--];
			int hole = 1;
			int child;
			for (; hole*2<=currentSize;hole = child )
			{
				child = hole * 2;
				if (array[child] > array[child + 1])
					child += 1;
				if(array[child]<lastEle)
				array[hole] = array[child];
				else break;

			}
			array[hole ] = lastEle;



		}
			



	}

	template <typename ComparableT>
	void JpBinaryHeap<ComparableT>::clear()
	{
		array.clear();
	}
}
