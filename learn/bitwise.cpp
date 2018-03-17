#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int S, n;

    S = 41;
    n = 4;

    printf("1) Mod em bitwise = %d\n\n", S & (n - 1));

    auto T = (S & (-S)); //Bit menos signifiicativo em S

    if (T == S)
        printf("2) S eh potencia de 2\n\n");
    else
        printf("2) S nao eh potencia de 2\n\n");

    T = S & (~(S & (-S)));

    printf("3) %d\n\n", T);

    T = ~(S);
    T = (T & (-T));
    T = (S | T);

    printf("4) %d\n\n", T);

    return 0;
}