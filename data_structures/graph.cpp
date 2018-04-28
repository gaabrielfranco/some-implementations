#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

template <class T>
class graph
{
	private:
		std::vector<std::vector<std::pair<T, T>>> adjacent_list;
	public:
		graph(T V)
		{
			adjacent_list.assign(V, std::vector<std::pair<T, T>>());
		}

		void insert(T V, T id, T weight)
		{
			std::pair<T, T> edge(id, weight);
			adjacent_list[V].push_back(edge);
		}

		void remove(T V) 
		{

			for (size_t i = 0; i < adjacent_list[V].size(); i++)
			{
				auto node = adjacent_list[V][i].first;

				std::cout << node << std::endl;

				auto pend = std::remove_if(adjacent_list[node].begin(), adjacent_list[node].end(),
					[V](std::pair<T, T> edge) {
					return edge.first == V;
				});

				size_t new_size = pend - adjacent_list[node].begin();

				adjacent_list[node].resize(new_size);
			}

			adjacent_list[V].clear();
		}

		void print()
		{
			for (auto it = adjacent_list.begin(); it != adjacent_list.end(); ++it)
			{
				for (auto it_node = it->begin(); it_node != it->end(); ++it_node)
				{
					std::cout << "(" << it - adjacent_list.begin() << ", " << it_node->first << ", " << it_node->second << ")\n";
				}
			}
		}
};

int main()
{
	graph<int> garfo(10);

	for (int i = 1; i < 10; i++)
	{
		garfo.insert(0, i, i);
		garfo.insert(i, 0, i);
	}

	garfo.print();

	garfo.remove(0);
	puts("\n========= NEW GRAPH ===========\n");
	garfo.print();

	return 0;
}