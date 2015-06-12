#include <iostream>
#include <cstdio>
#include <climits>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <array>
#include <queue>
#include <stack>
#include <utility>
#include <algorithm>
#include <limits>
#include <cstring>

using namespace std;

#define CROSS_SIZE  40
#define WORD_SIZE   50

int rows_nb, colums_nb;
int dictionnary_size;
char cross_word[CROSS_SIZE][CROSS_SIZE];
bool letter_taken[CROSS_SIZE][CROSS_SIZE];
vector<string> dictionnary (200);
char word[WORD_SIZE];
char global_str[CROSS_SIZE+CROSS_SIZE];

/* Directions :
 * 567
 * 4*0
 * 321
 */
void search_in_string (char *working_str, int where, int dir) {
    string str = string(working_str);
    for (int w = 0; w < (int) dictionnary_size; w++) {
        int index = str.find(dictionnary[w]);
        while (index != (int) string::npos) {
            //printf("Found %s at %d (%s) (case %d %d, size %d)\n", dictionnary[w].c_str(), index, working_str, dir, where, (int) dictionnary[w].size());
            switch (dir) {
                case 0:
                    for (int i = index; i < index + (int) dictionnary[w].size(); i++) {
                        letter_taken[where][i] = true;
                    }
                    break;
                case 4:
                    for (int i = index; i < index + (int) dictionnary[w].size(); i++) {
                        letter_taken[where][colums_nb - 1 - i] = true;
                    }
                    break;
                case 2:
                    for (int i = index; i < index + (int) dictionnary[w].size(); i++) {
                        letter_taken[i][where] = true;
                    }
                    break;
                case 6:
                    for (int i = index; i < index + (int) dictionnary[w].size(); i++) {
                        letter_taken[colums_nb - 1 - i][where] = true;
                    }
                    break;
                case 7:
                    {
                        int x = min(where, rows_nb - 1);
                        int y = max(0, where - rows_nb + 1);
                    for (int i = index; i < index + (int) dictionnary[w].size(); i++) {
                        letter_taken[x-i][y+i] = true;
                    }
                    break;
                    }
                case 3:
                    {
                        int x = min(where, rows_nb - 1);
                        int y = max(0, where - rows_nb + 1);
                        int diag_length = str.length();
                        for (int i = index; i < index + (int) dictionnary[w].size(); i++) {
                            letter_taken[(diag_length-x)+i][(diag_length-y)-i] = true;
                        }
                    }
                    break;
                case 1:
                    {
                        int wrk_column = max(0, where);
                        int x = max(0, -where);
                        for (int i = index; i < index + (int) dictionnary[w].size(); i++) {
                            letter_taken[x+i][wrk_column +i] = true;
                        }
                    }
                    break;
                case 5:
                    {
                        int wrk_column = max(0, where);
                        int x = max(0, -where);
                        int rev_index = str.length() - (index+dictionnary[w].size());
                        for (int i = rev_index; i < rev_index + (int) dictionnary[w].size(); i++) {
                            letter_taken[x+i][wrk_column+i] = true;
                        }
                    }
                    break;
                default :
                    break;
            }
            index = str.find(dictionnary[w], index + 1);
        }
    }
}

void print_result (void) {
    for (int x = 0; x < rows_nb; x++) {
        for (int y = 0; y < colums_nb; y++) {
            printf(" %d", letter_taken[x][y]);
        }
        puts("");
    }
}


int main(void) {

    while (scanf("%d %d", &rows_nb, &colums_nb) == 2) {
        memset(letter_taken, 0, CROSS_SIZE*CROSS_SIZE);
        scanf("%d", &dictionnary_size);
        for (int i = 0; i < dictionnary_size; i++) {
            scanf("%s", word);
            dictionnary[i] = word;
        }
        for (int x = 0; x < rows_nb; x++) {
            scanf("%s", cross_word[x]);
        }

        /* Check word horizontally*/
        for (int x = 0; x < rows_nb; x++) {
            //printf("%s\n", cross_word[x]);
            search_in_string(cross_word[x], x, 0);
            reverse_copy(cross_word[x], cross_word[x] + colums_nb, global_str);
            //printf("%s\n", global_str);
            search_in_string(global_str, x, 4);
            //puts("");
        }
        /* Check word vertically*/
        for (int y = 0; y < colums_nb; y++) {
            for (int x = 0; x < rows_nb; x++) {
                global_str[x] = cross_word[x][y];
            }
            global_str[rows_nb] = '\0';
            //printf("%s\n", global_str);
            search_in_string(global_str, y, 2);
            reverse(global_str, global_str + rows_nb);
            //printf("%s\n", global_str);
            search_in_string(global_str, y, 6);
            //puts("");
        }
        /* Check on first diagonals*/
        int wrk_row;
        for (int x = 0; x < rows_nb + colums_nb - 1; x++) {
            wrk_row = min(x, rows_nb - 1);

            int i;
            int y = max(0, x-rows_nb+1);
            for (i = 0; i <= wrk_row && i+y < colums_nb; i++) {
                global_str[i] = cross_word[wrk_row-i][i+y];
            }
            global_str[i] = '\0';
            //printf("Diag1: %s\n", global_str);
            search_in_string(global_str, x, 7);
            reverse(global_str, global_str+i);
            //printf("       %s\n", global_str);
            search_in_string(global_str, x, 3);
            //puts("");
        }
        /* Check on second diagonals*/
        int wrk_column;
        for (int y = - rows_nb + 1; y < colums_nb; y++) {
            wrk_column = max(0, y);
            int x = max(0, -y);
            int i;
            for (i = 0; x+i < rows_nb && wrk_column+i < colums_nb; i++) {
                global_str[i] = cross_word[x+i][wrk_column +i];
            }
            global_str[i] = '\0';
            //printf("Diag2: %s\n", global_str);
            search_in_string(global_str, y, 1);
            reverse(global_str, global_str+i);
            //printf("       %s\n", global_str);
            search_in_string(global_str, y, 5);
            //puts("");
        }
        for (int x = 0; x < rows_nb; x++) {
            for (int y = 0; y < colums_nb; y++) {
                if (!letter_taken[x][y])
                    printf("%c", cross_word[x][y]);
            }
        }
        puts("");
    }

    return 0;
}
