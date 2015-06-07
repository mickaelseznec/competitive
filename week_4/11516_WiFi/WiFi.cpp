#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <array>
#include <queue>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

#define MAX_HOUSE   100000

int houses[MAX_HOUSE];
int houses_nb, access_nb;

bool test_for_distance (double distance) {
    double coord = houses[0] + distance;
    int index = 0;
    int access = 1;

    //printf("Set at %f\n", coord);
    while (coord < houses[houses_nb - 1]) {
        /* Dichotomic search ?*/
        while (houses[index] <= coord + distance) {
            index++;
            if (index == houses_nb) {
                return true;
            }
        }
        //printf("First non reached house : %d\n", index);
        access++;
        if (access > access_nb)
            return false;

        coord = houses[index] + distance;
        //printf("Set at %f\n", coord);
    }

    return true;
}

int main(void) {

    int cases;

    scanf("%d", &cases);

    while (cases--) {
        scanf("%d %d", &access_nb, &houses_nb);

        for (int i = 0; i < houses_nb; i++) {
            scanf("%d", &houses[i]);
        }

        if (access_nb >= houses_nb) {
            printf("0.0\n");
            continue;
        }

        sort(houses, houses + houses_nb);

        double high = houses[houses_nb - 1] - houses[0];
        double low = 0;

        while (high - low > 0.005) {
            //printf("Trying with %f (%f, %f)", (high+low)/2.0, high, low);
            if (test_for_distance((high + low)/2.0)) {
                //printf("... ok !\n");
                high = (high + low) / 2.0;
            } else {
                //printf("... nope !\n");
                low = (high + low) / 2.0;
            }
        }
        printf("%.1f\n", (high+low)/2.0);
    }

    return 0;
}
