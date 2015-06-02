#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <array>
#include <queue>
#include <utility>
#include <set>
#include <limits>
#include <cmath>

using namespace std;

vector <vector <int>> nodes;

/* Shortest cycle method implemented using 
 * http://perso.ens-lyon.fr/eric.thierry/Graphes2007/adrien-panhaleux.pdf*/

int find_any_cycle(int begin) {

    vector<int> levels (nodes.size(), -1);
    queue<int> node_queue;

    levels[begin] = 0;
    node_queue.push(begin);

    /* Find existing cycle*/
    while (!node_queue.empty()) {
        int node = node_queue.front();
        node_queue.pop();

        for (auto neighboor : nodes[node]) {
            if (levels[neighboor] == -1) {
                levels[neighboor] = levels[node] + 1;
                node_queue.push(neighboor);
            } else if (levels[node] <= levels[neighboor]) {
                return(levels[node]);
            }
        }
    }
    return numeric_limits<int>::max();
}

pair<int, int> edge (map<int, int> S) {
    for (int i = 0; i < (S.size() - cbrt(nodes.size())); i++) {
        for (auto w : nodes[S[i]]) {
            if (S.find(w) != S.end())
                return make_pair(S[i], w);
            /* delete w*/
        }
    }
    int max = (0 > S.size() - cbrt(nodes.size()) + 1) ?
        0 : S.size() - cbrt(nodes.size());
    for (int i = 0; i < max; i++) {
        for (int j = i + 1; i < (int) S.size(); i++) {
            int w = S[j];
            /* Find if edge belongs to graph*/
        }
    }
    return make_pair(0,0);
}

int shortest_cycle() {
    int min = numeric_limits<int>::max();
    vector<int> cycle_level (nodes.size());
    for (int node = 0; (size_t) node < nodes.size(); node++) {
        cycle_level[node] = find_any_cycle(node);
        min = (cycle_level[node] < min) ? cycle_level[node] : min;
    }
    if (min == numeric_limits<int>::max())
        return -1;
    for (int node = 0; (size_t) node < nodes.size(); node++) {
        if (cycle_level[node] == min) {
            /* To be continued*/
        }
    }
    return 0;
}

/* The problem is equivalent to find the shortest cycle in a non-oriented graph
 * it may be solved using the algorithm above*/
int main(void) {

    int cases;

    scanf("%d", &cases);

    for (int n = 0; n < cases; n++) {
        nodes.clear();
        int nodes_nb, relations_nb;
        scanf("%d %d", &nodes_nb, &relations_nb);

        nodes.resize(nodes_nb);
        for (int i = 0; i < relations_nb; i++) {
            int from, to;
            scanf("%d %d", &from, &to);
            nodes[from].push_back(to);
            nodes[to].push_back(from);
        }

        printf("%d\n", shortest_cycle());
    }

    return 0;
}
