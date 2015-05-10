#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

#define SIZE_DICO      10000

int main(void) {
    int n;
    string word;

    srandom(1234321);

    for(int i = 0; i < SIZE_DICO; i++) {
        n = random() % 30 + 1;
        word = "";
        for(int j = 0; j < n; j++) {
            word += (char) ((random() % 26) + 65);
        }
        cout << word << endl;
    }

    return 0;
}
