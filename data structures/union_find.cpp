#include <bits/stdc++.h>

using namespace std;

class union_find
{
  private:
    vector<int> parent, rank, size;
    int n_sets;

  public:
    union_find(int number)
    {
        size.assign(number, 1);
        rank.assign(number, 0);
        parent.assign(number, 0);

        for (int i = 0; i < number; i++)
        {
            parent[i] = i;
        }

        n_sets = number;
    }

    int find_set(int set)
    {
        return (parent[set] == set) ? set : (parent[set] = find_set(parent[set]));
    }

    bool is_same_set(int set1, int set2)
    {
        return find_set(set1) == find_set(set2);
    }

    void union_set(int set1, int set2)
    {
        if (!is_same_set(set1, set2))
        {
            n_sets--;

            int p1 = find_set(set1);
            int p2 = find_set(set2);

            if (rank[p1] > rank[p2])
            {
                parent[p2] = p1;
                size[p1] += size[p2];
            }
            else
            {
                parent[p1] = p2;
                size[p2] += size[p1];
                if (rank[p1] == rank[p2])
                {
                    rank[p2]++;
                }
            }
        }
    }

    int size_of_set(int set)
    {
        return size[find_set(set)];
    }

    int number_sets()
    {
        return n_sets;
    }
};

int main()
{
    union_find set_1(10);

    printf("Number of disjoint sets = %d\n", set_1.number_sets());

    set_1.union_set(0, 1);
    set_1.union_set(0, 2);
    set_1.union_set(0, 3);

    set_1.is_same_set(0, 3) ? puts("Set 0 is equal to Set 3") : puts("Set 0 is not equal to Set 3");

    set_1.is_same_set(1, 7) ? puts("Set 1 is equal to Set 7") : puts("Set 1 is not equal to Set 7");

    printf("Size of set 0 = %d\n", set_1.size_of_set(0));

    printf("Number of disjoint sets = %d\n", set_1.number_sets());

    return 0;
}