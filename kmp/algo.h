#ifndef ALGO_H
#define ALGO_H

int *lps (char *pattern, int pattern_length);
void kmp (char *pattern, char *sentence, int pattern_length, int sentence_length, std::ofstream &output);

#endif
