#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int vertices,edges;
int *start,collection;
double *value;
struct point {
  int last,first;
  double value;
};
typedef struct point edge_doodle;
edge_doodle *tedge;

int search(int x)
{
int i,j,deep;
for (i=x;
     start[i]!=i;
     i=start[i])
  ;
deep=i;
for (i=x;
     start[i]!=i;
     j=start[i],start[i]=deep,i=j)
  ;
return deep;
}

void func(int i,int j)
{
if (value[i]>value[j])
{
  start[j]=i;
  value[i]+=value[j];
}
else
{
  start[i]=j;
  value[j]+=value[i];
}
collection--;
}

int asc_weight(const void* x_coordinate, const void* y_coordinate)
{
edge_doodle *x,*y;

x=(edge_doodle*) x_coordinate;
y=(edge_doodle*) y_coordinate;
double change = x->value - y->value;
if (change > 0) return 1;
else return -1;
}

int main()
{
int i,j;
double MSTweight=0;
int root1,root2;
scanf("%d", &vertices);
edges = vertices*(vertices-1)/2;

int *chech_x, *check_y;
chech_x = (int*)malloc(vertices*sizeof(int));
check_y = (int*)malloc(vertices*sizeof(int));
for(i=0;i<vertices;++i){
  scanf("%d %d", &chech_x[i], &check_y[i]);
}
for(i=0;i<vertices;++i) {
  printf("%4d %4d %4d\n", i, chech_x[i], check_y[i]);
}

tedge=(edge_doodle*) malloc(edges*sizeof(edge_doodle));
start=(int*) malloc(vertices*sizeof(int));
value=(double*) malloc(vertices*sizeof(double));
if (!tedge || !start || !value)
{
  printf("Invalid Error 2\n");
  exit(0);
}

int num_edge = 0;
for(i=0;i<vertices;++i){
  for(j=i+1;j<vertices;++j) {
    double ew = sqrt((double)((chech_x[i]-chech_x[j])*(chech_x[i]-chech_x[j]) + (check_y[i]-check_y[j])*(check_y[i]-check_y[j])));
    tedge[num_edge].last = i;
    tedge[num_edge].first = j;
    tedge[num_edge].value = ew;
    num_edge++;
  }
}
for (i=0;i<vertices;i++)
{
  start[i]=i;
  value[i]=1;
}
collection=vertices;
qsort(tedge,edges,sizeof(edge_doodle),asc_weight);
int num_edges_included = 0;
for (i=0;i<edges;i++)
{
  root1=search(tedge[i].last);
  root2=search(tedge[i].first);
  if (root1==root2)
    printf("%4d %4d %.4lf discarded\n",tedge[i].last,tedge[i].first,
      tedge[i].value);
  else
  {
    num_edges_included++;
    printf("%4d %4d    %.4lf included\n",tedge[i].last,tedge[i].first,
      tedge[i].value);
    MSTweight+=tedge[i].value;
    func(root1,root2);
    if (num_edges_included == vertices - 1)
      break;
  }
}
if (collection!=1)
  printf("MST does not exist\n");
printf("Sum of weights of spanning edges %.4lf\n",MSTweight);
free(tedge);
free(start);
free(value);
}
