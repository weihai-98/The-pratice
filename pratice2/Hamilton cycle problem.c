#include<stdlib.h>
#include<stdio.h>
#define max 300
int main(){
    int M,N,K;
    int n;
    int G[max][max];
    scanf("%d %d",&N,&M);
    int i,j;
    int a,b;
    /*初始化图*/
    for(i=0;i<M;i++){
        scanf("%d %d\n",&a,&b);
        G[a][b]=1;
        G[b][a]=1;
    }
    scanf("%d",&K);
    int x[max],y[max];
    for(i=0;i<K;i++){
        scanf("%d",&n);
        for(j=0;j<n;j++){
            y[j]=0;
            scanf("%d",&x[j]);
        }
        if(n!=N+1||x[0]!=x[n-1]){
            printf("NO\n");
        }
        else{
            for(j=0;j<n;j++){
            if(G[x[j]][x[j+1]]==0)
            break;
            if(y[x[j]]==1)
            break;
            else
            {
                y[x[j]]=1;
            }
            
        }
        if(j==n-1)
        printf("YES\n");
        else
        {
            printf("NO\n");
        }
        }
    }
    return 0;
}