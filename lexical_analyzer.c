#include "lexical_analyzer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Arrays for keywords and operators
const char *keywords[] = {"auto",     "break",   "case",   "char",     "const",
                          "continue", "default", "do",     "double",   "else",
                          "enum",     "extern",  "float",  "for",      "goto",
                          "if",       "int",     "long",   "register", "return",
                          "short",    "signed",  "sizeof", "static",   "struct",
                          "switch",   "typedef", "union",  "unsigned", "void",
                          "volatile", "while"};

const char *operators[] = {"+",  "-",  "*", "/",  "%",  "++", "--",
                           "==", "!=", ">", "<",  ">=", "<=", "&&",
                           "||", "!",  "=", "+=", "-=", "*=", "/=",
                           "%=", "&",  "|", "^",  "~",  "<<", ">>"};

const char *special_chars = "(){}[];,";

int is_keyword(const char *token) {
  for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
    if (strcmp(token, keywords[i]) == 0)
      return 1;
  }
  return 0;
}

int is_operator(const char *token) {
  for (size_t i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
    if (strcmp(token, operators[i]) == 0)
      return 1;
  }
  return 0;
}

void analyze_token(const char *token) {
  if (token[0] == '\0')
    return;

  if (is_keyword(token)) {
    printf("%-20s : Keyword\n", token);
  } else if (isdigit(token[0])) {
    // Simple numeric check, could be improved for floats
    printf("%-20s : Numeric Constant\n", token);
  } else if (token[0] == '"') {
    printf("%-20s : String Literal\n", token);
  } else if (isalpha(token[0]) || token[0] == '_') {
    printf("%-20s : Identifier\n", token);
  } else if (is_operator(token)) {
    printf("%-20s : Operator\n", token);
  } else if (strlen(token) == 1 && strchr(special_chars, token[0])) {
    printf("%-20s : Special Character\n", token);
  } else {
    printf("%-20s : Unknown Token\n", token);
  }
}

void process_line(char *line, int *brace_count) {
  int i = 0;
  int len = strlen(line);

  // Skip leading whitespace
  while (i < len && isspace(line[i]))
    i++;

  // Check for pre-processor directive
  if (line[i] == '#') {
    printf("%-20s : Preprocessor Directive\n", line + i);
    return;
  }

  char token[MAX_TOKEN_LEN];
  int t_idx = 0;

  while (i < len) {
    if (isspace(line[i])) {
      if (t_idx > 0) {
        token[t_idx] = '\0';
        analyze_token(token);
        t_idx = 0;
      }
      i++;
      continue;
    }

    // Handle string literals
    if (line[i] == '"') {
      if (t_idx > 0) {
        token[t_idx] = '\0';
        analyze_token(token);
        t_idx = 0;
      }
      token[t_idx++] = line[i++];
      while (i < len && line[i] != '"') {
        token[t_idx++] = line[i++];
      }
      if (i < len)
        token[t_idx++] = line[i++];
      token[t_idx] = '\0';
      analyze_token(token);
      t_idx = 0;
      continue;
    }

    // Handle single-character special chars and potential multi-char operators
    if (strchr(special_chars, line[i]) || strchr("+-*/%=!><&|^~", line[i])) {
      if (t_idx > 0) {
        token[t_idx] = '\0';
        analyze_token(token);
        t_idx = 0;
      }

      // Count braces
      if (line[i] == '{')
        (*brace_count)++;
      if (line[i] == '}')
        (*brace_count)--;

      // Check for multi-char operators (simple lookahead)
      token[t_idx++] = line[i++];
      if (i < len && strchr("+-=><!&|", line[i])) {
        char temp[3] = {token[0], line[i], '\0'};
        if (is_operator(temp)) {
          token[t_idx++] = line[i++];
        }
      }
      token[t_idx] = '\0';
      analyze_token(token);
      t_idx = 0;
      continue;
    }

    // Build identifiers/keywords/numbers
    token[t_idx++] = line[i++];
    if (t_idx >= MAX_TOKEN_LEN - 1) {
      token[t_idx] = '\0';
      analyze_token(token);
      t_idx = 0;
    }
  }

  if (t_idx > 0) {
    token[t_idx] = '\0';
    analyze_token(token);
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <filename.c>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (!file) {
    perror("Error opening file");
    return 1;
  }

  char line[MAX_LINE_LEN];
  int brace_count = 0;
  int line_num = 0;

  printf("%-20s : %s\n", "TOKEN", "TYPE");
  printf("----------------------------------------\n");

  while (fgets(line, sizeof(line), file)) {
    line_num++;
    // Remove newline
    line[strcspn(line, "\n")] = 0;
    process_line(line, &brace_count);
  }

  if (brace_count != 0) {
    printf("\n[ERROR] Unbalanced braces detected!\n");
  }

  fclose(file);
  return 0;
}
