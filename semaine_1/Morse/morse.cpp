#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

#define MORSE_DEPTH         4
#define MAX_SIZE_RETURN     50

const char input_string[] = "-.-..--.----.-";
char return_string[MAX_SIZE_RETURN];

char morse[] = {0,
    'E', 'T',
    'I', 'A', 'N', 'M',
    'S', 'U', 'R', 'W', 'D', 'K', 'G', 'O',
    'H', 'V', 'F',  0 , 'L',  0 , 'P', 'J', 'B', 'X', 'C', 'Y', 'Z', 'Q',  0 ,  0};

char decoded_string[50];

inline int move_index(int morse_index, char morse_symbol) {
    morse_index = 2 * (morse_index + 1);

    if (morse_symbol == '.')
        morse_index--;

    return morse_index;
}

void decode_morse(int input_string_index, int return_string_index) {
    int morse_index = 0;

    for (int i = input_string_index; i < input_string_index + MORSE_DEPTH; i++) {
        if (input_string[i] == '\0') {
            break;
        }
        morse_index = move_index(morse_index, input_string[i]);

        /* TODO : If morse[morse_index] belong to letter suitable*/
        if(morse[morse_index] != 0) {
            return_string[return_string_index] = morse[morse_index];
            return_string[return_string_index + 1] = '\0';
            if (i == sizeof(input_string) - 2)
                cout << return_string << endl;
            decode_morse(i + 1, return_string_index + 1);
        }
    }

}

int main(void) {

    decode_morse(0, 0);

    return 0;
}
