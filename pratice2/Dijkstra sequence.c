#include<stdio.h>
#include<stdlib.h>
#define maxdis 100000000 //define the maxdistance which show that there is no connection between two vertex
//The secondary pointer C stores the information of the graph, v represents the source vertex, n represents the number of vertices
int *dijkstra(int **C,int v,int n);//Get the array storing the minimum distance 
//The second-level pointer C stores the information of the graph, the first-level pointer p 
//stores the information of the sequence to be determined, 
//the first-level pointer D0 stores the information of the correct shortest path sequence,
//v represents the source vertex, and n represents the number of vertices
void check(int **C,int *p,int *D0,int v,int n);// check whether the given sequence is a Dijkstra Sequence
int main()
{
 int Nv,Ne,i,j,K;
 scanf("%d %d",&Nv,&Ne);
 int m,n,weight;
 int *D0;// Define an array to store the correct minimum distance to facilitate comparison and judgment
 //Store graphs in a two-dimensional matrix
 int G[Nv][Nv],*p[Nv];//Define an array of pointers and pass the two-dimensional array to the corresponding function
 int seq[Nv];//Store the sequence to be judged
 //Initialize the graph, the vertices are not connected, so the initial distance is set to maxdis
 for(i=0;i<Nv;i++){
     for(j=0;j<Nv;j++)
         G[i][j]=maxdis;
 }
 //Define the graph according to the connection relationship and weight value of the given edge
 for(i=0;i<Ne;i++){
     scanf("%d %d %d",&m,&n,&weight);
     G[m-1][n-1]=weight;//the array index starts from 0,so there is m-1 and n-1
     G[n-1][m-1]=weight;//this is a undirected graph,so the matrix symmetric matrix
 }
 //Store the two-dimensional matrix in a pointer array to pass parameters
 for(i=0;i<Nv;i++)
     p[i]=G[i];
 scanf("%d",&K);
 for(i=0;i<K;i++){
     for(j=0;j<Nv;j++)
        scanf("%d",&seq[j]);
    D0=dijkstra(p,seq[0],Nv);//Get the correct order of the shortest path and store it in D0
    check(p,seq,D0,seq[0],Nv);//Determine whether the given sequence is a Dijkstra Sequence
 }
 return 0;
}
int *dijkstra(int **C,int v,int n)
{
 int D[n],x=0;//Array D stores the distance after each update
 int *D0;//Define pointer D0 and allocate space for parameter transfer
 D0=(int*)malloc(n);
 int S[n];//Define an array S to store the vertices that have been visited
 int i,j,k,v1;
 int min,inf=200000000;//Define a larger distance, this distance is greater than maxdis to ensure that all points can be visited
 v1=v-1;//Because the index of the array starts from 0, the index of the source vertex must be reduced by one 
//Update the array D storing the distance for the first time
 for(i=0;i<n;i++)
 {
  D[i]=C[v1][i];   //The distance of the first update is the distance between the origin and its directly connected vertices, 
                   //and the remaining distances are infinite, here is maxdis
 }
//Initially, the set of vertices visited is an empty set, so the set S is initialized to 0
 for(i=0;i<n;i++)
  S[i]=0;
//Send the origin into the set S, and send the first shortest path 0 into D0    
 S[v1]=1;D[v1]=0;D0[0]=0;
 for(i=0;i<n-1;i++)
 {
//Define the minimum distance and prepare to expand the set S
  min=inf;
//Find the shortest vertex of the current path
  for(j=0;j<n;j++)
  {
   if((!S[j])&&(D[j]<min))
   {
    min=D[j];
    k=j;
   }
  }
//Add the vertex to the set S and update the array D0 storing the shortest path
  S[k]=1;
  D0[++x]=min;
//After adding vertex K+1 to set S, update the distance of the 
//remaining vertices that are not in set S
  for(j=0;j<n;j++)
  {
   if((!S[j])&&(D[j]>D[k]+C[k][j]))//(!S[j]) ensure the vertex is not in the set S and 
   //D[j]>D[k]+C[k][j] ensyre the updated distance is smaller
   {
    D[j]=D[k]+C[k][j]; //update the distance
   }
  }
 }
 return D0;//Return the array D0 storing the shortest path sequence
} 
void check(int **C,int *p,int *D0,int v,int n){
 int D[n],D1[n],x=0,y=0;//Use the array D1 to store the sequence of the shortest path generated according to the given sequence
 //If this D1 and D0 are not equal, then the given sequence is not a Dijkstra Sequence
 int S[n];
 int i,j,k,v1;
 int min,inf=200000000;
 v1=v-1;
//The function is the same as in the dijkstra function
 for(i=0;i<n;i++)
  D[i]=C[v1][i];   
 //The function is the same as in the dijkstra function
 for(i=0;i<n;i++)
  S[i]=0;     
  S[v1]=1;D[v1]=0;D1[0]=0;   
 for(i=0;i<n-1;i++)   
 {
//When the sequence is given, the vertices added to the set S are fixed, that is p[y]
  y++;
  k=p[y]-1;
  min=D[p[y]-1];
  S[k]=1;    
  D1[++x]=min;//When a given vertex is added to S, store the minimum distance
  for(j=0;j<n;j++)
  {
   if((!S[j])&&(D[j]>D[k]+C[k][j]))
   {
    D[j]=D[k]+C[k][j];  
   }
  }
 } 
 //Make judgments
 for(i=0;i<n;i++){
     //If any element of array D0 and D1 are different, it means that the given sequence is not Dijkstra Sequence,then break
     if(D0[i]!=D1[i]){
         break;
     }
 }
//if i!=n, indicates exit in the middle of the loop,then the sequence is not a Dijkstra Sequence;
//Otherwise,it is a a Dijkstra Sequence
 if(i!=n){
     printf("No\n");
 }
 else{
     printf("Yes\n");
 }
}