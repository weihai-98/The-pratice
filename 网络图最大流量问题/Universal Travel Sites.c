#include<stdio.h>
#include<string.h>
#define maxsize 1000 
#define inifinity 10000000
int Residual[maxsize][maxsize];
int count = 0;
char S[maxsize][4];
int front;
int rear;
int dist[maxsize];
int quantify(char s[4]);
void Enqueue(int x,int Q[]);
int Dequeue(int Q[]);
int isempty();
int find_path(int s, int d, int N);
int sum_update(int s, int d, int sum,int N);
int main(){
    int i,j,N,weight,sum=0;
    char s[4],d[4],v1[4],v2[4];
    int source,destination;
    scanf("%s %s %d",s,d,&N);
    source=quantify(s);
    destination=quantify(d);
    for(i=0;i<N;i++){
        scanf("%s %s %d",v1,v2,&weight);
        Residual[quantify(v1)][quantify(v2)]=weight;
    }
    while(find_path(source,destination,N)!=0){
        sum=sum+sum_update(source,destination,inifinity,N);
    }
    printf("%d\n",sum);
    return 0;
}
int quantify(char s[4]){
    int i;
    for(i=0;i<count;i++){
        if(strcmp(s,S[i])==0)
            break;
    }
    if(i==count){
        strcpy(S[count],s);
        count++;
    }
    return i;  
}
int Dequeue(int Q[]){
    int i;
    i=Q[front];
    front++;
    return i;
}
void Enqueue(int x,int Q[]){
    Q[rear]=x;
    rear++;
}
int isempty(){
    if(front==rear){
        return 1;
    }
    else
        return 0;
}
int find_path(int s,int d,int N){
    front=0;
    rear=0;
    int Q[maxsize];
    int i,v;
    Enqueue(s,Q);
    for(i=0;i<N;i++)
        dist[i]=0;
    dist[s]=1;
    while(!isempty()){
        v=Dequeue(Q);
        for(i=0;i<N;i++){
            if(!dist[i]&&Residual[v][i]){
                dist[i]=dist[v]+1;
                Enqueue(i,Q);
            }
        }
    }
    return dist[d];//若有从原点到终点的路径，则dist[d]不等于0
}
int sum_update(int s,int d,int sum,int N){
    int i,q,min;
    if(s==d){
        return sum;
    }
    for(i=0;i<N;i++){
        if((dist[i]==dist[s]+1)&&Residual[s][i]){
            if(Residual[s][i]<sum)
                min=Residual[s][i];
            else
                min=sum;
            q=sum_update(i,d,min,N);
            //update
            if(q){
                Residual[s][i]=Residual[s][i]-q;
                Residual[i][s]=Residual[i][s]+q;
                return q;
            }
        }
    }
    return 0;
}