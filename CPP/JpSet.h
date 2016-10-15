//2016.3.9��ʼ��д
//�Ҳ��������������ǰ�ƽ��ķ����������
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



