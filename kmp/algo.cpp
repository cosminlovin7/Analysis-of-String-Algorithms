#include <iostream>
#include <cstring>
#include <fstream>
#include <chrono>
#include "algo.h"
#define number_of_characters 256
#define number_of_tests 22

using namespace std;
using namespace std::chrono;

int *lps (char *pattern, int pattern_length) {
    int *lps_vector = (int*)calloc(pattern_length, sizeof(int));
    int len = 0;
    int index = 0;

    while (index < pattern_length) {
        if((int)pattern[len] == (int)pattern[index] && index != 0)
            lps_vector[index++] = ++len;
        else if((int)pattern[len] == (int)pattern[index] && index == 0)
            lps_vector[index++] = 0;
        else if((int)pattern[len] != (int)pattern[index] && len != 0)
            len = lps_vector[len - 1];
        else
            lps_vector[index++] = 0;
    }

    return lps_vector;
}

void kmp (char *pattern, char *sentence, int pattern_length, int sentence_length, ofstream &output) {
    int index_patt = 0;
    int index_sentence = 0;

    int *lps_vector = lps(pattern, pattern_length);

    while(index_sentence < sentence_length) {
        if(sentence[index_sentence] == pattern[index_patt]) {
            index_sentence++;
            index_patt++;
        }
        if(index_patt == pattern_length - 1) {
            output << "Pattern: " << pattern << " found at : " << index_sentence - index_patt << endl;
            index_patt = lps_vector[index_patt - 1];
        }
        else if(index_sentence < sentence_length && pattern[index_patt] != sentence[index_sentence]) {
            if(index_patt != 0)
                index_patt = lps_vector[index_patt - 1];
            else
                index_sentence++;
        }
    }
}

int main()
{
    int k = 0;
    for(k = 0; k < number_of_tests; k++) {
        string in = "in/input" + to_string(k) + ".in";
        string out = "out/output" + to_string(k) + ".out";

        ifstream input(in);
        ofstream output(out);

        //ifstream input("input/input16.in");
        //ofstream output("out/output16.out");

        char *sentence;
        char **patterns;
        int sentence_length;
        int number_of_patterns;
        string buffer;

        getline(input, buffer);
        sentence_length = stoi(buffer);
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
            kmp(patterns[i], sentence, strlen(patterns[i]) + 1, sentence_length, output);
            free(patterns[i]);
        }

        free(sentence);
        free(patterns);
        input.close();
        output.close();
    }
    return 0;
}
