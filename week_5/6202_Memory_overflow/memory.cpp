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

    int max_cases;

    scanf("%d", &max_cases);

    for (int cases = 1; cases <= max_cases; cases++) {
        int n, k, count = 0;
        char names[550];
        char person;

        scanf("%d %d %s", &n, &k, names);

        for (int i = 0; i < n; i++) {
            person = names[i];
            //printf("Trying %c\n", person);
            for (int j = i + 1; j < i + k + 1 && j < n; j++) {
                //printf("   with %c", names[j]);
                if (names[j] == person) {
                    //puts("  OK !");
                    count++;
                    break;
                }
                //puts("  NOPE !");
            }
        }

        printf("Case %d: %d\n", cases, count);
    }

    return 0;
}
