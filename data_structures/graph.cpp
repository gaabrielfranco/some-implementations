#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;

template <class T>
class graph
{
	private:
		vector<vector<pair<T, T>>> adjacent_list;
	public:
		graph(T V)
		{
			adjacent_list.assign(V, vector<pair<T, T>>());
		}

		void insert(T V, T id, T weight)
		{
			pair<T, T> edge(id, weight);
			adjacent_list[V].push_back(edge);
		}

		void print()
		{
			int i = 0;
			for (auto it = adjacent_list.begin(); it != adjacent_list.end(); it++, i++)
			{
				for (auto it2 = it->begin(); it2 != it->end(); it2++)
				{
					cout << i << " -> " << it2->first << " with weight = " << it2->second << endl;
				}
			}
		}
};

int main()
{
	graph<int> garfo(10);

	for (double i = 1.0; i < 10.0; i++)
	{
		garfo.insert(0, i, i);
		garfo.insert(i, 0, i);
	}

	garfo.print();
	

	return 0;
}