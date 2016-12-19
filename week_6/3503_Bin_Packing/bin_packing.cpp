#include <iostream>
#include <cmath>
#include <cstdio>
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

int main(void) {

    int cases;

    scanf("%d", &cases);

    while (cases--) {

        int n, l, bins = 0;
        multiset<int, greater<int>> items;
        scanf("%d\n%d", &n, &l);

        for (int i = 0; i < n; i++) {
            int item_l;
            scanf("%d", &item_l);
            items.insert(item_l);
        }

        while(!items.empty()) {
            bins++;
            int big_item = *items.begin();
            //printf("Choosing %d ", big_item);
            items.erase(items.begin());

            if (big_item < l) {
                if (items.lower_bound(l - big_item) != items.end()) {
                    //printf("with %d\n", *items.lower_bound(l - big_item));
                    items.erase(items.lower_bound(l - big_item));
                } else {
                    //puts(" alone (noone fits)");
                }
            } else {
                //puts(" alone (too big)");
            }
        }

        printf("%d\n", bins);

        if (cases)
            puts("");

    }

    return 0;
}
