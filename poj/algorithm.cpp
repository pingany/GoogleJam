
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

// Make a graph to a tree with startNode as root
void toRootTree(int startNode)
{
	Node &node = nodes[startNode];
	for (Node::iterator i = node.begin(); i != node.end(); ++i)
	{
		Node & child = nodes[*i];
		child.erase(find(child.begin(), child.end(), startNode));
	}
	for (Node::iterator i = node.begin(); i != node.end(); ++i)
	{
		toRootTree(*i);
	}
}
