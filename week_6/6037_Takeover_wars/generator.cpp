#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define TEST_NB 50

inline int RNG(int a, int b) {
    if (b > a)
        return rand() % (b-a) + a;
    else
        return rand() % (a-b) + b;
}

int main (void) {
    srand (time(NULL));

    int cases = TEST_NB;

    while (cases --) {

        int n = RNG(1, 5), m = RNG(1, 5);
        printf("%d %d\n", n, m);
        for (int i = 0; i < n; i++) {
            printf("%d ", RNG(1, 10));
        }
        puts("");
        for (int i = 0; i < m; i++) {
            printf("%d ", RNG(1, 10));
        }
        puts("");
    }
}
