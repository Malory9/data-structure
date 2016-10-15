#include <functional>
#include<iostream>
template<typename Iter>
void JpQsort(Iter beg, Iter end)
{

	JpQsortImple<Iter, decltype(*beg)>(beg, end);
}

template<typename Iter,typename Func>
void JpQsort(Iter beg,Iter end,Func func = Func())
{
	JpQsortImple<Iter,decltype(*beg)>(beg, end, func);


}
template<typename Iter, typename Obj, typename Func = std::less<Obj>>
void JpQsortImple(Iter beg, Iter end, Func func = Func())
{

	if (beg<end)
	{
		Iter low = beg;
		Iter high = --end;
		typename std::remove_reference<decltype(*low)>::type value = *low;
		while (low < high)
		{
			while (low < high&&!func(*high, value))
				--high;
			*low = *high;
			while (low < high&&func(*low, value))
				++low;
			*high = *low;
		}
		*low = value;
	
		JpQsortImple<Iter, decltype(*beg)>(beg, low, func);
		JpQsortImple<Iter, decltype(*beg)>(low + 1, end, func);

	}


}
