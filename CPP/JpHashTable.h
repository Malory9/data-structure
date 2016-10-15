//±‡–¥”Î2016.3.15
#pragma once
#include<vector>
#include<list>
#include<memory>
#include<algorithm>
namespace CjpSTL
{
	using namespace std;
	template<typename T>
	class JpHashTable
	{
	public:
		typedef vector<list<T>> ContentType;
		shared_ptr<ContentType> lists;
		int getHash(const T& x);


		JpHashTable():lists(make_shared<ContentType>())
		{
			lists->resize(10);
		}

		void insert(const T& val);

		void remove(const T&val);

		void clear();

		void rehash();

		bool contains(const T&val);

		int hash(const string& str);
	};

	template <typename T>
	int JpHashTable<T>::getHash(const T& x)
	{
		int hashVal = hash(x);
		hashVal %= lists->count();
		if (hashVal < 0)
			hashVal += lists->count();
		return hashVal;
	}

	template <typename T>
	void JpHashTable<T>::insert(const T& val)
	{
		int index = getHash(val);
		auto& list = (*lists)[index];
		list.push_front(val);
	}

	template <typename T>
	void JpHashTable<T>::remove(const T& val)
	{
	}

	template <typename T>
	void JpHashTable<T>::clear()
	{
	}

	template <typename T>
	void JpHashTable<T>::rehash()
	{
	}

	template <typename T>
bool JpHashTable<T>::contains(const T& val)
	{
		int index = getHash(val);
		auto list = (*lists)[index];
		cout << list.count();

		for (auto i = (*lists).begin(); i != (*lists).end();++i)
		{
			cout << i->count() << " ";
		}

		return list.end() != find(list.begin(), list.end(), val);
	}

	template <typename T>
	int JpHashTable<T>::hash(const string& str)
	{
		int hashVal = 0;
		for (int i = 0; i < str.length(); ++i)
			hashVal = 37 * hashVal + str[i];
		hashVal %= lists->count();
		
		if (hashVal < 0)
			hashVal += lists->count();
		return hashVal;
	}
}
