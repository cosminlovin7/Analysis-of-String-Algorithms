#ifndef ALGO_H
#define ALGO_H

int maxi(int a, int b);
int *bad_match_pattern(std::string pattern);
void boyer_moore(std::string sentence, std::string pattern, std::ofstream &output);

#endif
