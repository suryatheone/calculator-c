#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/token.h"
#include "../include/tokenizer.h"
#include "../include/parser.h"
#include "../include/evaluator.h"
#include "../include/variable.h"

void processExpression(const char *expression) {
  size_t token_count;
  Token *tokens = tokenize(expression, &token_count);
  if (!tokens) return;

  // printf("Tokens: ");
  // print_tokens(tokens, token_count);

  if (token_count > 2 && tokens[0].type == TOKEN_TYPE_VARIABLE &&
      tokens[1].type == TOKEN_TYPE_OPERATOR && tokens[1].value.operator== '=') {

    Token *right_side_tokens = tokens + 2;
    size_t right_side_count = token_count - 2;
    size_t postfix_token_count;
    Token *postfix_tokens = infixToPostfix(right_side_tokens, right_side_count, &postfix_token_count);

    if (postfix_tokens) {
      double result = evaluatePostfix(postfix_tokens, postfix_token_count);
      setVariableValue(tokens[0].value.variable_name, result);
      printf("Variable '%s' set to %.2f\n", tokens[0].value.variable_name, result);
      free_tokens(postfix_tokens, postfix_token_count);
    }
  } else {
    size_t postfix_token_count;
    Token *postfix_tokens = infixToPostfix(tokens, token_count, &postfix_token_count);
    if (postfix_tokens) {
      // printf("Postfix: ");
      // print_tokens(postfix_tokens, postfix_token_count);
      double result = evaluatePostfix(postfix_tokens, postfix_token_count);
      printf("Result: %.2f\n", result);
      free_tokens(postfix_tokens, postfix_token_count);
    }
  }
  free_tokens(tokens, token_count);
}

void printHelp() {
  printf("Enter expressions to be evaluated.\n");
  printf("Examples:\n");
  printf("> 3 + 4 * 2\n");
  printf("Result: 11.00\n\n");
  printf("You can also use variables:\n");
  printf("> x = 10\n");
  printf("Variable 'x' set to 10.00\n");
  printf("> x * 2 + 5\n");
  printf("Result: 25.00\n\n");
  printf("Commands:\n");
  printf("help: Show this help message.\n");
  printf("exit: Exit the calculator.\n");
}

int main() {
  char expression[256];
  printf("Welcome to the expression evaluator!\n");
  printf("Type 'help' for assistance or 'exit' to quit.\n");

  while (1) {
    printf("> ");
    if (fgets(expression, sizeof(expression), stdin) == NULL) break;
    
    expression[strcspn(expression, "\n")] = '\0';

    if (strcmp(expression, "exit") == 0) break;
    if (strcmp(expression, "help") == 0) {
      printHelp();
      continue;
    }
    if (strlen(expression) == 0) continue;

    processExpression(expression);
  }

  free_variables();
  printf("Exiting.\n");
  return 0;
}
