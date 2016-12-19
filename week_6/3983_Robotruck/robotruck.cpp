#include <iostream>
#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <array>
#include <queue>
#include <stack>
#include <utility>
#include <algorithm>
#include <limits>

using namespace std;

#define MAX_PACKAGES    100005

/* distance[i] = distance from i to i+1*/
pair<int,int> coords[MAX_PACKAGES];
int distances[MAX_PACKAGES];
int weights[MAX_PACKAGES];
int global_distance[MAX_PACKAGES];

int capacity, packages;

void next_trip (int index) {
    printf("Call with index %d\n", index);
    int weight_taken = 0;
    int max_index = 0;
    while (weight_taken < capacity && index + max_index < packages) {
        weight_taken += weights[index + max_index];
        max_index++;
    }

    for (int i = max_index; i >= 0; --i) {

        int trip_size = abs(coords[index].first) + abs(coords[index].second);
        for (int j = 0; j < i; ++j) {
            trip_size += distances[index + j];
        }
        trip_size += abs(coords[index + i].first) + abs(coords[index + i].second);

        int last_distance = (index == 0) ? 0 : global_distance[index - 1];
        printf("%d is reachable for %d (%d)\n", index + i, last_distance + trip_size, trip_size);
        if (last_distance + trip_size < global_distance[index + i]) {
            global_distance[index + i] = last_distance + trip_size;
            printf("%d is now at distance %d\n", index + i, global_distance[index + i]);
            if (index + i < packages)
                next_trip(index + i);
        }
    }
}

int main(void) {

    int cases;
    scanf("%d", &cases);

    while (cases--) {

        scanf("%d\n%d", &capacity, &packages);

        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        weights[0] = w;
        pair<int,int> last_location = make_pair(x,y);
        coords[0] = last_location;

        for (int i = 0; i < packages; i++) {
            global_distance[i] = INT_MAX;
        }

        for (int i = 1; i < packages; i++) {
            scanf("%d %d %d", &x, &y, &w);
            distances[i-1] = abs(last_location.first - x) + abs(last_location.second - y);
            weights[i] = w;
            last_location = make_pair(x,y);
            coords[i] = last_location;
        }

        next_trip(0);

        printf("%d\n", global_distance[packages - 1]);

        if (cases)
            puts("");
    }

    return 0;
}
