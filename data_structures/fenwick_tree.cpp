#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

class fenwick_tree 
{
	private:
		vector<int> ft;
	public:
		fenwick_tree(int n)
		{
			//Initialize with n+1 zeroes
			ft.assign(n + 1, 0);
		}

		int ls_one(int value)
		{
			return (value & (-value));
		}

		int rsq(int value)
		{
			int sum = 0;
			for (; value; value-= ls_one(value))
			{
				sum += ft[value];
			}
			return sum;
		}

		int rsq(int v1, int v2)
		{
			return rsq(v2) - (v1 == 1 ? 0 : rsq(v1 - 1));
		}

		void adjust(int k, int v)
		{
			for (; k < (int)ft.size(); k += ls_one(k))
			{
				ft[k] += v;
			}
		}
};

int main()
{
	int f[] = { 2, 4, 5, 5, 6, 6, 6, 7, 7, 8, 9 };

	fenwick_tree ft(10);

	//Insert in Fenwick Tree
	for (int i = 0; i < 11; i++)
	{
		ft.adjust(f[i], 1);
	}

	printf("%d\n", ft.rsq(1, 1));
	printf("%d\n", ft.rsq(1, 2));
	printf("%d\n", ft.rsq(1, 6));
	printf("%d\n", ft.rsq(1, 10));
	printf("%d\n", ft.rsq(3, 6));

	ft.adjust(5, 2);
	printf("%d\n", ft.rsq(1, 10));

	return 0;
}