
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../include/parser.h"
#include "../include/token.h"
#include <stdlib.h>

// Helper function to create a number token
Token create_number_token(double value) {
    Token t; 
    t.type = TOKEN_TYPE_NUMBER; 
    t.value.number = value; 
    return t;
}

// Helper function to create an operator token
Token create_operator_token(char op) {
    Token t; 
    t.type = TOKEN_TYPE_OPERATOR; 
    t.value.operator = op; 
    return t;
}

// Helper function to create a parenthesis token
Token create_paren_token(char p) {
    Token t; 
    t.type = TOKEN_TYPE_PARENTHESIS; 
    t.value.operator = p; 
    return t;
}

void test_simple_addition(void) {
    Token infix[] = {create_number_token(3), create_operator_token('+'), create_number_token(4)};
    size_t postfix_size;
    Token *postfix = infixToPostfix(infix, 3, &postfix_size);

    CU_ASSERT_PTR_NOT_NULL(postfix);
    CU_ASSERT_EQUAL(postfix_size, 3);
    CU_ASSERT_EQUAL(postfix[0].type, TOKEN_TYPE_NUMBER);
    CU_ASSERT_DOUBLE_EQUAL(postfix[0].value.number, 3, 0.001);
    CU_ASSERT_EQUAL(postfix[1].type, TOKEN_TYPE_NUMBER);
    CU_ASSERT_DOUBLE_EQUAL(postfix[1].value.number, 4, 0.001);
    CU_ASSERT_EQUAL(postfix[2].type, TOKEN_TYPE_OPERATOR);
    CU_ASSERT_EQUAL(postfix[2].value.operator, '+');

    free_tokens(postfix, postfix_size);
}

void test_precedence(void) {
    Token infix[] = {create_number_token(3), create_operator_token('+'), create_number_token(4), create_operator_token('*'), create_number_token(2)};
    size_t postfix_size;
    Token *postfix = infixToPostfix(infix, 5, &postfix_size);

    CU_ASSERT_PTR_NOT_NULL(postfix);
    CU_ASSERT_EQUAL(postfix_size, 5);
    // Expected: 3 4 2 * +
    CU_ASSERT_EQUAL(postfix[0].type, TOKEN_TYPE_NUMBER);
    CU_ASSERT_DOUBLE_EQUAL(postfix[0].value.number, 3, 0.001);
    CU_ASSERT_EQUAL(postfix[1].type, TOKEN_TYPE_NUMBER);
    CU_ASSERT_DOUBLE_EQUAL(postfix[1].value.number, 4, 0.001);
    CU_ASSERT_EQUAL(postfix[2].type, TOKEN_TYPE_NUMBER);
    CU_ASSERT_DOUBLE_EQUAL(postfix[2].value.number, 2, 0.001);
    CU_ASSERT_EQUAL(postfix[3].type, TOKEN_TYPE_OPERATOR);
    CU_ASSERT_EQUAL(postfix[3].value.operator, '*');
    CU_ASSERT_EQUAL(postfix[4].type, TOKEN_TYPE_OPERATOR);
    CU_ASSERT_EQUAL(postfix[4].value.operator, '+');

    free_tokens(postfix, postfix_size);
}

void test_parentheses(void) {
    Token infix[] = {create_paren_token('('), create_number_token(3), create_operator_token('+'), create_number_token(4), create_paren_token(')'), create_operator_token('*'), create_number_token(2)};
    size_t postfix_size;
    Token *postfix = infixToPostfix(infix, 7, &postfix_size);

    CU_ASSERT_PTR_NOT_NULL(postfix);
    CU_ASSERT_EQUAL(postfix_size, 5);
    // Expected: 3 4 + 2 *
    CU_ASSERT_EQUAL(postfix[0].type, TOKEN_TYPE_NUMBER);
    CU_ASSERT_DOUBLE_EQUAL(postfix[0].value.number, 3, 0.001);
    CU_ASSERT_EQUAL(postfix[1].type, TOKEN_TYPE_NUMBER);
    CU_ASSERT_DOUBLE_EQUAL(postfix[1].value.number, 4, 0.001);
    CU_ASSERT_EQUAL(postfix[2].type, TOKEN_TYPE_OPERATOR);
    CU_ASSERT_EQUAL(postfix[2].value.operator, '+');
    CU_ASSERT_EQUAL(postfix[3].type, TOKEN_TYPE_NUMBER);
    CU_ASSERT_DOUBLE_EQUAL(postfix[3].value.number, 2, 0.001);
    CU_ASSERT_EQUAL(postfix[4].type, TOKEN_TYPE_OPERATOR);
    CU_ASSERT_EQUAL(postfix[4].value.operator, '*');

    free_tokens(postfix, postfix_size);
}

void test_mismatched_parentheses(void) {
    Token infix[] = {create_paren_token('('), create_number_token(3), create_operator_token('+'), create_number_token(4)};
    size_t postfix_size;
    Token *postfix = infixToPostfix(infix, 4, &postfix_size);
    CU_ASSERT_PTR_NULL(postfix);
}

int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("Parser_Suite", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test_simple_addition", test_simple_addition)) ||
        (NULL == CU_add_test(pSuite, "test_precedence", test_precedence)) ||
        (NULL == CU_add_test(pSuite, "test_parentheses", test_parentheses)) ||
        (NULL == CU_add_test(pSuite, "test_mismatched_parentheses", test_mismatched_parentheses)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
