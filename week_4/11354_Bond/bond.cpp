#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <array>
#include <queue>
#include <utility>
#include <set>
#include <climits>

using namespace std;

int main(void) {

    int cities_nb, road_nb;
    bool first = true;

    while(scanf("%d %d", &cities_nb, &road_nb) == 2) {
        vector<vector<pair<int, int>>> cities (cities_nb);
        if (first)
            first = false;
        else
            puts("");

        for (int i = 0; i < road_nb; i++) {
            int city_1, city_2, dangerousness;
            scanf("%d %d %d", &city_1, &city_2, &dangerousness);
            city_1--;
            city_2--;

            cities[city_1].push_back(make_pair(city_2, dangerousness));
            cities[city_2].push_back(make_pair(city_1, dangerousness));
        }

        int answer_nb;
        scanf("%d", &answer_nb);
        for (int i = 0; i < answer_nb; i++) {
            int from, to;
            scanf("%d %d", &from, &to);
            from--;
            to--;

            priority_queue<pair<int, int>> queue;
            vector<bool> marked (cities_nb, false);
            vector<int> dist (cities_nb, INT_MAX);


            queue.push(make_pair(0, from));
            dist[from] = 0;

            while (!queue.empty()) {
                int pivot = queue.top().second;
                //printf("Pivot is %d (was at %d)\n", pivot, -queue.top().first);
                if (pivot == to)
                    break;
                marked[pivot] = true;
                queue.pop();
                if (dist[pivot] > dist[to])
                    continue;

                for (auto ngb : cities[pivot]) {
                    if (!marked[ngb.first] && (dist[ngb.first] > 
                                max(dist[pivot], ngb.second))) {
                        dist[ngb.first] = max(dist[pivot], ngb.second);
                        queue.push(make_pair(-dist[ngb.first], ngb.first));
                    }
                }
            }
            printf("%d\n", dist[to]);
        }
    }

    return 0;
}
