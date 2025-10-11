#include "../include/evaluator.h"
#include "../include/token.h"
#include "../include/variable.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

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
    } else if (postfix_tokens[i].type == TOKEN_TYPE_FUNCTION) {
       const char *func = postfix_tokens[i].value.variable_name;
       // Two-argument functions
       if (strcmp(func, "pow") == 0 || strcmp(func, "fmod") == 0 || strcmp(func, "atan2") == 0 || strcmp(func, "hypot") == 0 ||
           strcmp(func, "fmin") == 0 || strcmp(func, "fmax") == 0) {
         if (stack_size < 2) {
           fprintf(stderr, "Error: Function '%s' requires 2 arguments\n", func);
           return 0;
         }
         double b = stack[--stack_size];
         double a = stack[--stack_size];
         if (strcmp(func, "pow") == 0) {
           stack[stack_size++] = pow(a, b);
         } else if (strcmp(func, "fmod") == 0) {
           stack[stack_size++] = fmod(a, b);
         } else if (strcmp(func, "atan2") == 0) {
           stack[stack_size++] = atan2(a, b);
         } else if (strcmp(func, "hypot") == 0) {
           stack[stack_size++] = hypot(a, b);
         } else if (strcmp(func, "fmin") == 0) {
           stack[stack_size++] = fmin(a, b);
         } else if (strcmp(func, "fmax") == 0) {
           stack[stack_size++] = fmax(a, b);
         }
       } else {
         // One-argument functions
         if (stack_size < 1) {
           fprintf(stderr, "Error: Function '%s' requires 1 argument\n", func);
           return 0;
         }
         double a = stack[--stack_size];
         if (strcmp(func, "sin") == 0) {
           stack[stack_size++] = sin(a);
         } else if (strcmp(func, "cos") == 0) {
           stack[stack_size++] = cos(a);
         } else if (strcmp(func, "tan") == 0) {
           stack[stack_size++] = tan(a);
         } else if (strcmp(func, "asin") == 0) {
           stack[stack_size++] = asin(a);
         } else if (strcmp(func, "acos") == 0) {
           stack[stack_size++] = acos(a);
         } else if (strcmp(func, "atan") == 0) {
           stack[stack_size++] = atan(a);
         } else if (strcmp(func, "sinh") == 0) {
           stack[stack_size++] = sinh(a);
         } else if (strcmp(func, "cosh") == 0) {
           stack[stack_size++] = cosh(a);
         } else if (strcmp(func, "tanh") == 0) {
           stack[stack_size++] = tanh(a);
         } else if (strcmp(func, "asinh") == 0) {
           stack[stack_size++] = asinh(a);
         } else if (strcmp(func, "acosh") == 0) {
           stack[stack_size++] = acosh(a);
         } else if (strcmp(func, "atanh") == 0) {
           stack[stack_size++] = atanh(a);
         } else if (strcmp(func, "exp") == 0) {
           stack[stack_size++] = exp(a);
         } else if (strcmp(func, "log") == 0) {
           stack[stack_size++] = log(a);
         } else if (strcmp(func, "log10") == 0) {
           stack[stack_size++] = log10(a);
         } else if (strcmp(func, "log2") == 0) {
           stack[stack_size++] = log2(a);
         } else if (strcmp(func, "sqrt") == 0) {
           stack[stack_size++] = sqrt(a);
         } else if (strcmp(func, "cbrt") == 0) {
           stack[stack_size++] = cbrt(a);
         } else if (strcmp(func, "ceil") == 0) {
           stack[stack_size++] = ceil(a);
         } else if (strcmp(func, "floor") == 0) {
           stack[stack_size++] = floor(a);
         } else if (strcmp(func, "trunc") == 0) {
           stack[stack_size++] = trunc(a);
         } else if (strcmp(func, "round") == 0) {
           stack[stack_size++] = round(a);
         } else if (strcmp(func, "fabs") == 0) {
           stack[stack_size++] = fabs(a);
         } else if (strcmp(func, "erf") == 0) {
           stack[stack_size++] = erf(a);
         } else if (strcmp(func, "erfc") == 0) {
           stack[stack_size++] = erfc(a);
         } else if (strcmp(func, "tgamma") == 0) {
           stack[stack_size++] = tgamma(a);
         } else if (strcmp(func, "lgamma") == 0) {
           stack[stack_size++] = lgamma(a);
         } else {
           fprintf(stderr, "Error: Unknown function '%s'\n", func);
           return 0;
         }
       }
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
