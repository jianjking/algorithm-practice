#include <iostream>
#include <cmath>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    long long x = min(a, b), y = max(a, b);
    long long k = y - x;
    const long double phi = (1.0L + sqrtl(5.0L)) / 2.0L;
    long long t = (long long)(floorl(k * phi));
    if (x == t)
        cout << 0 << "\n";
    else
        cout << 1 << "\n";

    return 0;
}
