#include <iostream>
#include <cstdio>
#include <array>
#include <string>
#include <queue>
#include <utility>

using namespace std;

array<array<bool, 400>, 400> agenda;
array<int, 400> line_weight;
char agenda_line[400];
array<int, 400> permutations;

int weight (int i, int j) {
    int new_weight = line_weight[i];
    for (int k = 0; k < j + 1; ++k) {
        if (agenda[i][k])
            new_weight --;
    }
    return new_weight;
}

int main(void) {

    int cases;

    scanf("%d", &cases);

    while (cases--) {
        int lines, columns;
        priority_queue<pair<int, int>> processing;

        scanf("%d\n%d", &lines, &columns);

        for (int i = 0; i < lines; ++i) {
            scanf("%s", agenda_line);
            int weight = 0;
            for (int j = 0; j < columns; j++) {
                if (agenda_line[j] == '1') {
                    agenda[i][j] = true;
                    weight++;
                }
                else
                    agenda[i][j] = false;
            }
            line_weight[i] = weight;
        }

        for (int j = 0; j < columns; j++) {
            permutations[j] = j;
        }

        for (int j = 0; j < columns - 2; ++j) {
            for (int i = 0; i < lines; ++i) {
                if (agenda[i][j]) {
                    processing.push(make_pair(weight(i, j), i));
                    //printf("Coucou %d %d %d\n", weight(i,j), i, j);
                }
            }

            if (!agenda[processing.top().second][j+1]) {
                int k = j+1;
                while (k < columns && !agenda[processing.top().second][k]) {
                    k++;
                }

                int temp = permutations[k];
                permutations[k] = permutations[j+1];
                permutations[j+1] = temp;
                    //printf("Permuting %d and %d\n", k, j+1);

                for (int i = 0; i < lines; ++i) {
                    bool temp = agenda[i][k];
                    agenda[i][k] = agenda[i][j+1];
                    agenda[i][j+1] = temp;
                }

            }

            while (!processing.empty())
                processing.pop();
        }

        for (int j = 0; j < columns; j++) {
            printf("%d\n", permutations[j]);
        }

        if (cases)
            puts("\n");
        else
            puts("");
    }

    return 0;
}
