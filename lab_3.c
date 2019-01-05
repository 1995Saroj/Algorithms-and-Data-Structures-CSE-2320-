#include <stdio.h>
#include <stdlib.h>

void reading_the_input(int* n, int* data, int** S, int*** C)
{
    int i;
    scanf("%d", n);
    scanf("%d", data); 
    *S = (int*) malloc((*n + 1) * sizeof(int));
    *C = (int**) malloc((*n + 1) * sizeof(int*));
    if (!(*S) || !(*C))
    {
        printf("malloc failed %d\n", __LINE__);
        exit(0);
    }
    for (i = 0; i <= *n; i++)
    {
        (*C)[i] = (int*) malloc((*data + 1) * sizeof(int));
        if (!((*C)[i]))
        {
            printf("malloc failed %d\n", __LINE__);
            exit(0);
        }
    }
    (*S)[0] = 0;
    for (i = 1; i <= *n; i++)
        scanf("%d", *S + i);
}
void total_sub_set_sum_problem(int n, int data, int* S, int** C)
{
    int i, j, total_sum, remaining_sum, cardinal_value;
    C[0][0] = 0;
    for (i = 1; i <= n; i++)
    {
        C[i][0] = n + 1;
    }
    for (i = 1; i <= data; i++)
    {
        C[0][i] = n + 1;
    }
    for (cardinal_value = 1; cardinal_value <= n; cardinal_value++)
    {
        for (total_sum = 1; total_sum <= data; total_sum++)
        {
            for (j = 1; j <= n; j++)
            {
                remaining_sum = total_sum - S[j];
                if (remaining_sum >= 0 && C[cardinal_value - 1][remaining_sum] < j)
                    break;
            }
            C[cardinal_value][total_sum] = j;
        }
    }
}
void writing_the_output(int n, int data, int* S, int** C)
{
    int i, j;
    printf("  i\tS\n");
    printf("-----------\n");
    for (i = 0; i <= n; i++)
    printf("%3d \t%3d\n", i, S[i]);
    printf("i \tcard  \tC\n");
    printf("-------------------------\n");
    for (i = 0; i <= data; i++)
    {
        for (j = 1; j <= n; j++)
            printf("%3d\t%3d\t%3d\n",i,j, C[j][i]);
        
    }
    for (i = 1; i <= n; i++)
    {
        if(C[i][data]==n+1){
        printf("No Solution with %d elements\n\n", i);
	    }
        if (C[i][data] != n + 1)
        {
            int card = i;
            printf("Solution with %d elements\n\n", i);
            printf("i\t S\n");
            printf("----------\n");
            for (j = data; j > 0; j -= S[C[card][j]], card--)
            {
            printf("%d \t%3d\n\n",C[card][j],S[C[card][j]]);
            }
            printf("\n");
        }
    }}
int main()
{
    int i;
    int n;
    int data;
    int *S;
    int **C;
    reading_the_input(&n, &data, &S, &C);
    total_sub_set_sum_problem(n, data, S, C);
    writing_the_output(n, data, S, C);
    free(S);
    for (i = 0; i <= n; i++)
    free(C[i]);
    free(C);
}
