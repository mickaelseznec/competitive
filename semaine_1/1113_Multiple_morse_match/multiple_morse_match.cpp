#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <set>
#include <string>

using namespace std;

#define MORSE_DEPTH         4
#define MAX_SIZE_STRING     1000

char input_string[MAX_SIZE_STRING];
int input_size;

char morse[] = {0,
    'E', 'T',
    'I', 'A', 'N', 'M',
    'S', 'U', 'R', 'W', 'D', 'K', 'G', 'O',
    'H', 'V', 'F',  0 , 'L',  0 , 'P', 'J', 'B', 'X', 'C', 'Y', 'Z', 'Q',  0 ,  0};

/* Morse weight : how much symbol in morse to express a letter
 * Sorted in alphabetical order
char morse_weight[] = {
    2, 4, 4, 3, 1, 4, 3, // A to G
    4, 2, 4, 3, 4, 2, 2, // H to N
    3, 4, 4, 3, 3, 1, 3, // O to U
    4, 3, 4, 4, 4        // V to Z
};*/

char decoded_string[50];
set<string> dictionnary;
int dic_size;
int result;

inline int move_index (int morse_index, char morse_symbol) {
    morse_index = 2 * (morse_index + 1);

    if (morse_symbol == '.')
        morse_index--;

    return morse_index;
}

bool sub_word_in_dic (string word, set<string>::iterator range_low, set<string>::iterator range_max) {
    //TODO :  a dicotomic search in dictionnary
    for(set<string>::iterator word_dic(range_low); word_dic != range_max; ++word_dic) {
        if((*word_dic).find(word) == 0) {
#ifdef DEBUG
            cout << "Found " << word << " in " << *word_dic << endl;
#endif
            return true;
        }
    }
    return false;
}

/* Each time this function is called, the parser will try to match a letter in
 * one of the selected word (between range_low and range_max)
 *
 * int input_string_index                       where to begin morse caracter search in input string
 * string decoded_string                        string that has been decoded previously : only contains complete words
 * string decoding_word                         word being decoded
 * set<string>::iterator range_low, range_high  where to search in dictionnary
 */
void decode_morse (int input_string_index, string decoded_string, string decoding_word, set<string>::iterator range_low, set<string>::iterator range_max) {
#ifdef DEBUG
    cout << "   Call with : " << input_string_index << "   "  << decoding_word << ":" << decoded_string << endl;
#endif
    int morse_index = 0;

    /* Try to parse using 1 to 4 morse caracters*/
    for (int i = input_string_index; i < input_string_index + MORSE_DEPTH; i++) {
        if (input_string[i] == '\0') {
            break;
        }
        morse_index = move_index(morse_index, input_string[i]);

        /* Find if parsed word is a subword of the dictionnary*/
        if (sub_word_in_dic(decoding_word + morse[morse_index], range_low, range_max)) {
            /* Try to parse with a new word but also continue if the word found in the dictionnary
             * is a subword of another word of the dictionnary*/
            if (dictionnary.find(decoding_word + morse[morse_index]) != dictionnary.end()) {
#ifdef DEBUG
                cout << "       Found ! " << decoding_word+morse[morse_index] << endl;
#endif
                decode_morse(i + 1, decoded_string + decoding_word + morse[morse_index], "", range_low, range_max);
                if(i == input_size - 1)
                    result++;
            }
            decode_morse(i + 1, decoded_string, decoding_word + morse[morse_index], range_low, range_max);
        }
    }
}

int main(void) {
    int n;
    string word;

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> input_string;
        cin >> dic_size;
        for(int j = 0; j < dic_size; j++) {
            cin >> word;
            dictionnary.insert(word);
        }

        input_size = strlen(input_string);
        decode_morse(0, "", "", dictionnary.begin(), dictionnary.end());
        cout << "RESULT : " << result << endl;
    }

    return 0;
}
