#include <iostream>
#include <stdio.h>
#include <queue>
#include <utility>
#include <fstream>


using namespace std;

// Number of vertices in the graph
#define V 15
// NUmber of coloures
#define m 4

void printSolution(int color[]);

bool goal(int color[]){

   for(int i=0;i<V;i++){
      if(color[i]==0){
         return false;

      }
  }

     return true;
}
// returns the vertex having minimum value remains in domain
int select_unassigned_var(int color[],int domain[V][m]){

  int index,rem_val=m;
  int k;
  k=m;

  int r=0;
  for (int i = 0; i < V; i++){
      r=0;
     if(color[i]==0){
       for(int j=0;j<k;j++){
         if(domain[i][j]!=0)
           r++;
       }
    if(r<rem_val){
      index=i;
    }


  }
  }
  return index;
}

bool remove_incon_val(int x,int y,int domain[V][m]){
  bool removed=false;
  int c,flag;

  for(int i=0;i<m;i++){
    c=domain[x][i];
    flag=0;
    for (int j = 0; j < m; j++)
        if (domain[y][j]!=0&&i!=j ){
           flag=1;
        }
  if(flag ==0){
     domain[x][i]=0;
     removed=true;
     }
     else removed=false;

  }

  return removed;
}


void update_domain(int c,int v,bool graph[V][V],int domain[V][m]){
  for (int i = 0; i < V; i++)
      if (graph[v][i] ){
        domain[i][c-1]=0;
      }

}




bool arc3(bool graph[V][V],int domain[V][m]){
  pair<int,int> x;

   queue<pair<int,int> > q;
   for(int i=0;i<V;i++){
     for(int j=0;j<V;j++){
        if(graph[i][j]!=0)
           q.push(make_pair(i,j));
     }
   }
   while (q.empty()) {
     x=q.front();
       if(remove_incon_val(x.first,x.second,domain)){
         for(int i=0;i<V;i++){
           if(graph[x.first][i]!=0)
           q.push(make_pair(x.first,i));
         }
       }

     /* code */
   }

}
bool isSafe (int v, bool graph[V][V], int color[], int c)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}




bool graphColoringUtil(bool graph[V][V], int color[], int v, int domain[V][m])
{
    /* base case: If all vertices are assigned a color then
       return true */
    if(goal(color)) // check for goal test
        return true;

    int var;
    /* Consider this vertex v and try different colors */
    for (int c = 0; c < m; c++)
    {
        /* Check if assignment of color c to v is fine*/
      if(domain[v][c]!=0)
        if (isSafe(v, graph, color, domain[v][c]))
        {
           color[v] = domain[v][c];
           update_domain(color[v],v,graph,domain);//upate the domain of adjacent vertixes

           /* recur to assign colors to rest of the vertices */
             var=select_unassigned_var(color,domain);
           if (graphColoringUtil(graph, color, var,domain) == true)
             return true;

            /* If assigning color c doesn't lead to a solution
               then remove it */
           color[v] = 0;
        }
    }

    /* If no color can be assigned to this vertex then return false */
    return false;
}



bool graphColoring(bool graph[V][V], int domain[V][m])
{   arc3(graph,domain);

    // Initialize all color values as 0. This initialization is needed
    // correct functioning of isSafe()
    int *color = new int[V];
    for (int i = 0; i < V; i++)
       color[i] = 0;

    // Call graphColoringUtil() for vertex 0
    if (graphColoringUtil(graph, color, 0,domain) == false)
    {
      printf("Solution does not exist");
      return false;
    }

    // Print the solution
    printSolution(color);
    return true;
}

/* A utility function to print solution */
void printSolution(int color[])
{
    printf("Solution Exists:"
            " Following are the assigned colors \n");
    for (int i = 0; i < V; i++)
      printf(" %d ", color[i]);
    printf("\n");
}

void inti_domain(int domain[V][m]){
  for(int i=0;i<V;i++){
    for(int j=0;j<m;j++){
      domain[i][j]=j+1;
    }
}

}

int main()
{
   fstream fin;
     int a;
    fin.open("input10.txt");
    int domain[V][m];
    inti_domain(domain);
    bool graph[V][V];
    for(int i=0;i<V;i++)
      for(int j=0;j<V;j++){
        fin>>a;
        graph[i][j]=a;
      }
    graphColoring (graph,domain);
    return 0;
}
