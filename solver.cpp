#include <math.h>

#include "solver.h"
#include "constants.h"
#include "utils.h"
#include "myassert.h"


void solve_equation(Equation *eq)
{
    MY_ASSERT(eq != NULL, ERR_NULL_PTR, "'eq' must point to a structure");

    if (is_equal(eq->a, 0))
        solve_linear(eq);
    else
        solve_quadratic(eq);

    order_roots(eq);
//  удаление знака нуля -0.0 -> 0.0 
    for (int i = 0; i < MAX_ROOTS; i++)
        if (is_equal(eq->roots[i], 0))
            eq->roots[i] = 0.0;
}


void order_roots(Equation *eq)
{
    MY_ASSERT(eq != NULL, ERR_NULL_PTR, "'eq' must point to a structure");

    if (eq->r_count == TWO_ROOTS && eq->roots[0] > eq->roots[1]) {
        double temp = eq->roots[0];

        eq->roots[0] = eq->roots[1];
        eq->roots[1] = temp;
    }
}


void solve_linear(Equation *eq)
{
    MY_ASSERT(eq != NULL, ERR_NULL_PTR, "'eq' must point to a structure");
    MY_ASSERT(is_equal(eq->a, 0), ERR_UNKNOWN, "in this function the coefficient 'a' must be equal to 0");

    if (is_equal(eq->b, 0) && is_equal(eq->c, 0))
        eq->r_count = INFINITE_ROOTS;
    else if (is_equal(eq->b, 0) && !is_equal(eq->c, 0))
        eq->r_count = NO_ROOTS;
    else {
        eq->r_count = ONE_ROOT;
        eq->roots[0] = -(eq->c / eq->b);
        eq->roots[1] = 0.0;
    }     
}


void solve_quadratic(Equation *eq) 
{
    MY_ASSERT(eq != NULL, ERR_NULL_PTR, "'eq' must point to a structure");
    MY_ASSERT(!is_equal(eq->a, 0), ERR_UNKNOWN, "in this function the coefficient 'a' cannot be equal to 0");

    double discriminant = eq->b * eq->b - 4.0 * eq->a * eq->c;

    if (discriminant > EPS) {
        double root_discriminant = sqrt(discriminant);
        
        eq->r_count = TWO_ROOTS;
        eq->roots[0] = (-eq->b - root_discriminant) / (2.0 * eq->a);
        eq->roots[1] = (-eq->b + root_discriminant) / (2.0 * eq->a);
    } else if (is_equal(discriminant, 0)) {
        eq->r_count = ONE_ROOT;
        eq->roots[0] = (-eq->b) / (2.0 * eq->a);
        eq->roots[1] = 0.0; 
    } else {
        eq->r_count = NO_ROOTS;
        eq->roots[0] = eq->roots[1] = 0.0;
    }
}
