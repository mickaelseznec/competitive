#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <queue>

using namespace std;

vector <pair<bool, vector<int>>> relations;

static inline void add_relation (int from, int to) {
    relations[from].second.push_back(to);
    relations[to].second.push_back(from);
}

int dijkstra (int from, int to, int camarades) {
    priority_queue <pair<int, int>> not_marked;
    map<int, int> distance;
    for (int i = 0; i < camarades; ++i) {
        distance[i] = numeric_limits<int>::max();
    }

    distance[from] = 0;
    not_marked.push(pair<int, int> (0, from));

    while (!not_marked.empty()) {
        //cout << "Call with " << not_marked.top().second << endl;
        int node = not_marked.top().second;
        not_marked.pop();
        relations[node].first = true;

        if (node == to)
            break;

        for (auto neighboor : relations[node].second) {
            if (!relations[neighboor].first) {
                if (distance[neighboor] > distance[node] + 1) {
                    not_marked.push(make_pair(-distance[neighboor], neighboor));
                    distance[neighboor] = distance[node] + 1;
                }
            }
        }
    }
    return distance[to];
}

/* Using Dijkstra algorithm with adjacency vector to limit space occupied*/
int main(void) {

    int cases;

    scanf("%d", &cases);

    while (cases--) {
        relations.clear();
        int camarades, from, to;
        scanf("%d", &camarades);

        relations.resize(camarades);
        for (int i = 0; i < camarades; ++i) {
            int from, to, relations_nb;
            scanf("%d %d", &from, &relations_nb);
            while (relations_nb --) {
                scanf("%d", &to);
                add_relation(from, to);
            }
        }

        scanf("%d %d", &from, &to);

        printf("%d %d %d\n", from, to, dijkstra(from, to, camarades) - 1);

        if (cases)
            printf("\n");
    }
    return 0;
}
