
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../include/token.h"
#include <stdlib.h>
#include <string.h>

// Test case for freeing a simple list of tokens
void test_free_tokens_simple(void) {
    Token *tokens = malloc(2 * sizeof(Token));
    CU_ASSERT_PTR_NOT_NULL(tokens);

    tokens[0].type = TOKEN_TYPE_NUMBER;
    tokens[0].value.number = 123;

    tokens[1].type = TOKEN_TYPE_OPERATOR;
    tokens[1].value.operator = '+';

    // This test mainly checks if the function runs without crashing.
    free_tokens(tokens, 2);
    CU_PASS("free_tokens_simple completed without crash.");
}

// Test case for freeing tokens including a variable
void test_free_tokens_with_variable(void) {
    Token *tokens = malloc(3 * sizeof(Token));
    CU_ASSERT_PTR_NOT_NULL(tokens);

    tokens[0].type = TOKEN_TYPE_VARIABLE;
    // Duplicate string to ensure it can be safely freed
    char *var_name = strdup("my_var");
    CU_ASSERT_PTR_NOT_NULL(var_name);
    tokens[0].value.variable_name = var_name;

    tokens[1].type = TOKEN_TYPE_OPERATOR;
    tokens[1].value.operator = '=';

    tokens[2].type = TOKEN_TYPE_NUMBER;
    tokens[2].value.number = 45.6;

    // This test checks if it correctly frees the dynamically allocated variable name.
    free_tokens(tokens, 3);
    CU_PASS("free_tokens_with_variable completed without crash.");
}

// Test case for freeing an empty list of tokens
void test_free_tokens_empty(void) {
    free_tokens(NULL, 0);
    CU_PASS("free_tokens with NULL input did not crash.");
}

int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("Token_Suite", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test_free_tokens_simple", test_free_tokens_simple)) ||
        (NULL == CU_add_test(pSuite, "test_free_tokens_with_variable", test_free_tokens_with_variable)) ||
        (NULL == CU_add_test(pSuite, "test_free_tokens_empty", test_free_tokens_empty)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
