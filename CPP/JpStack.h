//编写时间 2016.3.4
//2016.3.5第一次重构
//2016.3.6添加了前缀表达式及其4则运算
//2016.3.10添加了超界时调整大小的机制
#pragma once
#include<exception>
#include <map>

namespace CjpSTL {
	using namespace std;

	template<typename T>
	class JpStack
	{
		typedef unsigned int size_t;
		typedef T value_type;
		enum {DEFAULTCAP = 100};
	private:
#pragma region Fields
		size_t capacity;
		int topIndex;
		T* arr;
		void resize()
		{
			if(this->size()==capacity)
			{
				capacity *= 2;
				T* newArr = new T[capacity];
				for (int i = 0; i < size(); ++i)
					newArr[i] = arr[i];
				delete[]arr;
				arr = newArr;
			}

		}

#pragma endregion


	public:
#pragma region Constrctors
		JpStack():capacity(DEFAULTCAP),topIndex(-1),arr(new T[capacity]){}
	


#pragma endregion

#pragma region Methods
		bool isEmpty()const
		{
			if (topIndex == -1)
				return true;
			return false;
		}

		size_t size()const
		{
			return topIndex + 1;
		}

		 const T& top()
		{
			return arr[topIndex];
		}

		const T& pop_back()
		{
			if(topIndex<0)
			{
				throw new exception("out of range");
			}
			return arr[topIndex--];
		}
		void push_back(const T& val)
		{
			++topIndex;
			arr[topIndex] = val;
			resize();

		}
		
		


#pragma endregion





	};


	inline string toPreFix(string str)
	{
		string result = "";
		const static string operatorArr = { '+','-','*','/' };
		static map<char, int>priorties{ { '+',1 },{ '-',1 },{ '*',2 },{ '/',2 } };
		JpStack<char>stkOpe;
		JpStack<char>stkNum;

		static auto lambdaFunc = [&](char val)->bool
		{
			for (auto i = 0; i < 4; ++i)
			{
				if (val == operatorArr[i])
					return true;
			}
			return false;

		};

		for (int i = str.length() - 1; i >= 0; --i)
		{
			auto tempChar = str[i];

			if (tempChar >= '0'&&tempChar <= '9')
			{
				stkNum.push_back(tempChar);
			}
			else if (lambdaFunc(tempChar))
			{

				if (stkOpe.isEmpty() || stkOpe.top() == ')') {
					stkOpe.push_back(tempChar);
				}

				else
				{
					while (priorties[tempChar] <= priorties[stkOpe.top()])
					{
						stkNum.push_back(stkOpe.pop_back());
					}
					stkOpe.push_back(tempChar);
				}
			}
			else if (tempChar == ')')
				stkOpe.push_back(')');
			else if (tempChar == '(')
			{
				while (stkOpe.top() != ')')
					stkNum.push_back(stkOpe.pop_back());
				stkOpe.pop_back();
			}



		}
		while (!stkOpe.isEmpty())
		{
			stkNum.push_back(stkOpe.pop_back());
		}
		while (!stkNum.isEmpty())
		{
			result += stkNum.pop_back();
		}

		return result;

	}


	inline int calculate(string str)
	{
		static auto calculateHelper = [](char ope, int left, int right)->int
		{
			{
				int tempRight = right;

				int tempLeft = left;

				switch (ope) {
				case '+':return tempLeft + tempRight;
				case '-': return tempLeft - tempRight;
				case '*': return tempLeft*tempRight;
				case '/': return tempLeft / tempRight;
				default: throw new exception("error");
				}
			}

		};
		static JpStack<int>stk;
		for (int i = str.length() - 1; i >= 0; --i)
		{
			int tempVal = str[i];
			if (tempVal >= '0'&&tempVal <= '9')
				stk.push_back(tempVal - 48);
			else {
				int left = stk.pop_back();
				int right = stk.pop_back();

				stk.push_back(calculateHelper(tempVal, left, right));

			}


		}

		return stk.top();
	}


}
