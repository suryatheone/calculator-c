#include "../include/evaluator.h"
#include "../include/token.h"
#include "../include/variable.h"
#include <stdio.h>

/**
 * @brief Evaluates an expression in postfix (RPN) order.
 */
double evaluatePostfix(const Token *postfix_tokens, size_t token_count) {
  double stack[100] = {0};
  size_t stack_size = 0;

  for (size_t i = 0; i < token_count; i++) {
    if (postfix_tokens[i].type == TOKEN_TYPE_NUMBER) {
      stack[stack_size++] = postfix_tokens[i].value.number;
    } else if (postfix_tokens[i].type == TOKEN_TYPE_VARIABLE) {
      double value = getVariableValue(postfix_tokens[i].value.variable_name);
      stack[stack_size++] = value;
    } else if (postfix_tokens[i].type == TOKEN_TYPE_OPERATOR) {
      if (stack_size < 2) {
          fprintf(stderr, "Error: Invalid expression for operator '%c'\n", postfix_tokens[i].value.operator);
          return 0;
      }
      double b = stack[--stack_size];
      double a = stack[--stack_size];
      switch (postfix_tokens[i].value.operator) {
      case '+': stack[stack_size++] = a + b; break;
      case '-': stack[stack_size++] = a - b; break;
      case '*': stack[stack_size++] = a * b; break;
      case '/': stack[stack_size++] = a / b; break;
      default:
          fprintf(stderr, "Error: Unknown operator in evaluation: %c\n", postfix_tokens[i].value.operator);
          return 0;
      }
    }
  }
  return (stack_size > 0) ? stack[0] : 0;
}
