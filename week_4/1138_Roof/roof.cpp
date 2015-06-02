#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <array>
#include <queue>
#include <utility>
#include <set>

using namespace std;

#define MAX_ROOF    40000

array<array<int, 5>, MAX_ROOF> roofs;

float get_current_heigth(int index, int current_x_coord) {
    float a = (float) (roofs[index][3] - roofs[index][1]) / (roofs[index][2] - roofs[index][0]);
    float b = (float) (roofs[index][1]*roofs[index][2] - roofs[index][0]*roofs[index][3]) / (roofs[index][2] - roofs[index][0]);
    return a * current_x_coord + b;
}

int main(void) {

    int roof_nb;
    bool first = true;
    while (scanf("%d", &roof_nb) == 1) {
        if (first)
            first = false;
        else
            puts("");

        priority_queue<pair<int,int>> left_to_rigth;
        priority_queue<pair<int,int>> up_to_down;

        for (int i = 0; i < roof_nb; i++) {
            array<int, 5> roof;
            scanf("%d %d %d %d", &roof[0], &roof[1], &roof[2], &roof[3]);
            roof[4] = 0;
            left_to_rigth.push(make_pair(-roof[0], i));
            left_to_rigth.push(make_pair(-roof[2], i));
            up_to_down.push(make_pair(min(roof[1], roof[3]), i));
            roofs[i] = roof;
        }

        vector<bool> active_roof (roof_nb, false);
        int last_roof = left_to_rigth.top().second;
        int last_x_coord = - left_to_rigth.top().first;
        while (!left_to_rigth.empty()) {
            int current_x_coord = -left_to_rigth.top().first;
            int current_roof = left_to_rigth.top().second;
            //printf("At %d, on roof %d\n", current_x_coord, current_roof);
            //printf("        Adding %d of rain on %d\n", current_x_coord - last_x_coord, last_roof);
            left_to_rigth.pop();
            if (last_roof != -1)
                roofs[last_roof][4] += current_x_coord - last_x_coord;

            /* New roof reached*/
            if (current_x_coord == roofs[current_roof][0]) {
                active_roof[current_roof] = true;
                //printf("        Set %d as active\n", current_roof);
                if (get_current_heigth(last_roof, current_x_coord) < roofs[current_roof][1] || last_roof == -1)
                    last_roof = current_roof;
            }
            /* End of any roof*/
            else {
                active_roof[current_roof] = false;
                /* End of current roof : find the highest remaining roof*/
                if (current_roof == last_roof) {
                    //printf("        Warning : %d is finished\n", current_roof);
                    float max_height = 0;
                    int max_height_index = -1;
                    for (int i = 0; i < roof_nb; i++) {
                        if (active_roof[i])
                                //printf("%d is at %f\n", i, get_current_heigth(i, current_x_coord));
                        if (active_roof[i] && get_current_heigth(i, current_x_coord) > max_height) {
                            max_height = get_current_heigth(i, current_x_coord);
                            max_height_index = i;
                        }
                    }
                    last_roof = max_height_index;
                }
            }
            last_x_coord = current_x_coord;
        }

        while (!up_to_down.empty()) {
            int current_height = up_to_down.top().first;
            int current_roof = up_to_down.top().second;
            int current_x_coord = 0;
            up_to_down.pop();

            if (roofs[current_roof][1] < roofs[current_roof][3])
                current_x_coord = roofs[current_roof][0];
            else
                current_x_coord = roofs[current_roof][2];

            int below_roof = -1;
            int below_height = 0;
            for (int i = 0; i < roof_nb; i++) {
                if (roofs[i][0] <= current_x_coord && roofs[i][2] >= current_x_coord && roofs[i][1] < current_height) {
                    if (roofs[i][1] > below_height) {
                        below_roof = i;
                        below_height = roofs[i][1];
                    }
                }
            }
            if (below_roof != -1) {
                //printf("%d falls on %d\n", current_roof, below_roof);
                roofs[below_roof][4] += roofs[current_roof][4];
            }
        }

        for (int x = 0; x < roof_nb; x++) {
            printf("%d\n", roofs[x][4]);
        }
    }

    return 0;
}
