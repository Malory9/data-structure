#pragma once
#include<functional>
#include<vector>
template<typename T,typename Filter>inline
std::vector<T> filter(std::vector<T>collection, Filter& predicate)
{
	std::vector<T>result;
	for (auto& i : collection)
		if (predicate(i))
			result.emplace_back(i);

	return result;
}
template<typename T, typename ProcessFunc>inline
void process(std::vector<T>&collection, ProcessFunc& processor)
{
	for (auto& i : collection)
		processor(i);
}
