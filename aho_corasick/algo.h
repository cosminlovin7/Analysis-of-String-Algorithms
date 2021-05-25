#ifndef ALGO_H
#define ALGO_H

int buildMatchingMachine(std::string patterns[], int patterns_number);
int findNextState(int currentState, char nextInput);
void searchWords(std::string patterns[], int number_of_patterns, std::string text, std::ofstream &output);

#endif
