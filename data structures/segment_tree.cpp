#include <bits/stdc++.h>

using namespace std;

struct segment_tree
{
    vector<int> segtree, array;
    int n;

    //Constructor
    segment_tree(const vector<int> &_array)
    {
        array = _array;
        n = (int)_array.size();
        segtree.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    //Return (i / 2)
    int left(int i)
    {
        return i << 1;
    }

    //Return (i / 2) + 1
    int right(int i)
    {
        return (i << 1) + 1;
    }

    //Build segtree
    void build(int i, int l, int r)
    {
        if (l == r)
        {
            segtree[i] = l;
        }
        else
        {
            build(left(i), l, (l + r) / 2);
            build(right(i), ((l + r) / 2) + 1, r);
            int i_left = segtree[left(i)], i_right = segtree[right(i)];
            segtree[i] = (array[i_left] <= array[i_right]) ? i_left : i_right;
        }
    }

    //Range Minimum Querry
    int rmq(int p, int l, int r, int i, int j)
    {
        if (i > r || j < l)
        {
            return -1;
        }
        if (l >= i && r <= j)
        {
            return segtree[p];
        }

        int p1 = rmq(left(p), l, (l + r) / 2, i, j);
        int p2 = rmq(right(p), ((l + r) / 2) + 1, r, i, j);

        if (p1 == -1)
        {
            return p2;
        }

        if (p2 == -1)
        {
            return p1;
        }

        return (array[p1] <= array[p2]) ? p1 : p2;
    }

    //Overload
    int rmq(int i, int j)
    {
        return rmq(1, 0, n - 1, i, j);
    }

    //Update a value in array
    int update_value(int p, int l, int r, int index, int new_value)
    {
        int i = index, j = index;

        if (i > r || j < l)
            return segtree[p];

        if (l == i && r == j)
        {
            array[i] = new_value;
            return segtree[p] = l;
        }

        int p1, p2;
        p1 = update_value(left(p), l, (l + r) / 2, index, new_value);
        p2 = update_value(right(p), ((l + r) / 2) + 1, r, index, new_value);

        return segtree[p] = (array[p1] <= array[p2]) ? p1 : p2;
    }

    //Overload
    int update_value(int index, int new_value)
    {
        return update_value(1, 0, n - 1, index, new_value);
    }
};

int main()
{
    int v[] = {18, 17, 13, 19, 15, 11, 20};

    vector<int> A(v, v + sizeof(v) / sizeof(int));

    segment_tree st(A);

    printf("rmq(1, 3) = %d\n", st.rmq(1, 3));
    printf("rmq(0, 6) = %d\n", st.rmq(0, 6));

    puts("A[1] = 100");
    st.update_value(1, 100);

    puts("A[5] = 80");
    st.update_value(5, 100);

    printf("rmq(0, 6) = %d\n", st.rmq(0, 6));

    return 0;
}