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
    char names[550];

    while (cases --) {

        int i;
        for(i = 0; i < RNG(1, 500); i ++)
            names[i] = RNG('A', 'Z');
        names[i] = '\0';

        printf("%d %d %s\n", i - 1, RNG(1,500), names);

    }
}
