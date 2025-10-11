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
  case ',': return -1;
  default: return -1;
  }
}

static int get_precedence(Token t) {
  if (t.type == TOKEN_TYPE_OPERATOR) {
    return precedence(t.value.operator);
  } else if (t.type == TOKEN_TYPE_FUNCTION) {
    return 3; // Higher than operators
  }
  return -1;
}

Token *infixToPostfix(const Token *infix_tokens, size_t infix_size, size_t *postfix_size) {
  Token operator_stack[100];
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
    } else if (current_token.type == TOKEN_TYPE_FUNCTION) {
        operator_stack[operator_stack_size++] = current_token;
    } else if (current_token.type == TOKEN_TYPE_PARENTHESIS) {
      if (current_token.value.operator == '(') {
        operator_stack[operator_stack_size].type = TOKEN_TYPE_PARENTHESIS;
        operator_stack[operator_stack_size].value.operator = '(';
        operator_stack_size++;
      } else { // ')'
        while (operator_stack_size > 0 && !(operator_stack[operator_stack_size - 1].type == TOKEN_TYPE_PARENTHESIS && operator_stack[operator_stack_size - 1].value.operator == '(')) {
          Token top = operator_stack[--operator_stack_size];
          postfix_tokens[*postfix_size] = top;
          if (top.type == TOKEN_TYPE_FUNCTION) {
            postfix_tokens[*postfix_size].value.variable_name = strdup(top.value.variable_name);
          }
          (*postfix_size)++;
        }
        if (operator_stack_size == 0) {
          fprintf(stderr, "Mismatched parentheses\n");
          free_tokens(postfix_tokens, *postfix_size);
          return NULL;
        }
        operator_stack_size--; // Pop the '('.
        // Check if there's a function to pop
        if (operator_stack_size > 0 && operator_stack[operator_stack_size - 1].type == TOKEN_TYPE_FUNCTION) {
          Token func = operator_stack[--operator_stack_size];
          postfix_tokens[*postfix_size] = func;
          postfix_tokens[*postfix_size].value.variable_name = strdup(func.value.variable_name);
          (*postfix_size)++;
        }
      }
    } else if (current_token.type == TOKEN_TYPE_OPERATOR) {
      while (operator_stack_size > 0 && operator_stack[operator_stack_size - 1].type != TOKEN_TYPE_PARENTHESIS &&
             get_precedence(current_token) <= get_precedence(operator_stack[operator_stack_size - 1])) {
        Token top = operator_stack[--operator_stack_size];
        postfix_tokens[*postfix_size] = top;
        if (top.type == TOKEN_TYPE_FUNCTION) {
          postfix_tokens[*postfix_size].value.variable_name = strdup(top.value.variable_name);
        }
        (*postfix_size)++;
      }
      operator_stack[operator_stack_size++] = current_token;
    }
  }

  while (operator_stack_size > 0) {
    if (operator_stack[operator_stack_size - 1].type == TOKEN_TYPE_PARENTHESIS) {
        fprintf(stderr, "Mismatched parentheses\n");
        free_tokens(postfix_tokens, *postfix_size);
        return NULL;
    }
    Token top = operator_stack[--operator_stack_size];
    postfix_tokens[*postfix_size] = top;
    if (top.type == TOKEN_TYPE_FUNCTION) {
      postfix_tokens[*postfix_size].value.variable_name = strdup(top.value.variable_name);
    }
    (*postfix_size)++;
  }

  return postfix_tokens;
}
