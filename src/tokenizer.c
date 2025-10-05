#include "../include/tokenizer.h"
#include "../include/token.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Converts an input string into a sequence of tokens.
 */
Token *tokenize(const char *input, size_t *token_count) {
  size_t capacity = 10;
  Token *tokens = malloc(capacity * sizeof(Token));
  if (!tokens) return NULL;

  *token_count = 0;
  const char *p = input;

  while (*p) {
    while (isspace(*p)) p++;
    if (*p == '\0') break;

    if (isdigit(*p) || (*p == '.' && isdigit(p[1]))) {
      char *end;
      tokens[*token_count].type = TOKEN_TYPE_NUMBER;
      tokens[*token_count].value.number = strtod(p, &end);
      p = end;
    } else if (isalpha(*p)) {
      const char *start = p;
      while (isalnum(*p) || *p == '_') p++;
      size_t len = p - start;
      char *name = malloc(len + 1);
      strncpy(name, start, len);
      name[len] = '\0';
      tokens[*token_count].type = TOKEN_TYPE_VARIABLE;
      tokens[*token_count].value.variable_name = name;
    } else if (strchr("+-*/=", *p)) {
      tokens[*token_count].type = TOKEN_TYPE_OPERATOR;
      tokens[*token_count].value.operator= *p++;
    } else if (*p == '(' || *p == ')') {
      tokens[*token_count].type = TOKEN_TYPE_PARENTHESIS;
      tokens[*token_count].value.operator= *p++;
    } else {
      fprintf(stderr, "Error: Invalid character in input: %c\n", *p);
      free_tokens(tokens, *token_count);
      return NULL;
    }

    (*token_count)++;
    if (*token_count >= capacity) {
      capacity *= 2;
      tokens = realloc(tokens, capacity * sizeof(Token));
      if (!tokens) return NULL;
    }
  }
  return tokens;
}
