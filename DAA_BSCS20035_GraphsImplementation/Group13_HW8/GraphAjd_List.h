#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<unordered_map>
using namespace std;

//BSCS20035
//Space Complexity O(V+E) 
class GraphAjd_List
{
	vector<list<int>> m;
	vector<int> cnn;
	bool isdirected;

	void BFSExplore(int source, vector<int>& parent, vector<bool>& isvisited)
	{
		queue<int> Q;
		int current_v;

		Q.push(source);
		isvisited[source] = true;

		while (!Q.empty())
		{
			current_v = Q.front();

			Q.pop();
			for (auto itr : m[current_v])
			{
				if (isvisited[itr] == false)
				{
					isvisited[itr] = true;
					parent[itr] = current_v;
					Q.push(itr);
				}
			}
		}
	}

	void DFSExplore(int source, vector<bool>& visited, vector<int>& parents, vector<int>& starting_time, vector<int>& ending_time, vector<int>& connected_components, int current_connected_component, int& clock)
	{
		visited[source] = true;
		starting_time[source] = clock++;
		connected_components[source] = current_connected_component;

		for (auto itr : m[source])
		{
			if (visited[itr] == false)
			{
				parents[itr] = source;
				DFSExplore(itr, visited, parents, starting_time, ending_time, connected_components, current_connected_component, clock);
			}
		}

		ending_time[source] = clock++;
	}

	void DFS_sort(int source, vector<bool>& visited, vector<int>& sort, vector<int>& starting_time, vector<int>& ending_time, int& clock)
	{
		visited[source] = true;
		starting_time[source] = clock++;
		for (auto itr : m[source])
		{
			if (visited[itr] == false)
			{
				DFS_sort(itr, visited, sort, starting_time, ending_time, clock);
			}
		}

		sort.push_back(source);
		ending_time[source] = clock++;
	}

	bool DFS_dag(int source, vector<int>& visited)
	{
		visited[source] = 0;

		for (auto itr : m[source])
		{
			if (visited[itr] == 0)
				return false;
			else if (visited[itr] == -1 && DFS_dag(itr, visited) == false)
				return false;
		}

		visited[source] = 1;
		return true;

	}

	void find_path(int destination, vector<int>parent, int iterator, vector<int>& res)
	{
		if (iterator == -1)
		{
			res.push_back(-1);
			return;
		}
		if (iterator == destination)
		{
			res.push_back(iterator);
			return;
		}
		find_path(destination, parent, parent[iterator], res);
		res.push_back(iterator);
	}

public:
	GraphAjd_List(int size, bool directed = false)
	{

		isdirected = directed;
		m.resize(size);
		cnn.resize(size, -1);
	}

	void addedge(int u, int v)
	{
		if (u >= m.size() || v >= m.size() || u == v)
			return;

		for (auto itr : m[u])
		{
			if (itr == v)
				return;
		}

		m[u].push_back(v);

		if (!isdirected)
			m[v].push_back(u);
	}

	void deleteedge(int u, int v)
	{
		if (u >= m.size() || v >= m.size() || u == v)
			return;

		for (auto itr = m[u].begin(); itr != m[u].end(); itr++)
		{
			if (*(itr) == v)
			{
				m[u].erase(itr);
				break;
			}
		}



		if (!isdirected)
		{
			for (auto itr = m[v].begin(); itr != m[v].end(); itr++)
			{
				if (*(itr) == u)
				{
					m[v].erase(itr);
					break;
				}
			}
		}
	}

	vector<pair<int, int>> all_edges()
	{
		vector<pair<int, int>> edges;
		pair<int, int> p;
		for (int i = 0; i < m.size(); i++)
		{
			p.first = i;
			for (auto itr : m[i])
			{
				p.second = itr;
				edges.push_back(p);
			}

		}

		return edges;
	}

	vector<int> list_neighbours(int source)
	{
		vector<int> edges;

		for (auto itr : m[source])
		{
			edges.push_back(itr);
		}

		return edges;
	}

	void BFS(vector<int>& parents)
	{
		vector<bool> isvisited(m.size(), 0);
		parents.resize(m.size(), -1);

		for (int i = 0; i < m.size(); i++)
		{
			if (isvisited[i] == false)
				BFSExplore(i, parents, isvisited);
		}
	}

	void DFS(vector<int>& parents, vector<int>& starting_time, vector<int>& ending_time, vector<int>& connected_components)
	{
		parents.resize(m.size(), -1);
		starting_time.resize(m.size(), -1);
		ending_time.resize(m.size(), -1);
		connected_components.resize(m.size(), -1);

		vector<bool>visited(m.size(), false);

		int clock = 1;
		int ccnum = 1;
		for (int i = 0; i < m.size(); i++)
		{
			if (visited[i] == false)
			{
				DFSExplore(i, visited, parents, starting_time, ending_time, connected_components, ccnum, clock);
				ccnum++;
				clock = 1;
			}
		}
	}

	vector<int> BFSPath(int source, int destination)
	{
		vector<int> parents(m.size(), -1);
		vector<bool> visited(m.size(), false);

		BFSExplore(source, parents, visited);

		vector<int> res;

		find_path(source, parents, destination, res);
		if (res.front() == -1)
			res.clear();
		return res;
	}

	vector<int> DFSPath(int source, int destination)
	{
		vector<int> parents(m.size(), -1);
		vector<int> starting_time(m.size(), -1);
		vector<int> ending_time(m.size(), -1);
		vector<int> connected_components(m.size(), -1);
		vector<bool> visited(m.size(), false);
		int clock = 1;
		int ccnum = 1;

		DFSExplore(source, visited, parents, starting_time, ending_time, connected_components, ccnum, clock);

		vector<int> res;

		if (connected_components[source] != connected_components[destination])
			return res;

		find_path(source, parents, destination, res);
		return res;

	}

	void print_graph()
	{

		for (int i = 0; i < m.size(); i++)
		{
			cout << i << ": ";
			for (auto t : m[i])
			{
				cout << t << " ";
			}
			cout << endl;
		}
	}

	bool IsGraph_Directed()
	{
		return isdirected;
	}

	//hw8

	vector<list<int>> transpose()
	{
		vector<list<int>> T(m.size());
		for (int i = 0; i < m.size(); i++)
		{
			for (auto itr : m[i])
			{
				T[itr].push_back(i);
			}
		}

		return T;
	}

	vector<list<int>> inverse()
	{

		vector<list<int>> I(m.size());
		vector<unordered_map<int, int>> check(m.size());

		for (int i = 0; i < m.size(); i++)
		{
			for (auto itr : m[i])
			{
				check[i].insert({ itr, itr });
			}
		}


		for (int i = 0; i < m.size(); i++)
		{
			for (int j = 0; j < m.size(); j++)
			{
				if (i == j)
					continue;

				if (check[i].find(j) == check[i].end())
					I[i].push_back(j);
			}
		}

		return I;
	}

	bool is_graphdag()
	{
		vector<int> visited(m.size(), -1);

		for (int i = 0; i < m.size(); i++)
		{
			if (visited[i] == -1)
			{
				if (!DFS_dag(i, visited))
					return false;
			}
		}

		return true;
	}

	vector<int> find_topological_order()
	{
		vector<int> sort;
		vector<bool> visited(m.size(), false);
		vector<int> starting_time(m.size(), -1);
		vector<int> ending_time(m.size(), -1);
		int clock = 0;

		for (int i = 0; i < m.size(); i++)
		{
			if (visited[i] == false)
				DFS_sort(i, visited, sort, starting_time, ending_time, clock);
		}

		reverse(sort.begin(), sort.end());				//ending time will be in descending order because of topological ordering 
		return sort;

	}

	void assign_cnn()
	{
		vector<bool> visited(m.size(), false);
		vector<int> starting_time(m.size(), -1);
		vector<int> ending_time(m.size(), -1);
		vector<int> parents(m.size(), -1);
		int clock = 1;
		int ccnum = 1;

		for (int i = 0; i < m.size(); i++)
		{
			if (visited[i] == false)
			{
				DFSExplore(i, visited, parents, starting_time, ending_time, cnn, ccnum, clock);
				ccnum++;
			}
		}
	}

	int get_cnn(int vertex)
	{
		if (vertex >= m.size())
			return -1;
		return cnn[vertex];
	}
};

