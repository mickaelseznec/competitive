#include <iostream>
#include <algorithm>

#define FIELD_LENGTH    100
#define FIELD_WIDTH     75

using namespace std;

bool is_fully_cut(float *cuts, int size, float length, float thickness);

int main(void) {
    int width, length;
    float thickness;

    while (cin >> width >> length >> thickness) {
        if (width == 0 && length == 0)
            break;

        float cuts_width[width];
        float cuts_length[length];

        for (int i = 0; i < width; i++) {
            cin >> cuts_width[i];
        }

        for (int i = 0; i < length; i++) {
            cin >> cuts_length[i];
        }

        sort(cuts_width, cuts_width + width);
        sort(cuts_length, cuts_length + length);

        if (is_fully_cut(cuts_width, width, FIELD_WIDTH, thickness) && is_fully_cut(cuts_length, length, FIELD_LENGTH, thickness))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}

bool is_fully_cut(float *cuts, int size, float length, float thickness) {
    if (cuts[0] > thickness / 2)
        return false;

    for (int i = 1; i < size; i++) {
        if (cuts[i] - cuts[i-1] > thickness)
            return false;
    }

    if (cuts[size-1] < length - (thickness / 2))
        return false;

    return true;
}
