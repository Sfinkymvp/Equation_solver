#include <stdio.h>

#include "tests.h"
#include "input.h"
#include "output.h"
#include "constants.h"
#include "utils.h"
#include "solver.h"
#include "myassert.h"


void run_tests(Tests *tests)
{
    MY_ASSERT(tests != NULL, ERR_NULL_PTR, "'tests' must point to structure");
    MY_ASSERT(tests->equations != NULL, ERR_NULL_PTR, "Dynamic array with tests must exist"); 

    for (int index = 0; index < tests->len; index++)
        solve_test(&tests->equations[index]);
}


void solve_test(Test_equation *test)
{
    MY_ASSERT(test != NULL, ERR_NULL_PTR, "'test' should point to test");

    test->ref = test->eq;

    solve_equation(&test->ref);

    if (test->ref.r_count == test->eq.r_count
        && is_equal(test->ref.roots[0], test->eq.roots[0])
        && is_equal(test->ref.roots[1], test->eq.roots[1]))
        test->status = TEST_OK;
    else
        test->status = TEST_ERR;
}


void is_tests_correct(Tests *tests)
{
    MY_ASSERT(tests != NULL, ERR_NULL_PTR, "'tests' must point to structure");
    MY_ASSERT(tests->equations != NULL, ERR_NULL_PTR, "Dynamic array with tests must exist"); 

    for (int index = 0; index < tests->len; index++)
        if (tests->equations[index].status == TEST_ERR) {
            printf(RED "Not all tests passed\n" DEFAULT
                       "Do you want to write the incorrect solutions to a file? (y/n)\n");

            if (check_agreement())
                print_tests_into_file(tests);

            return;
        }

    printf(GREEN "All tests passed\n" DEFAULT);
}

