#include <iostream>
#include <set>
#include <string>

using namespace std;

string letter_to_morse[] = {
    ".-",
    "-...",
    "-.-.",
    "-..",
    ".",
    "..-.",
    "--.",
    "....",
    "..",
    ".---",
    "-.-",
    ".-..",
    "--",
    "-.",
    "---",
    ".--.",
    "--.-",
    ".-.",
    "...",
    "-",
    "..-",
    "...-",
    ".--",
    "-..-",
    "-.--",
    "--..",
};

string input_string;
set<string> dictionnary;
int dic_size;
volatile int result;

string convert_to_morse (string word) {
    string result = "";
    for (int i = 0; i < word.size(); ++i) {
        result += letter_to_morse[word[i]-65];
    }
    return result;
}

void match_morse (int input_string_index) {
    for (int i = 0; i < input_string.size() - input_string_index; i++) {
        if (dictionnary.find(input_string.substr(input_string_index, i + 1)) != dictionnary.end()) {
            if (input_string_index + i + 1 == input_string.size())
                result ++;
            match_morse(input_string_index + i + 1);
        }
    }
}

int main(void) {
    int n;
    string word;

    cin >> n;
    for(int i = 0; i < n; i++) {
        result = 0;
        cin >> input_string;
        cin >> dic_size;
        for(int j = 0; j < dic_size; j++) {
            cin >> word;
            dictionnary.insert(convert_to_morse(word));
        }

        match_morse(0);
        cout << result << endl << endl;
    }

    return 0;
}
