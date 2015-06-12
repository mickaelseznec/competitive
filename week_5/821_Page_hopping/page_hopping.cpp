#include <iostream>
#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>
#include <cstdio>
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

int distances[100][100];

int main(void) {

    int from, to, size, cases = 1;
    queue<pair<int,int>> buffer;
    size = 0;
    while (scanf("%d %d", &from, &to) == 2 && !(from == 0 && to == 0)) {
        size = max(--from, --to);
        buffer.push(make_pair(from, to));

        while (scanf("%d %d", &from, &to) == 2 && !(from == 0 && to == 0)) {
            size = max(size, --from);
            size = max(size, --to);
            buffer.push(make_pair(from, to));
        }

        size++;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                distances[i][j] = INT_MAX / 2;
            }
        }

        while (!buffer.empty()) {
            distances[buffer.front().first][buffer.front().second] = 1;
            buffer.pop();
        }
        for (int i = 0; i < size; i++) {
            distances[i][i] = 0;
        }
        /*
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (distances[i][j] >= INT_MAX / 2)
                    printf("x ");
                else
                    printf("%d ", distances[i][j]);
            }
            puts("");
        }
        */
        for (int k = 0; k < size; k++) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j]);
                }
            }
        }

        int sum = 0, n = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0 ; j < size; j++) {
                if (distances[i][j] != 0 && distances[i][j] < INT_MAX / 2) {
                    sum += distances[i][j];
                    n++;
                }
            }
        }
        printf("Case %d: average length between pages = %.3f clicks\n", cases++, sum/(double)n); 
    }

    return 0;
}
