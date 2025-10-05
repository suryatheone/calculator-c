#include "../include/token.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Frees all memory associated with a list of tokens.
 */
void free_tokens(Token *tokens, size_t token_count) {
    if (tokens == NULL) return;
    // CRITICAL: We must loop through the tokens and free the allocated memory
    // for each variable name to prevent memory leaks.
    for (size_t i = 0; i < token_count; i++) {
        if (tokens[i].type == TOKEN_TYPE_VARIABLE) {
            free(tokens[i].value.variable_name);
        }
    }
    // Finally, free the array of tokens itself.
    free(tokens);
}

/**
 * @brief A helper function to print tokens, useful for debugging.
 */
void print_tokens(const Token *tokens, size_t token_count) {
  for (size_t i = 0; i < token_count; i++) {
    if (tokens[i].type == TOKEN_TYPE_NUMBER) {
      printf("[%.2f]", tokens[i].value.number);
    } else if (tokens[i].type == TOKEN_TYPE_OPERATOR) {
      printf("[%c]", tokens[i].value.operator);
    } else if (tokens[i].type == TOKEN_TYPE_PARENTHESIS) {
      printf("[%c]", tokens[i].value.operator);
    } else if (tokens[i].type == TOKEN_TYPE_VARIABLE) {
      printf("[VAR:%s]", tokens[i].value.variable_name);
    }
  }
  printf("\n");
}
