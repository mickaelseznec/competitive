#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {

    int cases;

    cin >> cases;

    for (int n = 0; n < cases; ++n) {
        if (n != 0)
            printf("\n");

        int cistern_nb;
        cin >> cistern_nb;

        vector<pair<float, float>> cisterns(2 * cistern_nb); 

        for (int i = 0; i < cistern_nb; ++i) {
            float base_level, height, width, depth;
            cin >> base_level >> height >> width >> depth;
            cisterns[2 * i] = make_pair(base_level, width * depth);
            cisterns[2 * i + 1] = make_pair(base_level + height, - width * depth);
        }

        float water_level;
        cin >> water_level;

        if (cistern_nb == 0) {
            if (water_level == 0) {
                cout << "0.00" << endl;
                continue;
            } else {
                cout << "OVERFLOW" << endl;
                continue;
            }
        }


        sort(cisterns.begin(), cisterns.end());

        /*
        for (int i = 0; i < 2 * cistern_nb; ++i) {
            cout << cisterns[i].first << ' ' << cisterns[i].second << endl;
        }
        */

        float result = 0;
        float surface = cisterns[0].second;
        int i = 1;
        //cout << "Water is now at " << cisterns[0].first << ". Level at " << water_level << endl;
        while (water_level >= 0 && i < 2 * cistern_nb) {
            if (water_level - (surface * (cisterns[i].first - cisterns[i-1].first)) > 0)
                water_level -= (surface * (cisterns[i].first - cisterns[i-1].first));
            else {
                result = cisterns[i-1].first + (water_level / surface);
                water_level = 0;
                break;
            }
            surface += cisterns[i].second;
            //cout << "Water is now at " << cisterns[i].first << ". Level at " << water_level << endl;
            ++i;
        }
        if (i == 2 * cistern_nb && water_level > 0)
            cout << "OVERFLOW" << endl;
        else
            printf("%.2f\n", result);
    }

    return 0;
}
