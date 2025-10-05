#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "token.h"
#include <stddef.h>

/**
 * @brief Evaluates an expression in postfix (RPN) order.
 * @param postfix_tokens The array of tokens in postfix order.
 * @param token_count The number of postfix tokens.
 * @return The final calculated result as a double.
 */
double evaluatePostfix(const Token *postfix_tokens, size_t token_count);

#endif // EVALUATOR_H
