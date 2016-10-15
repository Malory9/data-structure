//2016.3.9开始编写
//找不到解决迭代器往前推进的方法，待解决
#pragma once
#include<initializer_list>
#include"JpAVLTree.h"

namespace CjpSTL
{
	template<typename ComparableT>
	class JpSet
	{
	private:
		JpAVLTree<ComparableT>tree;

	public:
		class const_iterator
		{
			
		private:
			typename JpAVLTree<ComparableT>::NodePtr ptr;

		public:
			ComparableT& operator *()const {
				return ptr->data;

			}

		};



		JpSet() = default;
		JpSet(const std::initializer_list<ComparableT>&lis) :tree(lis){}

		



	};




}



