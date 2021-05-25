#include <bits/stdc++.h>
#include "algo.h"
using namespace std;
using namespace std::chrono;
# define number_of_characters 256
# define number_of_tests 22

int maxi(int a, int b) {
    if(a > b)
        return a;
    return b;
}

int *bad_match_pattern(string pattern)
{
    int i;
    int *bad_match_array = (int*) calloc(number_of_characters, sizeof(int));
    memset(bad_match_array, -1, sizeof *bad_match_array);
    for (i = 0; i < (int) pattern.size(); i++)
        bad_match_array[(int)pattern[i]] = i;

    return bad_match_array;
}

void boyer_moore(string sentence, string pattern, ofstream &output)
{
    int pattern_length = pattern.size();
    int sentence_length = sentence.size();

    int *bad_match_array = bad_match_pattern(pattern);

    int index = 0;
    while(index <= (sentence_length - pattern_length)) {
        int pattern_index = pattern_length - 1;

        while(pattern_index >= 0 && pattern[pattern_index] == sentence[index + pattern_index])
            pattern_index--;

        if (pattern_index < 0) {
            output << "Pattern: " << pattern << " found at : " <<  index << endl;

            if(index + pattern_length < sentence_length)
                index += pattern_length - bad_match_array[(int) sentence[index + pattern_length]];
            else
                index += 1;
        } else
            index += maxi(1, pattern_index - bad_match_array[(int) sentence[index + pattern_index]]);
    }

    free(bad_match_array);
}

int main()
{
    ofstream outtime("time.out");
    int k = 0;
    for(k = 0; k < number_of_tests; k++) {
        string in = "in/input" + to_string(k) + ".in";
        string out = "out/output" + to_string(k) + ".out";

        ifstream input(in);
        ofstream output(out);

        //ifstream input("input/test.in");
        //ofstream output("test.out");

        string text;
        getline(input, text);
        string buffer;
        getline(input, buffer);
        int number_of_patterns = stoi(buffer);
        string patterns[number_of_patterns];

        for(int i = 0; i < number_of_patterns; i++) {
            getline(input, buffer);
            patterns[i] = buffer;
        }

        auto start = high_resolution_clock::now();
        for(int i = 0; i < number_of_patterns; i++) {
            boyer_moore(text, patterns[i], output);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        outtime << k << " : " << duration.count() << endl;

        input.close();
        output.close();
    }
    outtime.close();
    return 0;
}
