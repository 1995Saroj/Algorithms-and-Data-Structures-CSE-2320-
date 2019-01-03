#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int subsequence(const int *first, int second, int third, const int *fourth, int fifth)
{
    int start = 0;
    int temp;
    int i;
    assert(second > 0 && third >= 0 && fifth > 0);
        if (third == 0)
            return 0;
        if (second * third > fifth)
            return 1;
            puts("\n");
        for (i = 0; start < second * third && i < fifth; i++)
        {
            temp = start / third;
            printf("%d,%d ", first[temp], fourth[i]);
        if (first[temp] == fourth[i])
            start++;
        }
        puts("\n");
        return start == (second * third) ? 0 : 1;
}
int main(void) 
    {
        int fifth;
        int second;
        int *fourth;
        int *first;
        int tim;
        const int trash = -999999999;
        int low;
        int high;
        int mid;
        int final;
        int occurences;
        int i;
    assert(2 == scanf("%d %d\n", &fifth, &second));
    assert(fifth > 0 && second > 0 && fifth >= second);
    assert(0 != (fourth = malloc(fifth * sizeof *fourth)));
    assert(0 != (first = malloc(second * sizeof *first)));
    for (i = 0, occurences = 0; !occurences && i <= fifth; i++)
    {
        assert(1 == scanf("%d\n", &tim));
        if (tim == trash)
            occurences = 1;
        else
            fourth[i] = tim;
    }
    assert(tim == trash);
    for (i = 0, occurences = 0; !occurences && i <= second; i++)
    {
        assert(1 == scanf("%d\n", &tim));
        if (tim == trash)
            occurences = 1;
        else
            first[i] = tim;
    }
    assert(tim == trash);
    puts("Correct Reading - Fine");

    low = 0;
    high = fifth / second;
    final = -1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        printf("low %d mid %d high %d", low, mid, high);
        if (subsequence(first, second, mid, fourth, fifth) == 0) 
        {
            printf(" passed\n");
            final = mid;
            low = mid + 1;
        } else {
            printf(" failed\n");
            high = mid - 1;
        }
    }
    printf("Maximum repeats is %d\n", final);
    free(fourth);
    free(first);
    return 0;
}
