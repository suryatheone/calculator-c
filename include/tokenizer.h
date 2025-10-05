#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"
#include <stddef.h>

/**
 * @brief Converts an input string into a sequence of tokens.
 * @param input The raw mathematical expression string.
 * @param token_count A pointer to a size_t to store the number of tokens found.
 * @return A dynamically allocated array of Tokens, or NULL on failure.
 */
Token *tokenize(const char *input, size_t *token_count);

#endif // TOKENIZER_H
