#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> mas;
    for (int i = 0; i < n - 2; ++i)
    {
        int x;
        std::cin >> x;
        mas.push_back(x);
    }

    int s  = 0;
    int s2 = 0;
    for (int i = 0; i < mas.size(); ++i)
    {
        s  += mas[i];
        s2 += mas[i]*mas[i];
    }

    s  = n*(n+1)/2 - s;
    s2 = n*(n+1)*(2*n+1)/6 - s2;

    int p = -s;
    int q = (s*s - s2) / 2;

    double D = p*p - 4*q;

    int a = ( -p + std::sqrt(D) ) / 2. + 0.5;
    int b = ( -p - std::sqrt(D) ) / 2. + 0.5;

    std::cout << a << " " << b << std::endl;

    return 0;
}
