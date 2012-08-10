
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

// dfs, for find circle in digraph or undirected graph, return true if found
bool visited[MAXN];
bool visiting[MAXN];
bool dfs(int startNode, bool digraph)
{
	visited[startNode] = true;
	visiting[startNode] = true;
	bool ret = false;
	for (std::vector<char>::iterator i = nodes[startNode].adjs.begin();
	 i != nodes[startNode].adjs.end(); ++i)
	{
		if(visited[*i])
		{
			if(digraph)
			{
				// We don't init visiting in the begining because we always check visited false
				// if visited, then visiting is always valid
				if(visiting[*i])
				{
					ret = true;
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{
				ret = true;
				break;
			}
		}
		if(dfs(*i, digraph))
		{
			ret = true;
			break;
		}
	}
	visiting[startNode] = false;
	return ret;
}

bool haveCircle()
{
	bool totallyVisited[MAXN];
	memset(totallyVisited, 0, sizeof(totallyVisited));
	forn(i, 0, n)
	{
		// consider a graph whose all parts are not connected
		if(!totallyVisited[i])
		{
			memset(visited, 0, sizeof(visited));
			if(dfs(i, false/* or true for digraph */))
				return true;
			forn(j, 0, n)
				totallyVisited[j] |= visited[j];
		}
	}
	return false;
}

// do Dijstla algorithm for the shortest path
// template<typename T>
void moveSmallestFirst(Node* * begin, Node* * end,  bool (*node_less)(const Node* n1, const Node* n2))
{
	if(begin == end || begin+1 == end)
		return; // size is 0 or 1
	Node* * minValuePointer = begin;
	Node*  minValue = *begin;
	for(Node* *p = begin+1; p != end; ++p)
	{
		if(node_less(*p, minValue))
		{
			minValuePointer = p;
			minValue = *p;
		}
	}
	if(minValuePointer == begin)
		return;
	for(Node* *p = minValuePointer; p != begin; --p)
	{
		*p = *(p-1);
	}
	*begin = minValue;
}

void solve()
{
	(*nodes[0]).value = 0;
	Node* nodeMap[MAXN];
	char visited[MAXN] = {0};
	forn(i, 0, n)
		nodeMap[i] = nodes[i];
	forn(i, 0, n)
	{
		Node& node = (*nodes[i]);
		visited[node.index] = 1;
		for (NodeAdjs::iterator it = node.adjs.begin();
		 it != node.adjs.end(); ++it)
		{
			Edge &e = *it;
			if(visited[e.nodeIndex])
				continue;
			Node &adj = (*nodeMap[e.nodeIndex]);
			adj.value = min(adj.value, node.value + e.weight);
		}
		moveSmallestFirst(nodes+i+1, nodes+n, node_cmp);
		forn(j, i+1, n)
		{
			nodeMap[nodes[j]->index] = nodes[j];
		}
	}
}