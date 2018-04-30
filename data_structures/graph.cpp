#include <algorithm>
#include <cstdio>
#include <exception>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

template <class Tx, class Ty>
class graph
{
   private:
    std::vector<std::vector<std::pair<Tx, Ty>>> adjacency_matrix;
    std::unordered_map<Tx, size_t> key_to_index;
    std::vector<Tx> index_to_key;
    std::vector<size_t> empty_positions;

   public:
    struct Vertex_Not_Found : std::exception
    {
        virtual const char* what() const
        {
            return "Vertex not found.";
        }
    };

    graph()
    {
    }

    void add_node(Tx V)
    {
        if (key_to_index.find(V) == key_to_index.end())
        {
            if (empty_positions.size())
            {
                size_t index = empty_positions.back();
                empty_positions.pop_back();

                adjacency_matrix[index] = std::vector<std::pair<Tx, Ty>>();
                key_to_index[V] = index;
                index_to_key[index] = V;
            }
            else
            {
                adjacency_matrix.push_back(std::vector<std::pair<Tx, Ty>>());
                key_to_index[V] = adjacency_matrix.size() - 1;
                index_to_key.push_back(V);
            }
        }
    }

    void add_edge(Tx source, Tx destination, Ty weight)
    {
        std::pair<Tx, Ty> edge(destination, weight);

        if (key_to_index.find(source) == key_to_index.end() ||
            key_to_index.find(destination) == key_to_index.end())
        {
            throw Vertex_Not_Found();
        }

        adjacency_matrix[key_to_index[source]].push_back(edge);
    }

    void remove_node(Tx V)
    {
        if (key_to_index.find(V) == key_to_index.end())
        {
            throw Vertex_Not_Found();
        }

        int index = key_to_index[V];

        for (size_t i = 0; i < adjacency_matrix[index].size(); i++)
        {
            auto node = adjacency_matrix[index][i].first;

            adjacency_matrix[key_to_index[node]].erase(
                std::remove_if(
                    adjacency_matrix[key_to_index[node]].begin(),
                    adjacency_matrix[key_to_index[node]].end(),
                    [V](std::pair<Tx, Ty> edge) { return edge.first == V; }),
                adjacency_matrix[key_to_index[node]].end());
        }

        adjacency_matrix[index].clear();
        key_to_index.erase(V);
        index_to_key[index] = -(1ULL);
        empty_positions.push_back(index);
    }

    void to_dot()
    {
        std::cout << "digraph {\n";

        for (size_t i = 0; i < adjacency_matrix.size(); i++)
        {
            if (index_to_key[i] == -1)
                continue;

            std::cout << "    " << index_to_key[i] << ";\n";

            for (size_t j = 0; j < adjacency_matrix[i].size(); j++)
            {
                std::cout << "    " << index_to_key[i] << " -> "
                          << adjacency_matrix[i][j].first << " [label=\""
                          << adjacency_matrix[i][j].second << "\"];\n";
            }
        }

        std::cout << "}";
    }
};

int main()
{
    graph<char, float> garfo;

    try
    {
        garfo.add_node('a');
        garfo.add_node('b');
        garfo.add_node('c');
        garfo.add_edge('a', 'b', 5.5);
        garfo.add_edge('a', 'b', 10.5);
        garfo.add_edge('a', 'b', 15.5);
        garfo.add_edge('a', 'b', 20.5);
        garfo.add_edge('a', 'b', 25.5);
        garfo.add_edge('b', 'a', 2.0);
        garfo.add_edge('b', 'c', 2.0);
        garfo.add_node('d');
    }
    catch (graph<char, float>::Vertex_Not_Found e)
    {
        std::cout << e.what() << std::endl;
    }

    garfo.to_dot();

    return 0;
}
