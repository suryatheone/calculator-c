
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../include/variable.h"
#include <stdlib.h>

// This function will be called before each test
int init_suite(void) {
    // Reset variable count before each test to ensure isolation
    free_variables();
    variable_count = 0;
    return 0;
}

void test_set_and_get_variable(void) {
    setVariableValue("x", 10.5);
    double val = getVariableValue("x");
    CU_ASSERT_DOUBLE_EQUAL(val, 10.5, 0.001);
}

void test_update_variable(void) {
    setVariableValue("y", 20.0);
    setVariableValue("y", 30.0); // Update the value
    double val = getVariableValue("y");
    CU_ASSERT_DOUBLE_EQUAL(val, 30.0, 0.001);
}

void test_get_nonexistent_variable(void) {
    // This should return 0.0 as per the implementation
    double val = getVariableValue("nonexistent");
    CU_ASSERT_DOUBLE_EQUAL(val, 0.0, 0.001);
}

void test_set_multiple_variables(void) {
    setVariableValue("a", 1.0);
    setVariableValue("b", 2.0);
    CU_ASSERT_DOUBLE_EQUAL(getVariableValue("a"), 1.0, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(getVariableValue("b"), 2.0, 0.001);
}

void test_free_variables_does_not_crash(void) {
    setVariableValue("temp1", 1);
    setVariableValue("temp2", 2);
    free_variables(); 
    variable_count = 0; // Reset manually after freeing
    CU_PASS("free_variables completed without crash.");
    // After freeing, getting a variable should fail gracefully
    CU_ASSERT_DOUBLE_EQUAL(getVariableValue("temp1"), 0.0, 0.001);
}


int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("Variable_Suite", init_suite, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test_set_and_get_variable", test_set_and_get_variable)) ||
        (NULL == CU_add_test(pSuite, "test_update_variable", test_update_variable)) ||
        (NULL == CU_add_test(pSuite, "test_get_nonexistent_variable", test_get_nonexistent_variable)) ||
        (NULL == CU_add_test(pSuite, "test_set_multiple_variables", test_set_multiple_variables)) ||
        (NULL == CU_add_test(pSuite, "test_free_variables_does_not_crash", test_free_variables_does_not_crash)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
