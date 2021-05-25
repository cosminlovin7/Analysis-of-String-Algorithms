#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include "algo.h"
#define number_of_tests 22

using namespace std;

const int MAXS = 1000000;
const int MAXC = 128;

int out[MAXS];
int fail[MAXS];
int gotoo[MAXS][MAXC];
int w[MAXS];

int buildMatchingMachine(string patterns[], int patterns_number)
{
    memset(out, 0, sizeof out);
    memset(gotoo, -1, sizeof gotoo);
    memset(w, -1, sizeof w);
    memset(fail, -1, sizeof fail);
    int states = 1;

    for (int i = 0; i < patterns_number; ++i)
    {
        const string &word = patterns[i];
        int currentState = 0;

        for (int j = 0; j < (int)word.size(); ++j)
        {
            int ch = word[j];

            if (gotoo[currentState][ch] == -1)
                gotoo[currentState][ch] = states++;

            currentState = gotoo[currentState][ch];
        }
        w[currentState] = i;
        out[currentState] = 1;
    }

    for (int ch = 0; ch < MAXC; ++ch)
        if (gotoo[0][ch] == -1)
            gotoo[0][ch] = 0;

    queue<int> q;
    for (int ch = 0; ch < MAXC; ++ch)
    {
        if (gotoo[0][ch] != 0)
        {
            fail[gotoo[0][ch]] = 0;
            q.push(gotoo[0][ch]);
        }
    }

    while (q.size())
    {
        int state = q.front();
        q.pop();

        for (int ch = 0; ch <= MAXC; ++ch)
        {
            if (gotoo[state][ch] != -1)
            {
                int failure = fail[state];
                while (gotoo[failure][ch] == -1)
                      failure = fail[failure];

                failure = gotoo[failure][ch];
                fail[gotoo[state][ch]] = failure;
                q.push(gotoo[state][ch]);
            }
        }
    }

    return states;
}

int findNextState(int currentState, char nextInput)
{
    int answer = currentState;
    int character = nextInput;

    while (gotoo[answer][character] == -1)
        answer = fail[answer];

    return gotoo[answer][character];
}

void searchWords(string patterns[], int number_of_patterns, string text, ofstream &output)
{
    buildMatchingMachine(patterns, number_of_patterns);

    int currentState = 0;
    for (int i = 0; i < (int)text.size(); ++i)
    {
        currentState = findNextState(currentState, text[i]);
        if (out[fail[currentState]] > 0) {
            output << "Pattern: "<< patterns[w[fail[currentState]]] << " found at : " << i - patterns[w[fail[currentState]]].size() + 1 << endl;
        }
        if (out[currentState] == 0)
             continue;
        if (out[currentState] > 0)
            output << "Pattern: "<< patterns[w[currentState]] << " found at : " << i - patterns[w[currentState]].size() + 1 << endl;
    }
}

int main()
{
    for(int k = 0; k < number_of_tests; k++) {
        cout << k;
        string in = "in/input" + to_string(k) + ".in";
        string out = "out/output" + to_string(k) + ".out";

        ifstream input(in);
        ofstream output(out);

        //ifstream input("input1/input1.in");
        //ofstream output("out_aho/output1.out");
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

        searchWords(patterns, number_of_patterns, text, output);
    }

    return 0;
}
