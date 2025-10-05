#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>

// --- Data Structure Definitions ---

/**
 * @enum TokenType
 * @brief Defines the various types of tokens that the tokenizer can produce.
 */
typedef enum {
  TOKEN_TYPE_NUMBER,
  TOKEN_TYPE_OPERATOR,
  TOKEN_TYPE_PARENTHESIS,
  TOKEN_TYPE_VARIABLE,
} TokenType;

/**
 * @union TokenValue
 * @brief A token can hold one of several types of values.
 */
typedef union {
  double number;
  char operator;
  char *variable_name;
} TokenValue;

/**
 * @struct Token
 * @brief Represents a single token, containing its type and its value.
 */
typedef struct {
  TokenType type;
  TokenValue value;
} Token;

// --- Function Prototypes ---

/**
 * @brief Frees all memory associated with a list of tokens.
 * @param tokens The array of tokens to free.
 * @param token_count The number of tokens in the array.
 */
void free_tokens(Token *tokens, size_t token_count);

/**
 * @brief A helper function to print tokens, useful for debugging.
 */
void print_tokens(const Token *tokens, size_t token_count);

#endif // TOKEN_H
