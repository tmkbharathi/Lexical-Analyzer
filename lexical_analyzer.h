#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <stdio.h>

#define MAX_TOKEN_LEN 100
#define MAX_LINE_LEN 256

// Arrays for keywords and operators
extern const char *keywords[];
extern const char *operators[];
extern const char *special_chars;

// Function prototypes
int is_keyword(const char *token);
int is_operator(const char *token);
void analyze_token(const char *token);
void process_line(char *line, int *brace_count);

#endif // LEXICAL_ANALYZER_H
