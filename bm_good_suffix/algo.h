#ifndef ALGO_H
#define ALGO_H

void preprocess_strong_suffix(int *shift, int *border, char *pattern, int pattern_length);
void bm_good_suffix(char *text, char *pattern, std::ofstream &output);

#endif
