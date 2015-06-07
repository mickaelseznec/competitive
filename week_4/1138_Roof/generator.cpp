#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define MAX_ROOFS   2000

int main (void) {
    srand (time(NULL));

    int cases = 100;

    while (cases --) {
        int roofs = rand() % MAX_ROOFS + 1;
        printf("%d\n", roofs);

        for (int i = 0; i < roofs; i++) {
            int x1 = rand() % 200 + 1; 
            int y1 = rand() % 200 + 1; 
            int x2 = rand() % 200 + 1; 
            int y2 = rand() % 200 + 1; 

            printf("%d %d %d %d\n", x1, y1, x2, y2);
        }
    }
}
