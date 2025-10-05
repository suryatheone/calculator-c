#include "../include/parser.h"
#include "../include/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int precedence(char operator) {
  switch (operator) {
  case '=': return 0;
  case '+': case '-': return 1;
  case '*': case '/': return 2;
  default: return -1;
  }
}

Token *infixToPostfix(const Token *infix_tokens, size_t infix_size, size_t *postfix_size) {
  char operator_stack[100];
  size_t operator_stack_size = 0;
  Token *postfix_tokens = calloc(infix_size, sizeof(Token));
  if (!postfix_tokens) return NULL;

  *postfix_size = 0;
  for (size_t i = 0; i < infix_size; i++) {
    Token current_token = infix_tokens[i];
    if (current_token.type == TOKEN_TYPE_NUMBER) {
        postfix_tokens[(*postfix_size)++] = current_token;
    } else if (current_token.type == TOKEN_TYPE_VARIABLE) {
        postfix_tokens[*postfix_size] = current_token;
        postfix_tokens[*postfix_size].value.variable_name = strdup(current_token.value.variable_name);
        (*postfix_size)++;
    } else if (current_token.type == TOKEN_TYPE_PARENTHESIS) {
      if (current_token.value.operator== '(') {
        operator_stack[operator_stack_size++] = current_token.value.operator;
      } else { // ')'
        while (operator_stack_size > 0 && operator_stack[operator_stack_size - 1] != '(') {
          postfix_tokens[*postfix_size].type = TOKEN_TYPE_OPERATOR;
          postfix_tokens[(*postfix_size)++].value.operator= operator_stack[--operator_stack_size];
        }
        if (operator_stack_size == 0) {
          fprintf(stderr, "Mismatched parentheses\n");
          free_tokens(postfix_tokens, *postfix_size);
          return NULL;
        }
        operator_stack_size--; // Pop the '('.
      }
    } else if (current_token.type == TOKEN_TYPE_OPERATOR) {
      while (operator_stack_size > 0 && operator_stack[operator_stack_size - 1] != '(' &&
             precedence(current_token.value.operator) <= precedence(operator_stack[operator_stack_size - 1])) {
        postfix_tokens[*postfix_size].type = TOKEN_TYPE_OPERATOR;
        postfix_tokens[(*postfix_size)++].value.operator= operator_stack[--operator_stack_size];
      }
      operator_stack[operator_stack_size++] = current_token.value.operator;
    }
  }

  while (operator_stack_size > 0) {
    if (operator_stack[operator_stack_size - 1] == '(') {
        fprintf(stderr, "Mismatched parentheses\n");
        free_tokens(postfix_tokens, *postfix_size);
        return NULL;
    }
    postfix_tokens[*postfix_size].type = TOKEN_TYPE_OPERATOR;
    postfix_tokens[(*postfix_size)++].value.operator= operator_stack[--operator_stack_size];
  }

  return postfix_tokens;
}
