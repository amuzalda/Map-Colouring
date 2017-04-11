#include <iostream>
#include<stdio.h>

using namespace std;

// Number of vertices in the graph
#define V 4
// NUmber of coloures
#define m 3


void printSolution(int color[]);
/*
function B ACKTRACKING -S EARCH (csp) returns a solution, or failure
return R ECURSIVE -B ACKTRACKING ({ }, csp)

function R ECURSIVE -B ACKTRACKING (assignment , csp) returns a solution, or failure
if assignment is complete then return assignment
var ← S ELECT -U NASSIGNED -V ARIABLE (V ARIABLES [csp], assignment , csp)
for each value in O RDER -D OMAIN -V ALUES (var , assignment, csp) do
  if value is consistent with assignment according to C ONSTRAINTS [csp] then
  add {var = value} to assignment
  result ← R ECURSIVE -B ACKTRACKING (assignment , csp)
  if result 6 = failure then return result
  remove {var = value} from assignment
return failure*/

/* A utility function to check if the current color assignment
   is safe for vertex v */
bool goal(int color[]){

   for(int i=0;i<V;i++){
      if(color[i]==0){
         return false;

      }
  }

     return true;
}



void update_domain(int c,int v,bool graph[V][V],int domain[V][m]){
  for (int i = 0; i < V; i++)
      if (graph[v][i] ){
        domain[i][c-1]=0;
      }

}

bool isSafe (int v, bool graph[V][V], int color[], int c)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}

/* A recursive utility function to solve m coloring problem */
bool graphColoringUtil(bool graph[V][V], int color[], int v, int domain[V][m])
{
    /* base case: If all vertices are assigned a color then
       return true */
    if(goal(color)) // check for goal test
        return true;


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

           if (graphColoringUtil(graph, color, v+1,domain) == true)
             return true;

            /* If assigning color c doesn't lead to a solution
               then remove it */
           color[v] = 0;
        }
    }

    /* If no color can be assigned to this vertex then return false */
    return false;
}

/* This function solves the m Coloring problem using Backtracking.
  It mainly uses graphColoringUtil() to solve the problem. It returns
  false if the m colors cannot be assigned, otherwise return true and
  prints assignments of colors to all vertices. Please note that there
  may be more than one solutions, this function prints one of the
  feasible solutions.*/
bool graphColoring(bool graph[V][V], int domain[V][m])
{

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
// driver program to test above function
int main()
{
    int domain[V][m];
    inti_domain(domain);
    /* Create following graph and test whether it is 3 colorable
      (3)---(2)
       |   / |
       |  /  |
       | /   |
      (0)---(1)
    */
    bool graph[V][V] = {{0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    };

    graphColoring (graph,domain);
    return 0;
}
