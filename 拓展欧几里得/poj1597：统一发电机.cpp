#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

long long gcdll(long long a, long long b) {
    a = llabs(a); b = llabs(b);
    while (b) { long long t = a % b; a = b; b = t; }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long step, mod;
    while ((cin >> step >> mod)) {
        bool good = (gcdll(step, mod) == 1);

        cout << right << setw(10) << step
            << right << setw(10) << mod
            << "    "                       // 恰好 4 个空格 -> 第25列
            << (good ? "Good Choice" : "Bad Choice")
            << "\n\n";                      // 每组后只加一行空行
    }
    return 0;
}
