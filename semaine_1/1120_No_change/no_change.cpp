#include <iostream>

using namespace std;

void adem_algo (int amount, int *coin_value, int coins) {
    int coin_used[5] = {0,};
    bool solved = false;

    while (amount >= coin_value[0]) {
        amount -= coin_value[0];
        coin_used[0]++;
    }

    for (int i = 1; i < coins; i++) {
        while (amount >= coin_value[i] && coin_used[i] < coin_used[i-1]) {
            amount -= coin_value[i];
            coin_used[i]++;
        }
        if (amount == 0) {
            solved = true;
            break;
        }
    }
    if (solved)
        cout << "YES" << endl << endl;
    else
        cout << "NO" << endl << endl;

}

int main (void) {
    int cases, amount, coins;
    int coin_value[5];
    int coin_used[5];

    cin >> cases;
    for (int n = 0; n < cases; n++) {
        cin >> amount >> coins;
        for (int i = 0; i < coins; i++) {
            cin >> coin_value[i];
        }

        adem_algo(amount, coin_value, coins);
    }

    return 0;
}
