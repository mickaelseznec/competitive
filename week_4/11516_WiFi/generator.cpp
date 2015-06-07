#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define TEST_NB 5
#define MAX_HOUSES  100
#define MAX_NUMBER  1000000

inline int RNG(int a, int b) {
    if (b > a)
        return rand() % (b-a) + a;
    else
        return rand() % (a-b) + b;
}

int main (void) {
    srand (time(NULL));

    int cases = TEST_NB;

    printf("%d\n", cases);
    while (cases --) {
        int houses = RNG(1,MAX_HOUSES);
        int access = RNG(1,MAX_HOUSES);
        printf("%d %d\n", access, houses);

        for (int i = 0; i < houses; i++) {
            printf("%d\n", RNG(1, MAX_NUMBER));
        }
    }
    printf("0\n");
}
