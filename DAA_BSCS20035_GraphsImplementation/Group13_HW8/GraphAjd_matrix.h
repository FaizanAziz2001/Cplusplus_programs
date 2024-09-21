#pragma once
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

//BSCS20035
//Space Complexity = O(V^2)

class GraphAjd_matrix
{
	vector<vector<int>> m;
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
			for (int i = current_v, j = 0; j < m.size(); j++)
			{
				if (m[i][j] != 0 && isvisited[j] == false)
				{
					isvisited[j] = true;
					parent[j] = i;
					Q.push(j);
				}
			}
		}
	}

	void DFSExplore(int source, vector<bool>& visited, vector<int>& parents, vector<int>& starting_time, vector<int>& ending_time, vector<int>& connected_components, int current_connected_component, int& clock)
	{
		visited[source] = true;
		starting_time[source] = clock++;
		connected_components[source] = current_connected_component;

		for (int i = source, j = 0; j < m.size(); j++)
		{
			if (m[i][j] == 1 && visited[j] == false)
			{
				parents[j] = i;
				DFSExplore(j, visited, parents, starting_time, ending_time, connected_components, current_connected_component, clock);
			}
		}

		ending_time[source] = clock++;
	}

	void DFS_sort(int source, vector<bool>& visited, vector<int>& sort, vector<int>& starting_time, vector<int>& ending_time, int& clock)
	{
		visited[source] = true;
		starting_time[source] = clock++;
		for (int i = source, j = 0; j < m.size(); j++)
		{
			if (m[i][j] == 1 && visited[j] == false)
			{
				DFS_sort(j, visited, sort, starting_time, ending_time, clock);
			}
		}

		sort.push_back(source);
		ending_time[source] = clock++;
	}

	bool DFS_dag(int source, vector<int>& visited)
	{
		visited[source] = 0;

		for (int i = source, j = 0; j < m.size(); j++)
		{
			if (m[i][j] == 1 && visited[j] == 0)
				return false;
			else if (m[i][j] == 1 && visited[j] == -1 && DFS_dag(j, visited) == false)
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

	GraphAjd_matrix(int size, bool direction = false)
	{
		isdirected = direction;

		m.resize(size);
		cnn.resize(size, -1);
		for (int i = 0; i < size; i++)
		{
			m[i].resize(size);
			for (int j = 0; j < size; j++)
			{
				m[i][j] = 0;
			}
		}
	}

	void addedge(int u, int v)
	{
		if (u >= m.size() || v >= m.size())
			return;

		if (u == v)
			return;

		if (m[u][v] != 1)
			m[u][v] = 1;

		if (!isdirected && m[v][u] != 1)
			m[v][u] = 1;
	}

	void deleteedge(int u, int v)
	{
		if (u >= m.size() || v >= m.size())
			return;

		if (u == v)
			return;

		if (m[u][v] != 0)
			m[u][v] = 0;

		if (!isdirected && m[v][u] != 0)
			m[v][u] = 0;
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

	vector<pair<int, int>> all_edges()
	{
		vector<pair<int, int>> edges;
		pair<int, int> p;
		for (int i = 0; i < m.size(); i++)
		{
			for (int j = 0; j < m.size(); j++)
			{
				if (m[i][j] == 0)
					continue;

				p.first = i;
				p.second = j;
				edges.push_back(p);
			}
		}

		return edges;
	}

	vector<int> list_neighbours(int source)
	{
		vector<int> edges;

		for (int i = source, j = 0; j < m.size(); j++)
		{
			if (m[i][j] != 0)
				edges.push_back(j);
		}
		return edges;
	}

	vector<int> DFSPath(int source, int destination)
	{
		vector<int> parents(m.size(), -1);
		vector<int> starting_time(m.size(), -1);
		vector<int> ending_time(m.size(), -1);
		vector<int> connected_components(m.size(), -1);
		vector<bool> visited(m.size(), false);
		vector<int> res;
		int clock = 1;
		int ccnum = 1;

		DFSExplore(source, visited, parents, starting_time, ending_time, connected_components, ccnum, clock);

		if (connected_components[source] != connected_components[destination])
			return res;

		find_path(source, parents, destination, res);
		return res;

	}

	vector<int> BFSPath(int source, int destination)
	{
		vector<int> parents(m.size(), -1);
		vector<bool> visited(m.size(), false);
		vector<int> res;

		BFSExplore(source, parents, visited);

		find_path(source, parents, destination, res);
		if (res.front() == -1)
			res.clear();

		return res;
	}

	void print_graph()
	{

		cout << "V: ";
		for (int i = 0; i < m.size(); i++)
		{
			cout << i << " ";
		}

		cout << endl;
		for (int i = 0; i < m.size(); i++)
		{
			cout << i << ": ";
			for (int j = 0; j < m.size(); j++)
			{
				cout << m[i][j] << " ";
			}
			cout << endl;
		}
	}

	bool IsGraph_Directed()
	{
		return isdirected;
	}


	//hw8

	vector<vector<int>> transpose()
	{
		vector<vector<int>> T(m.size(), vector<int>(m.size(), 0));

		for (int i = 0; i < m.size(); i++)
		{
			for (int j = 0; j < m.size(); j++)
			{
				if (m[i][j] == 1)
					T[j][i] = 1;
			}
		}

		return T;
	}

	vector<vector<int>> inverse()
	{

		vector<vector<int>> I(m.size(), vector<int>(m.size(), 0));
		for (int i = 0; i < m.size(); i++)
		{
			for (int j = 0; j < m.size(); j++)
			{
				I[i][j] = !(m[i][j]);
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

