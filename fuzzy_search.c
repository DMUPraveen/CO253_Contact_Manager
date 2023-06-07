#include "fuzzy_search.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int min(int a, int b)
{
    return a < b ? a : b;
}

void swap_arrays(int **a, int **b)
{
    int *t = *a;
    *a = *b;
    *b = t;
}
const int deletion_weight = 3;
const int substitution_weight = 3;
const int insertion_weight = 1;
int levenshtein_distance(const char *str1, const char *str2)
{
    /*
    This is an implementation of levenshtein distance
    This will be used in fuzzy searching
    This code was written with the following pseudo code refference
    https://en.wikipedia.org/wiki/Levenshtein_distance
    */
    int m = strlen(str1);
    int n = strlen(str2);
    int *v0 = calloc(n + 1, sizeof(int));
    int *v1 = calloc(n + 1, sizeof(int));
    for (int i = 0; i < n + 1; i++)
    {
        v0[i] = (i)*insertion_weight;
    }
    for (int i = 0; i < m; i++)
    {

        v1[0] = (i + 1) * deletion_weight;
        for (int j = 0; j < n; j++)
        {
            int deletion_cost = v0[j + 1] + 1 * deletion_weight;
            int insertion_cost = v1[j] + 1 * insertion_weight;
            int substituion_cost = 0;
            if (tolower(str1[i]) == tolower(str2[j]))
            {
                substituion_cost = v0[j];
            }
            else
            {
                substituion_cost = v0[j] + 1 * substitution_weight;
            }
            v1[j + 1] = min(min(deletion_cost, insertion_cost), substituion_cost);
        }
        swap_arrays(&v1, &v0);
    }
    int answer = v0[n];
    free(v0);
    free(v1);
    return answer;
}