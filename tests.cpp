#include <stdio.h>

#include "tests.h"
#include "constants.h"
#include "utils.h"
#include "solver.h"


bool run_tests()
{
    Equation equations[] = {{1, -5, 4}, {.r_count = TWO_ROOTS, .roots = {1, 4}},
                            {1, -2, 1}, {.r_count = ONE_ROOT, .roots = {1, 0}},
                            {1, 0, 5}, {.r_count = NO_ROOTS, .roots = {0, 0}},
                            {0, 2, 5}, {.r_count = ONE_ROOT, .roots = {-2.5, 0}}, {0, -1, 0}, {.r_count = ONE_ROOT, .roots = {0, 0}},
                            {0, 0, 5}, {.r_count = NO_ROOTS, .roots = {0, 0}},
                            {0, 0, 0}, {.r_count = INFINITE_ROOTS, .roots = {0, 0}}};

    int len_equations = sizeof(equations) / sizeof(*equations);
    bool correctness_flag = true;

    for (int index = 0; index < len_equations; index += 2)
        if (!one_test(&equations[index], &equations[index + 1]))
            correctness_flag = false;
    
    return correctness_flag; 
}


bool one_test(Equation * eq, Equation * eq_ref)
{
    solve_equation(eq); 

    if (eq->r_count == eq_ref->r_count && is_equal(eq->roots[0], eq_ref->roots[0])
        && is_equal(eq->roots[1], eq_ref->roots[1]))
        return true;
    

    printf("ERROR IN FUNCTION: 'one_test' in the equation with coefficients a = %.5lf, b = %.5lf, c = %.5lf\n"
           "Incorrect number of roots or incorrect roots:\n", eq->a, eq->b, eq->c);

    printf("r_count = %s (should be r_count = %s)\n"
           "x1 = %.5lf, x2 = %.5lf (should be x1 = %.5lf, x2 = %.5lf)\n",
           r_count_to_str(eq->r_count), r_count_to_str(eq_ref->r_count),
           eq->roots[0], eq->roots[1], eq_ref->roots[0], eq_ref->roots[1]);

    return false;
}
