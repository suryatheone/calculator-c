#include "../include/variable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Global Symbol Table ---

Variable variables[256];
size_t variable_count = 0;

/**
 * @brief Retrieves the value of a variable from the symbol table.
 */
double getVariableValue(const char *name) {
  for (size_t i = 0; i < variable_count; i++) {
    if (strcmp(variables[i].name, name) == 0) {
      return variables[i].value;
    }
  }
  fprintf(stderr, "Error: Variable '%s' not found\n", name);
  return 0.0;
}

/**
 * @brief Sets a variable in the symbol table.
 */
void setVariableValue(const char *name, double value) {
  for (size_t i = 0; i < variable_count; i++) {
    if (strcmp(variables[i].name, name) == 0) {
      variables[i].value = value;
      return;
    }
  }
  
  if (variable_count < sizeof(variables) / sizeof(variables[0])) {
    variables[variable_count].name = strdup(name);
    if (variables[variable_count].name == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for variable name.\n");
        return;
    }
    variables[variable_count].value = value;
    variable_count++;
  } else {
    fprintf(stderr, "Error: Variable storage full\n");
  }
}

/**
 * @brief Frees memory allocated for variable names in the symbol table.
 */
void free_variables() {
  for (size_t i = 0; i < variable_count; i++) {
    free(variables[i].name);
  }
}
