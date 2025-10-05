#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include <stddef.h>

/**
 * @brief Converts a sequence of infix tokens to postfix (RPN) using Shunting-yard algorithm.
 * @param infix_tokens The array of tokens in infix order.
 * @param infix_size The number of infix tokens.
 * @param postfix_size A pointer to store the resulting number of postfix tokens.
 * @return A new array of tokens in postfix order, or NULL on failure.
 */
Token *infixToPostfix(const Token *infix_tokens, size_t infix_size, size_t *postfix_size);

#endif // PARSER_H
