#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef unsigned int * poi;
int comp (const void * a, const void * b)
{
  return ( *(unsigned int*)a - *(unsigned int*)b );     }
void qt_selection (unsigned int arr1[], int time, int ending, unsigned int k)
{
  unsigned int next;
  int m = time, n = ending;
  unsigned int piv = arr1[time];
  while (m <= n)
  {
    while (arr1[m] < piv)
      m++;
    while (arr1[n] > piv)
      n--;
    if (m <= n)
    {   // swap
        next = arr1[m];
        arr1[m] = arr1[n];
        arr1[n] = next;
        m++;
        n--;
    }
  }
  if (k - 1 <= n){
    if (time < n)
    qt_selection (arr1, time, n, k);
  }
  else if (k - 1 >= m)
  {
        if (ending > m)
            qt_selection (arr1, m, ending, k);
  }
}

int main() {
    unsigned int i, j, next, total = 0, position, num = 0, divi = 100000000;
    unsigned int n[9]= {0}, k[9]= {0}, digit[9] = {0};
    unsigned int count[10] = {0};
    unsigned int last = 0;
    time_t beginning, ending;
    poi a[9] = {0};
    printf("\nThe program computes the kth smallest num in a sequence\n");
    printf("of n integers in the range 0 . . . 999,999,999\n\n");
    printf("Enter the num of items: ");
    scanf("%u",&n[0]);
    printf("Enter k : ");
    scanf("%u", &k[0]);
    a[0] = (unsigned int*)malloc(n[0] * sizeof(int));
    a[1] = (unsigned int*)malloc(n[0] * sizeof(int));
    printf("Enter %u integers\n", n[0]);
    for(i = 0; i < n[0]; i++) {
        scanf("%u", &a[0][i]);
        a[1][i] = a[0][i];
        next = a[0][i]/divi;
        count[next]++;
    }
    printf("\n");
    beginning = clock();
    qt_selection(a[1], 0, n[0] - 1, k[0]);
    ending = clock();
    printf ("qt_selection: The value with rank %u is %u \n", k[0], a[1][k[0]-1]);
    printf ("qt_selection time used is %f \n", (double)(ending - beginning) / CLOCKS_PER_SEC);
    for(i = 0; i < n[0]; i++) {
        a[1][i] = a[0][i];
     }
    beginning = clock();
    qsort (a[1], n[0], sizeof(unsigned int), comp);
    ending = clock();
    printf ("qsort: The value with rank %u is %u \n", k[0], a[1][k[0]-1]);
    printf ("qsort time used is %f \n", (double)(ending - beginning) / CLOCKS_PER_SEC);
    free(a[1]);
    a[1] = NULL;
    beginning = clock();
    for(j = 0; j < 8; j++) {
        total = 0;    
        for(i = 0; i < 10; i++) {
            total += count[i];
            if(total >= k[j]) {
                digit[j] = i;
                break;
            }
        }
        num = num * 10 + digit[j];
        n[j + 1] = count[digit[j]];
        if(n[j] == 1)
        {
            last = j;
            break;
        }
        k[j + 1] = k[j] - total + n[j + 1];
        for(i = 0; i < 10; i++) {
            count[i] = 0;
        }
        position = 0;
        a[j+1] = (unsigned int*)malloc(n[j+1] * sizeof(int));
        for(i = 0; i < n[j]; i++) {
            if(a[j][i]/divi  == num) {
                next = a[j][i] % divi / (divi / 10);
                count[next]++;
                a[j+1][position++] = a[j][i];
            }
        }
        divi /= 10;
        last = j;
    }
    j = last;
    total = 0;
    for(i = 0; i < 10; i++) {
        total += count[i];
        if(total >= k[j]) {
            digit[j] = i;
            break;
        }
    }
    ending = clock();
    for(j = 0; j <= last; j++)
    {
         printf("position %u n %u \n", 9 - j, n[j]);
    }
    if(last == 7)
            printf("position %u n %u \n", 1, 1);
    num = num * 10 + digit[j];
    printf("MSD 10 radix: The value with rank %u is %u \n", k[0],a[last][0]);
    printf ("radix selection time used is %f \n", (double)(ending - beginning) / CLOCKS_PER_SEC);
    for(i = 0; i < 9; i++)
    {
        if(a[i] != NULL)
        {
            free(a[i]);
            a[i] = NULL;
        }
    }
    return 0;
}
