#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define TEST_NB 5

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

    }
}
