#include <iostream>
#include <iostream>
#include <cstring>
#include <fstream>
#include <chrono>
#include "algo.h"
#define number_of_characters 256
#define number_of_tests 22
using namespace std;

void preprocess_strong_suffix(int *shift, int *border, char *pattern, int pattern_length)
{
    int i = pattern_length;
    int j = pattern_length + 1;
    border[i] = j;

    while (i > 0)
    {
        while (j <= pattern_length && pattern[i-1] != pattern[j-1]) {
            if (shift[j] == 0)
                shift[j] = j - i;
            j = border[j];
        }
        i--; j--;
        border[i] = j;
    }

    j = border[0];
    for (i = 0; i <= pattern_length; i++) {
        if (shift[i] == 0)
            shift[i] = j;
        if (i == j)
            j = border[j];
    }
}

void bm_good_suffix(char *text, char *pattern, ofstream &output)
{
    int position=0;
    int pattern_length = strlen(pattern);
    int text_length = strlen(text);

    int border[pattern_length + 1];
    int *shift = (int*) calloc(pattern_length + 1, sizeof(int));

    preprocess_strong_suffix(shift, border, pattern, pattern_length);

    int j = 0;
    while(position <= text_length - pattern_length) {
        j = pattern_length - 1;
        while(j >= 0 && pattern[j] == text[position + j])
            j--;
        if (j < 0){
            output << "Pattern: " << pattern << " found at : " << position << endl;
            position += shift[0];
        }
        else
            position += shift[j + 1];
    }

    free(shift);
}

int main()
{
    for(int k = 0; k < number_of_tests; k++) {
        cout << k;
        string in = "in/input" + to_string(k) + ".in";
        string out = "out/output" + to_string(k) + ".out";

        ifstream input(in);
        ofstream output(out);

        //ifstream input("input/input15.in");
        //ofstream output("out/output15.out");

        char *sentence;
        char **patterns;
        int sentence_length;
        int number_of_patterns;
        string buffer;

        getline(input, buffer);
        sentence_length = stoi(buffer);
        //Read the text.
        getline(input, buffer);
        sentence = (char*) malloc(sizeof(char) * sentence_length);
        strcpy(sentence, buffer.c_str());

        getline(input, buffer);
        number_of_patterns = stoi(buffer);

        patterns = (char**) malloc(sizeof(char*) * number_of_patterns);

        for(int i = 0; i < number_of_patterns; i++) {
            getline(input, buffer);
            patterns[i] = (char*) malloc(sizeof(char*) * buffer.length());
            strcpy(patterns[i], buffer.c_str());
        }
        for(int i = 0; i < number_of_patterns; i++) {
            bm_good_suffix(sentence, patterns[i], output);
            free(patterns[i]);
        }

        free(sentence);
        free(patterns);
        input.close();
        output.close();
    }
    return 0;
}
