#include <stdio.h>
#include <stdlib.h>
#include "contactManager.h"

void check(bool expression, char *test)
{
    char *status = (expression) ? "PASSED" : "FAILED";
    printf("%s -- %s\n", test, status);
}

void run_test_suite(void (*test_function)(), char *test_collection_name)
{
    printf("Running ----------- %s ------------\n", test_collection_name);
    test_function();
    printf("-----------------------------------\n");
    printf("\n");
}
void test_test_suite()
{
    check(true, "test pass");
    check(false, "test fail");
}
int main()
{
    run_test_suite(test_test_suite, "SIMPLE_TEST");
    return 0;
}