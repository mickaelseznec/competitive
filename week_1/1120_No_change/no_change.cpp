#include <iostream>
#include <cmath>

using namespace std;

int cases, amount, coins;
int coin_value[5];
int coin_used[5];

inline int coin_max (int index, int max_coin, int amount) {

    int min = (floor(amount/coin_value[index])) > max_coin ? max_coin : floor(amount/coin_value[index]);
    return min;
}

bool amount_possible (int index, int max_coin, int amount) {
    if (amount % coin_value[index] == 0) {
        if ((int) amount / coin_value[index] <= max_coin) {
            return true;
        }
    }
    if (index == coins-1)
        return false;

    /* Try with every number of current coin possible */
    for (int i = 1; i <= coin_max(index, max_coin, amount); i++) {
        if (amount_possible(index + 1, i, amount - i * coin_value[index]))
            return true;
    }

    return false;
}


int main (void) {
    cin >> cases;
    for (int n = 0; n < cases; n++) {
        cin >> amount >> coins;
        for (int i = 0; i < coins; i++) {
            cin >> coin_value[i];
        }

        if (n > 0)
            cout << endl << endl;
        if (amount_possible(0, floor(amount/coin_value[0]), amount))
            cout << "YES";
        else
            cout << "NO";
    }

    cout << endl;

    return 0;
}
