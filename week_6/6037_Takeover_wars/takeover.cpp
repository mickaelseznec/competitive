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

#define TAKEOVER    0
#define BUYOUT      1

#define US    companies[i%2]
#define THEM  companies[(i+1)%2]

#define show_game() do {\
    printf("Takeover has ");\
    for (auto point : companies[TAKEOVER]) {\
        printf("%d ", point);\
    }\
    printf("\nBuyout has ");\
    for (auto point : companies[BUYOUT]) {\
        printf("%d ", point);\
    }\
    puts("");\
}while(0)


bool winner (vector<deque<int>> companies) {
    int i = 1;
    //show_game();
    while (1) {
        if (companies[TAKEOVER].empty()) {
            return false;
        } else if (companies[BUYOUT].empty()) {
            return true;
        } else if (companies[TAKEOVER].size() == 1 && companies[BUYOUT].size() == 1 && companies[TAKEOVER][0] == companies[BUYOUT][0]) {
            return true;
        } else if (US[0] > THEM[0]) {
            /* Do a takeover*/
            THEM.pop_front();
        } else if (US.size() > 1) {
            /* Do a merge*/
            int weight = US[0];
            US.pop_front();
            US[0] += weight;
        }
        i++;
        //show_game();
    }
}

int main(void) {

    int m, n, cases = 0;

    vector<deque<int>> memory_companies (2);
    vector<deque<int>> companies (2);

    while (scanf("%d %d", &n, &m) == 2) {
        companies.clear();
        companies.resize(2);

        memory_companies.clear();
        memory_companies.resize(2);

        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);

            companies[TAKEOVER].push_back(x);
        }

        for (int i = 0; i < m; i++) {
            int x;
            scanf("%d", &x);
            companies[BUYOUT].push_back(x);
        }

        sort(companies[TAKEOVER].begin(), companies[TAKEOVER].end(), greater<int>());
        sort(companies[BUYOUT].begin(), companies[BUYOUT].end(), greater<int>());

        for (int i = 0; i < (int) companies.size(); i++) {
            for (int j = 0; j < (int) companies[i].size(); j++) {
                memory_companies[i].push_back(companies[i][j]);
            }
        }
        bool result;
        //show_game();
        if (companies[TAKEOVER][0] > companies[BUYOUT][0]) {
            /* Try with takeover...*/
            //printf("Try with takeover\n");
            companies[BUYOUT].pop_front();
            result = winner(companies);
            /* And with merge*/
            //printf("Try with merge\n");
            if (!result) {
            int weight = memory_companies[TAKEOVER][0];
            memory_companies[TAKEOVER].pop_front();
            memory_companies[TAKEOVER][0] += weight;
            result = winner(memory_companies);
            }
        } else {
            if (companies[TAKEOVER].size() > 1) {
                //printf("Must merge\n");
                int weight = companies[TAKEOVER][0];
                companies[TAKEOVER].pop_front();
                companies[TAKEOVER][0] += weight;
                result = winner(companies);
            } else {
                //printf("Can't even merge\n");
                result = winner(companies);
            }

        }

        if (result) {
            printf("Case %d: Takeover Incorporated\n", ++cases);
        } else {
            printf("Case %d: Buyout Limited\n", ++cases);
        }
    }

    return 0;
}
