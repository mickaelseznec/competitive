#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <climits>
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

set<string> dic = {"pass", "ifgo", "jump", "loop", "die"};
vector<vector<int>> edges (100000);
vector<int> end_vertex;
priority_queue<pair<pair<int, int>, int>> post_path;

int main(void) {
    string command;
    int arg1, arg2;
    int line_index;
    string line;
    while (getline(cin, line)) {
        line_index = 0;
        while (!line.empty()) {
            line = line.substr(line.find_first_not_of(' '));
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            command = line.substr(0, line.find(' '));
            if (command.compare("pass") == 0) {
                edges[line_index].push_back(line_index + 1);
            } else if (command.compare("die") == 0) {
                end_vertex.push_back(line_index);
            } else if (command.compare("ifgo") == 0) {
                line = line.substr(line.find(' '));
                line = line.substr(line.find_first_not_of(' '));
                arg1 = stoi(line.substr(0, line.find(' ')));

                edges[line_index].push_back(line_index + 1);
                edges[line_index].push_back(arg1);
            } else if (command.compare("jump") == 0) {
                line = line.substr(line.find(' '));
                line = line.substr(line.find_first_not_of(' '));
                arg1 = stoi(line.substr(0, line.find(' ')));

                edges[line_index].push_back(arg1);
            } else if (command.compare("loop") == 0) {
                line = line.substr(line.find(' '));
                line = line.substr(line.find_first_not_of(' '));
                arg1 = stoi(line.substr(0, line.find(' ')));

                line = line.substr(line.find(' '));
                line = line.substr(line.find_first_not_of(' '));
                arg2 = stoi(line.substr(0, line.find(' ')));

                edges[line_index].push_back(line_index + 1);
                post_path.push(make_pair(make_pair(-line_index, arg1), arg2));
            }
            getline(cin, line);
            line_index++;
        }
    }
    return 0;
}
