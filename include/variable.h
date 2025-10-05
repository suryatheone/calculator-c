#ifndef VARIABLE_H
#define VARIABLE_H

#include <stddef.h>

// --- Data Structure Definition ---

/**
 * @struct Variable
 * @brief Represents a variable in our symbol table, mapping a name to a value.
 */
typedef struct {
  char *name;
  double value;
} Variable;

// --- Global Symbol Table ---

extern Variable variables[256];
extern size_t variable_count;

// --- Symbol Table Management Functions ---

/**
 * @brief Retrieves the value of a variable from the symbol table.
 * @param name The name of the variable to look up.
 * @return The double value of the variable, or 0.0 if not found.
 */
double getVariableValue(const char *name);

/**
 * @brief Sets a variable in the symbol table. If it exists, it's updated.
 *        If not, a new variable is created.
 * @param name The name of the variable to set.
 * @param value The new value for the variable.
 */
void setVariableValue(const char *name, double value);

/**
 * @brief Frees memory allocated for variable names in the symbol table.
 */
void free_variables();

#endif // VARIABLE_H
