//2017.10.8
//第一次添加trie树
//代码仅作参考和记录，就不进行h和cpp的分割了
#pragma once
#include<string>
#include<unordered_set>
#include <unordered_map>
using namespace std;

namespace CjpSTL
{
	class Trie
	{
		struct Node;
		using NodePtr = Node*;

		struct Node
		{
			unordered_map<char, NodePtr> dict;

			char ch;
			bool hasVal;
			int count;
			Node(char _ch) :ch(_ch), dict(), count(1), hasVal(false) {}

		};

	public:
		Trie();

		void add(const string& str) const
		{
			auto cur = root;
			for (auto ch : str)
			{
				auto des = cur->dict.find(ch);
				if (des != cur->dict.end())
				{
					++cur->dict[ch]->count;
					cur = cur->dict[ch];
				}
				else
				{
					cur->dict[ch] = new Node(ch);
					cur = cur->dict[ch];
				}

			}
			cur->hasVal = true;
		}
		bool find(const string& str)const
		{
			auto cur = root;
			for (auto ch : str)
			{
				auto des = cur->dict.find(ch);
				if (des != cur->dict.end())
				{

					cur = cur->dict[ch];
					++cur->count;
				}
				else
				{
					return false;
				}

			}
			return cur->hasVal;

		}
		void erase(const string& str)const
		{
			auto cur = root;
			auto pre = root;
			for (auto ch : str)
			{
				auto des = cur->dict.find(ch);
				if (des != cur->dict.end())
				{

					pre = cur;
					cur = cur->dict[ch];
					--cur->count;
				}
				else
				{
					break;
				}

			}
			cur->hasVal = false;


		}

		~Trie();
	private:
		NodePtr root = new Node('\0');

	};

}