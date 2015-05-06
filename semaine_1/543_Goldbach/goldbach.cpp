#include <iostream>
#include <cmath>

using namespace std;

#define MAX_SIZE_N  1000000

bool is_prime[MAX_SIZE_N];
int primes[MAX_SIZE_N];

bool compute_prime (int n) {
    if (n <= 1) {
        return false;
    }

    for (int i = 2; i < ceil(sqrt(n)) + 1; i++) {
        if ( n % i == 0)
            return false;
    }
    return true;
}

int main(void) {
    int n, j = 0, i = 0;

    /* May increase speed by pre-calculate both arrays*/
    for(int i = 0; i < MAX_SIZE_N; i++) {
        is_prime[i] = compute_prime(i);
        if (is_prime[i])
            primes[j++] = i;
    }

    while (cin >> n) {
        if (n < 6 || n % 2 == 1)
            continue;
        for (i = 0; i < MAX_SIZE_N; i++) {
            if(is_prime[n - primes[i]])
                break;
        }
        cout << n << " = " << primes[i] << " + " << n - primes[i] << endl;
    }

    return 0;
}
