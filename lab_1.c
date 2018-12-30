#include <stdlib.h>
#include <stdio.h>
struct sorting_pairs
{
    int list;                      
    int index;
};
int list_compare(const void *p, const void *q);
int index_compare(const void *p, const void *q);


int list_compare(const void *p, const void *q)
{
    int node;
    node = ((struct sorting_pairs*)p)->list - ((struct sorting_pairs*)q)->list;
    if (node == 0) 
    {
        node = ((struct sorting_pairs*)p)->index - ((struct sorting_pairs*)q)->index;
    }
    return node;
}
int index_compare(const void *p, const void *q) 
{
    return ((struct sorting_pairs*)p)->index - ((struct sorting_pairs*)q)->index;
}

int main()
{
    int n;
    int i;
    int end_n;       
    struct sorting_pairs *temp;
    scanf("%d", &n);
    temp = malloc(sizeof(struct sorting_pairs) *n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &(temp[i].list) );
        temp[i].index = i;
    }
     printf("\n\n\n");
    
    qsort(temp, n, sizeof(struct sorting_pairs), list_compare);
    end_n = 0; 
    for (i = 0; i < n; i++)
    {
        if (end_n == 0 || temp[i].list != temp[end_n - 1].list)
        {
            temp[end_n] = temp[i];
            end_n++;
        }
    }
    n = end_n;
    
   
    qsort(temp, n, sizeof(struct sorting_pairs), index_compare);
    printf("%d\n", n);
    for (i = 0; i < n; i++)
    {
        printf("%d\n", temp[i].list);
    }
    free(temp);
    return 0;
}
