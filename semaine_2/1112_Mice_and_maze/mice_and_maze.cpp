#include <iostream>
#include <limits>
#include <vector>
#include <set>
#include <utility>

using namespace std;

int escape_mouse (vector<vector<int>> connections, int exit_cell, int timer) {
    set<pair<int,int>> not_marked;
    vector<int> distance(connections.size(), numeric_limits<int>::max());

    not_marked.insert(pair<int, int> (0, exit_cell));
    distance[exit_cell] = 0;

    while (!not_marked.empty()) {
        int exam_cell = get<1>(*not_marked.begin());
        not_marked.erase(not_marked.begin());
        //cout << "Trying with cell n " << exam_cell << endl;
                for (unsigned int i = 1; i < connections.size(); ++i) {
                    if (connections[i][exam_cell] != 0) {
                        if (distance[i] > distance[exam_cell] + connections[i][exam_cell]) {
                            distance[i] = distance[exam_cell] + connections[i][exam_cell];
                            if (distance[i] < timer)
                                not_marked.insert(pair<int,int> (distance[i] , i));
                        }
                    }
                }
    }

    /*

    for (auto x : connections) {
        for (auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }

    for (auto x : distance)
        cout << x << ' ';
    cout << endl;

    */

    int result = 0;
    for (auto x : distance) {
        if (x <= timer)
            result ++;
    }

    return result;
}

int main(void) {

    int cases;

    cin >> cases;

    for (int i = 0; i < cases; ++i) {
        if (i > 0)
            cout << endl;
        int maze_size, exit_cell, timer, connections_size;
        cin >> maze_size >> exit_cell >> timer >> connections_size;
        vector<vector<int>> connections (maze_size + 1, vector<int> (maze_size + 1));

        for (int j = 0; j < connections_size; ++j) {
            int cell_from, cell_to, cell_duration;
            cin >> cell_from >> cell_to >> cell_duration;
            connections[cell_from][cell_to] = cell_duration;
        }

        cout << escape_mouse(connections, exit_cell, timer) << endl;

    // Replace with static list of neighboors ?
    }

    return 0;
}
