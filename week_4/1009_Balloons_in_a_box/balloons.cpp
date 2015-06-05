#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <array>
#include <queue>
#include <utility>
#include <set>
#include <climits>
#include <cmath>
#include <cfloat>
#include <algorithm>

using namespace std;

array<array<int, 3>, 6> points;
array<float, 6> radius;
array<array<int, 3>, 2> box;
array<int, 6> dist_min_box;

void compute_dist_min_box (int point_nb) {
    for (int point = 0; point < point_nb; point++) {
        int min = INT_MAX;

        bool out = false;

        /* Discard point if not in box*/
        for (int i = 0; i < 2; i++) {
            if (box[0][i] < box[1][i]) {
                if (!(points[point][i] > box[0][i] && points[point][i] < box[1][i]))
                    out = true;
            } else {
                if (!(points[point][i] < box[0][i] && points[point][i] > box[1][i]))
                    out = true;
            }
        }
        if (out) {
            dist_min_box[point] = 0;
            continue;
        }

        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < 3; i++) {
                if (min > abs(points[point][i] - box[j][i]))
                    min = abs(points[point][i] - box[j][i]);
            }
        }
        dist_min_box[point] = min;
    }
}

inline float euclidian_dist (int pt1, int pt2) {
    return sqrt(((points[pt1][0] - points[pt2][0]) * (points[pt1][0] - points[pt2][0])) +
            ((points[pt1][1] - points[pt2][1]) * (points[pt1][1] - points[pt2][1])) +
            ((points[pt1][2] - points[pt2][2]) * (points[pt1][2] - points[pt2][2])));
}

inline float dist_to_ballon (int point, int balloon) {
    if (euclidian_dist (point, balloon) - radius[balloon] > 0)
        return euclidian_dist (point, balloon) - radius[balloon];
    else 
        return 0;
}

inline float box_volume (void) {
    return abs((box[1][0] - box[0][0]) *
            (box[1][1] - box[0][1]) *
            (box[1][2] - box[0][2]));
}

int main(void) {

    int point_nb;
    int cases = 0;
    bool first = true;

    while (1) {
        cases ++;
        scanf("%d", &point_nb);
        if (!point_nb)
            break;

        if (first)
            first = false;
        else
            puts("");

        scanf("%d %d %d", &box[0][0], &box[0][1], &box[0][2]);
        scanf("%d %d %d", &box[1][0], &box[1][1], &box[1][2]);

        for (int i = 0; i < point_nb; i++) {
            int point_x, point_y, point_z;
            scanf("%d %d %d", &point_x, &point_y, &point_z);
            points[i][0] = point_x;
            points[i][1] = point_y;
            points[i][2] = point_z;
        }

        compute_dist_min_box(point_nb);

        vector<int> prm (point_nb);
        for (int i = 0; i < point_nb; i++) {
            prm[i] = i;
        }

        float final_volume = 0.0f;
        do {
            float volume = 0.0f;
            for (int i = 0; i < point_nb; i++) {
                float min_r = dist_min_box[prm[i]];
                //printf("Distance between box and %d: %d\n", prm[i], (int) min_r);
                for (int j = 0; j < i; j++) {
                    //printf("Distance from %d and balloon %d: %f (%f)\n", prm[j], prm[i], dist_to_ballon(prm[i],prm[j]), euclidian_dist(prm[i], prm[j]));
                    if (min_r > dist_to_ballon(prm[i], prm[j]))
                        min_r = dist_to_ballon(prm[i],prm[j]);
                }
                //printf("Choose r=%f for point %d\n", min_r, prm[i]);
                radius[prm[i]] = min_r;
                volume += pow(min_r, 3);
            }
            volume *= (4.0f / 3.0f) * M_PI;
            //printf("Intermediate volume : %f\n\n", volume);
            if (volume > final_volume)
                final_volume = volume;
        } while (next_permutation(prm.begin(), prm.end()));

        printf("Box %d: %d\n", cases, (int) round(box_volume() - final_volume));
    }
    return 0;
}
