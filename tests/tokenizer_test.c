
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../include/tokenizer.h"
#include "../include/token.h"
#include <stdlib.h>

// Test case for a simple expression
void test_tokenize_simple_expression(void) {
    const char *input = "1 + 2";
    size_t token_count;
    Token *tokens = tokenize(input, &token_count);

    CU_ASSERT_PTR_NOT_NULL(tokens);
    CU_ASSERT_EQUAL(token_count, 3);

    CU_ASSERT_EQUAL(tokens[0].type, TOKEN_TYPE_NUMBER);
    CU_ASSERT_DOUBLE_EQUAL(tokens[0].value.number, 1.0, 0.001);

    CU_ASSERT_EQUAL(tokens[1].type, TOKEN_TYPE_OPERATOR);
    CU_ASSERT_EQUAL(tokens[1].value.operator, '+');

    CU_ASSERT_EQUAL(tokens[2].type, TOKEN_TYPE_NUMBER);
    CU_ASSERT_DOUBLE_EQUAL(tokens[2].value.number, 2.0, 0.001);

    free_tokens(tokens, token_count);
}

// Test case for an expression with parentheses
void test_tokenize_with_parentheses(void) {
    const char *input = "(3 * 4)";
    size_t token_count;
    Token *tokens = tokenize(input, &token_count);

    CU_ASSERT_PTR_NOT_NULL(tokens);
    CU_ASSERT_EQUAL(token_count, 5);

    CU_ASSERT_EQUAL(tokens[0].type, TOKEN_TYPE_PARENTHESIS);
    CU_ASSERT_EQUAL(tokens[0].value.operator, '(');

    CU_ASSERT_EQUAL(tokens[1].type, TOKEN_TYPE_NUMBER);
    CU_ASSERT_DOUBLE_EQUAL(tokens[1].value.number, 3.0, 0.001);
    
    CU_ASSERT_EQUAL(tokens[2].type, TOKEN_TYPE_OPERATOR);
    CU_ASSERT_EQUAL(tokens[2].value.operator, '*');

    CU_ASSERT_EQUAL(tokens[3].type, TOKEN_TYPE_NUMBER);
    CU_ASSERT_DOUBLE_EQUAL(tokens[3].value.number, 4.0, 0.001);

    CU_ASSERT_EQUAL(tokens[4].type, TOKEN_TYPE_PARENTHESIS);
    CU_ASSERT_EQUAL(tokens[4].value.operator, ')');

    free_tokens(tokens, token_count);
}

// Test case for an expression with variables
void test_tokenize_with_variables(void) {
    const char *input = "x = 5";
    size_t token_count;
    Token *tokens = tokenize(input, &token_count);

    CU_ASSERT_PTR_NOT_NULL(tokens);
    CU_ASSERT_EQUAL(token_count, 3);

    CU_ASSERT_EQUAL(tokens[0].type, TOKEN_TYPE_VARIABLE);
    CU_ASSERT_STRING_EQUAL(tokens[0].value.variable_name, "x");

    CU_ASSERT_EQUAL(tokens[1].type, TOKEN_TYPE_OPERATOR);
    CU_ASSERT_EQUAL(tokens[1].value.operator, '=');

    CU_ASSERT_EQUAL(tokens[2].type, TOKEN_TYPE_NUMBER);
    CU_ASSERT_DOUBLE_EQUAL(tokens[2].value.number, 5.0, 0.001);

    free_tokens(tokens, token_count);
}

// Test case for an invalid character
void test_tokenize_invalid_character(void) {
    const char *input = "2 ? 3";
    size_t token_count;
    Token *tokens = tokenize(input, &token_count);
    CU_ASSERT_PTR_NULL(tokens);
}

// Test case for an empty string
void test_tokenize_empty_string(void) {
    const char *input = "";
    size_t token_count;
    Token *tokens = tokenize(input, &token_count);
    CU_ASSERT_PTR_NOT_NULL(tokens);
    CU_ASSERT_EQUAL(token_count, 0);
    free_tokens(tokens, token_count);
}

// Test case for a string with only whitespace
void test_tokenize_whitespace_string(void) {
    const char *input = "   ";
    size_t token_count;
    Token *tokens = tokenize(input, &token_count);
    CU_ASSERT_PTR_NOT_NULL(tokens);
    CU_ASSERT_EQUAL(token_count, 0);
    free_tokens(tokens, token_count);
}

int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("Tokenizer_Suite", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test_tokenize_simple_expression", test_tokenize_simple_expression)) ||
        (NULL == CU_add_test(pSuite, "test_tokenize_with_parentheses", test_tokenize_with_parentheses)) ||
        (NULL == CU_add_test(pSuite, "test_tokenize_with_variables", test_tokenize_with_variables)) ||
        (NULL == CU_add_test(pSuite, "test_tokenize_invalid_character", test_tokenize_invalid_character)) ||
        (NULL == CU_add_test(pSuite, "test_tokenize_empty_string", test_tokenize_empty_string)) ||
        (NULL == CU_add_test(pSuite, "test_tokenize_whitespace_string", test_tokenize_whitespace_string)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
