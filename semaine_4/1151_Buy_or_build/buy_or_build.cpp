#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <array>
#include <queue>
#include <utility>
#include <set>
#include <climits>

using namespace std;

#define MAX_CITIES  1000

array<pair<int,int>, MAX_CITIES> cities;
array<array<int, MAX_CITIES>, MAX_CITIES> distances;
array<array<bool, MAX_CITIES>, MAX_CITIES> share_subnetwork;

int buy_or_build (vector<vector<int>> subnetworks, int city_nb) {
    int min_price = INT_MAX;
    for (int sub_combinaison = 0; sub_combinaison < (1 << subnetworks.size()); sub_combinaison ++) {
        for (int x = 0; x < city_nb; x++) {
            for (int y = 0; y < city_nb; y++) {
                share_subnetwork[x][y] = false;
            }
        }
        //printf("Case %d:", sub_combinaison);
        int price = 0;

        vector<bool> linked_cities (city_nb);

        for (int i = 0; i < (int) subnetworks.size(); i++) {
            if ((sub_combinaison >> i) % 2 == 1) {
                //printf(" %d", i);
                price += subnetworks[i][0];
                for (int x = 1; x < (int) subnetworks[i].size(); x++) {
                    for (int y = x + 1; y < (int) subnetworks[i].size(); y++) {
                        //printf("Adding %d and %d in same subnetwork\n", subnetworks[i][x], subnetworks[i][y]);
                        share_subnetwork[subnetworks[i][x]][subnetworks[i][y]] = true;
                        share_subnetwork[subnetworks[i][y]][subnetworks[i][x]] = true;
                    }
                }
            }
        }
        //printf(" bought for a cost of %d\n", price);

        vector<int> distance_to_network (city_nb, INT_MAX);
        vector<int> nearest_neighboor (city_nb);
        set<int> build_network;
        set<int> not_in_network;

        build_network.insert(0);
        int nearest_city = 0;
        for(int city = 1; city < city_nb; city ++) {
            not_in_network.insert(city);
        }

        /* Prim algorithm*/
        while (!not_in_network.empty()) {
            for (auto city_unlinked : not_in_network) {
                //printf("Trying with %d and %d\n", nearest_city, city_unlinked);
                if (share_subnetwork[nearest_city][city_unlinked]) {
                    //printf("%d and %d are in same subnetwork\n", nearest_city, city_unlinked);
                    distance_to_network[city_unlinked] = 0;
                } else if (distances[city_unlinked][nearest_city] < distance_to_network[city_unlinked]) {
                    distance_to_network[city_unlinked] = distances[city_unlinked][nearest_city];
                }
            }

            int nearest_dist = INT_MAX;
            for (auto city_unlinked : not_in_network) {
                if (distance_to_network[city_unlinked] < nearest_dist) {
                    nearest_city = city_unlinked;
                    nearest_dist = distance_to_network[city_unlinked];
                }
            }

            build_network.insert(nearest_city);
            //printf("  Linked %d at a price of %d\n", nearest_city, nearest_dist);
            price += nearest_dist;
            not_in_network.erase(not_in_network.find(nearest_city));
        }

        min_price = (min_price > price) ? price : min_price;

    }
    return min_price;
}

int main(void) {
    int cases;

    scanf("%d", &cases);

    while (cases--) {
        vector<vector<int>> subnetworks;
        int city_nb, sub_nb;
        scanf("%d %d", &city_nb, &sub_nb);

        for (int i = 0; i < sub_nb; i++) {
            int sub_length, price;
            vector<int> subnetwork;
            scanf("%d %d", &sub_length, &price);

            subnetwork.push_back(price);
            for (int j = 0; j < sub_length; j++) {
                int temp;
                scanf("%d", &temp);
                subnetwork.push_back(temp - 1);
            }
            subnetworks.push_back(subnetwork);
        }

        for (int i = 0; i < city_nb; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            cities[i] = make_pair(x,y);
        }

        for (int i = 0; i < city_nb; i++) {
            for (int j = i + 1; j < city_nb; j++) {
                distances[i][j] = (cities[i].first - cities[j].first) *
                    (cities[i].first - cities[j].first) +
                    (cities[i].second - cities[j].second) *
                    (cities[i].second - cities[j].second);
                distances[j][i] = distances[i][j];
            }
        }

        printf("%d\n", buy_or_build(subnetworks, city_nb));

        if (cases)
            printf("\n");
    }

    return 0;
}
