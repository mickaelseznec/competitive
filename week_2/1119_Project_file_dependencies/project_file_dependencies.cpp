#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main(void) {

    int cases;

    cin >> cases;

    for (int i = 0; i < cases; ++i) {
        if (i > 0)
            cout << endl;
        int node_number, dep_node_number;
        cin >> node_number >> dep_node_number;
        vector<pair<set<int>, set<int>>> nodes(node_number + 1);
        set<int> free_nodes;

        for (int j = 0; j < dep_node_number; j++) {
            int node, deps;
            cin >> node >> deps;
            for (int k = 0; k < deps; ++k) {
                int dependencie;
                cin >> dependencie;
                //cout << "Adding " << dependencie << " to dependencies of " << node << endl;
                nodes[node].first.insert(dependencie);
                //cout << "Adding " << node << " as a dependent of " << dependencie << endl;
                nodes[dependencie].second.insert(node);
            }
        }

        // Algorithm
        
        // Find first nodes without dependencies
        for (int j = 1; j < node_number + 1; ++j) {
            if (nodes[j].first.empty()) {
                //cout << j << " has no dependencies !" << endl;
                free_nodes.insert(j);
            }
        }

        bool first = true;
        while (!free_nodes.empty()) {
            if (!first)
                cout << ' ';
            first = false;
            int current_node  = *free_nodes.begin();
            free_nodes.erase(free_nodes.begin());
            cout << current_node;

            for (auto dependent : nodes[current_node].second) {
                nodes[dependent].first.erase(nodes[dependent].first.find(current_node));
                if (nodes[dependent].first.empty())
                    free_nodes.insert(dependent);
            }
        }
        cout << endl;
    }

    return 0;
}
