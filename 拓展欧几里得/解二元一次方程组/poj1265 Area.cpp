#include<iostream>
#include<vector>
using namespace std;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    int n;
    scanf("%d", &n);
    for (int z = 1; z <= n; z++) {
        int m;
        scanf("%d", &m);
        long long twice = 0;  // |2 * area| 的有向和
        long long out = 0;    // 边界整点数 B
        long long x = 0, y = 0; // 当前点，从原点出发

        for (int i = 0; i < m; i++) {
            int dx, dy;
            scanf("%d%d", &dx, &dy);
            long long nx = x + dx, ny = y + dy;
            twice += x * ny - nx * y;                 // 累加鞋带(按路径)
            out += gcd(abs(dx), abs(dy));           // 每段边贡献 gcd(|dx|,|dy|)
            x = nx; y = ny;
        }
        long long T = llabs(twice);                   // |2A|
        long long in = (T - out + 2) / 2;             // Pick: 2A = 2I + B - 2
        double area = T / 2.0;

        printf("Scenario #%d:\n", z);
        printf("%lld %lld %.1f\n\n", in, out, area);
    }
    return 0;
}

}