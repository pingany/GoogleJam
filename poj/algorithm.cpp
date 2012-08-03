
template<typename T>
T maxn(T* start, T*end)
{
	ASSERT(start != end);
	T result = *start;
	++start;
	while(start != end)
	{
		if(*start > result)
			result = *start;
		start++;
	}
	return result;
}

template<typename T>
T sumn(T*start, T*end)
{
	T result = T(0);
	while(start != end)
	{
		result += *start;
		start++;
	}
	return result;
}
