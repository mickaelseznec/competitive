#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

inline int RNG(int a, int b) {
    if (b > a)
        return rand() % (b-a) + a;
    else
        return rand() % (a-b) + b;
}

int main (void) {
    srand (time(NULL));

    int cases = 30;

    while (cases --) {
        int points = RNG(1,6);
        printf("%d\n", points);
        volatile int x0 = RNG(-10,10),
            y0 = RNG(-10,10),
            z0 = RNG(-10,10);
        volatile int x1, y1, z1;
        do {
            x1 = RNG(-10,10);
            y1 = RNG(-10,10);
            z1 = RNG(-10,10);
        } while (x1 == x0 || y1 == y0 || z1 == z0);
        printf("%d %d %d\n", x0, y0, z0);
        printf("%d %d %d\n", x1, y1, z1);

        for (int i = 0; i < points; i++) {
            printf("%d %d %d\n", RNG(x0, x1), RNG(y0, y1), RNG(z0,z1));
        }
    }
    printf("0\n");
}
