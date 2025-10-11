#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../include/evaluator.h"
#include "../include/tokenizer.h"
#include "../include/parser.h"
#include "../include/token.h"
#include "../include/variable.h"
#include <stdlib.h>
#include <math.h>

// Test case for sin function
void test_evaluate_sin_function(void) {
    const char *input = "sin(0)";
    size_t token_count;
    Token *tokens = tokenize(input, &token_count);
    CU_ASSERT_PTR_NOT_NULL(tokens);

    size_t postfix_token_count;
    Token *postfix_tokens = infixToPostfix(tokens, token_count, &postfix_token_count);
    CU_ASSERT_PTR_NOT_NULL(postfix_tokens);

    double result = evaluatePostfix(postfix_tokens, postfix_token_count);
    CU_ASSERT_DOUBLE_EQUAL(result, 0.0, 0.001);

    free_tokens(tokens, token_count);
    free_tokens(postfix_tokens, postfix_token_count);
}

// Test case for cos function
void test_evaluate_cos_function(void) {
    const char *input = "cos(0)";
    size_t token_count;
    Token *tokens = tokenize(input, &token_count);
    CU_ASSERT_PTR_NOT_NULL(tokens);

    size_t postfix_token_count;
    Token *postfix_tokens = infixToPostfix(tokens, token_count, &postfix_token_count);
    CU_ASSERT_PTR_NOT_NULL(postfix_tokens);

    double result = evaluatePostfix(postfix_tokens, postfix_token_count);
    CU_ASSERT_DOUBLE_EQUAL(result, 1.0, 0.001);

    free_tokens(tokens, token_count);
    free_tokens(postfix_tokens, postfix_token_count);
}

// Test case for sqrt function
void test_evaluate_sqrt_function(void) {
    const char *input = "sqrt(4)";
    size_t token_count;
    Token *tokens = tokenize(input, &token_count);
    CU_ASSERT_PTR_NOT_NULL(tokens);

    size_t postfix_token_count;
    Token *postfix_tokens = infixToPostfix(tokens, token_count, &postfix_token_count);
    CU_ASSERT_PTR_NOT_NULL(postfix_tokens);

    double result = evaluatePostfix(postfix_tokens, postfix_token_count);
    CU_ASSERT_DOUBLE_EQUAL(result, 2.0, 0.001);

    free_tokens(tokens, token_count);
    free_tokens(postfix_tokens, postfix_token_count);
}

// Test case for log function
void test_evaluate_log_function(void) {
    const char *input = "log(2.718)";
    size_t token_count;
    Token *tokens = tokenize(input, &token_count);
    CU_ASSERT_PTR_NOT_NULL(tokens);

    size_t postfix_token_count;
    Token *postfix_tokens = infixToPostfix(tokens, token_count, &postfix_token_count);
    CU_ASSERT_PTR_NOT_NULL(postfix_tokens);

    double result = evaluatePostfix(postfix_tokens, postfix_token_count);
    CU_ASSERT_DOUBLE_EQUAL(result, 1.0, 0.01); // log(e) ≈ 1

    free_tokens(tokens, token_count);
    free_tokens(postfix_tokens, postfix_token_count);
}

// Test case for function with expression inside
void test_evaluate_function_with_expression(void) {
    const char *input = "sin(3.14159 / 2)";
    size_t token_count;
    Token *tokens = tokenize(input, &token_count);
    CU_ASSERT_PTR_NOT_NULL(tokens);

    size_t postfix_token_count;
    Token *postfix_tokens = infixToPostfix(tokens, token_count, &postfix_token_count);
    CU_ASSERT_PTR_NOT_NULL(postfix_tokens);

    double result = evaluatePostfix(postfix_tokens, postfix_token_count);
    CU_ASSERT_DOUBLE_EQUAL(result, 1.0, 0.01); // sin(π/2) ≈ 1

    free_tokens(tokens, token_count);
    free_tokens(postfix_tokens, postfix_token_count);
}

int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("Evaluator_Function_Suite", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test_evaluate_sin_function", test_evaluate_sin_function)) ||
        (NULL == CU_add_test(pSuite, "test_evaluate_cos_function", test_evaluate_cos_function)) ||
        (NULL == CU_add_test(pSuite, "test_evaluate_sqrt_function", test_evaluate_sqrt_function)) ||
        (NULL == CU_add_test(pSuite, "test_evaluate_log_function", test_evaluate_log_function)) ||
        (NULL == CU_add_test(pSuite, "test_evaluate_function_with_expression", test_evaluate_function_with_expression)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}