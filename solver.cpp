#include <math.h>
#include <assert.h>

#include "solver.h"
#include "constants.h"
#include "utils.h"


void solve_equation(Equation * eq)
{
    assert(eq != NULL);

    if (is_zero(eq->a))
        solve_linear(eq);
    else
        solve_quadratic(eq);

    order_roots(eq);
//  удаление знака нуля -0.0 -> 0.0 
    for (int i = 0; i < MAX_ROOTS; i++)
        if (is_zero(eq->roots[i]))
            eq->roots[i] = 0.0;
}


void order_roots(Equation * eq)
{
    assert(eq != NULL);

   if (eq->r_count == TWO_ROOTS && eq->roots[0] > eq->roots[1]) {
        double temp = eq->roots[0];

        eq->roots[0] = eq->roots[1];
        eq->roots[1] = temp;
    }
}


void solve_linear(Equation * eq)
{
    assert(eq != NULL);

    if (is_zero(eq->b) && is_zero(eq->c))
        eq->r_count = INFINITE_ROOTS;
    else if (is_zero(eq->b) && !is_zero(eq->c))
        eq->r_count = NO_ROOTS;
    else {
        eq->r_count = ONE_ROOT;
        eq->roots[0] = -(eq->c / eq->b);
        eq->roots[1] = 0.0;
    }     
}


void solve_quadratic(Equation * eq) 
{
    assert(eq != NULL);
    assert(!is_zero(eq->a));

    double discriminant = eq->b * eq->b - 4.0 * eq->a * eq->c;

    if (discriminant > EPS) {
        double root_discriminant = sqrt(discriminant);
        
        eq->r_count = TWO_ROOTS;
        eq->roots[0] = (-eq->b - root_discriminant) / (2.0 * eq->a);
        eq->roots[1] = (-eq->b + root_discriminant) / (2.0 * eq->a);
    } else if (is_zero(discriminant)) {
        eq->r_count = ONE_ROOT;
        eq->roots[0] = (-eq->b) / (2.0 * eq->a);
        eq->roots[1] = 0.0; 
    } else {
        eq->r_count = NO_ROOTS;
        eq->roots[0] = eq->roots[1] = 0.0;
    }
}
