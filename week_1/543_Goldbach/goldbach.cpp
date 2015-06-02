#include <iostream>
#include <cmath>

using namespace std;

#define MAX_SIZE_N  1000000

bool is_not_prime[MAX_SIZE_N];
int primes[MAX_SIZE_N];

void compute_primes (void) {
    is_not_prime[0] = 1;
    is_not_prime[1] = 1;
    for(int n = 2; n < sqrt(MAX_SIZE_N) + 1; n++) {
        for(int m = 2; n * m < MAX_SIZE_N; m++) {
            is_not_prime[n * m] = 1;
        }
    }
}

int main(void) {
    int n, j = 0, i = 0;

    compute_primes();
    for(int i = 0; i < MAX_SIZE_N/2; i++) {
        if (!is_not_prime[i]) { // if prime
            primes[j++] = i;
        }
    }

    while (cin >> n) {
        if (n < 6 || n % 2 == 1)
            continue;
        for (i = 0; i < MAX_SIZE_N; i++) {
            if(!is_not_prime[n - primes[i]])
                break;
        }
        cout << n << " = " << primes[i] << " + " << n - primes[i] << endl;
    }

    return 0;
}
