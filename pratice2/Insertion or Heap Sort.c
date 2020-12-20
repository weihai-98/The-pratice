#include<stdio.h>
#define N 200
void initial_(int a[],int initial[],int n);
int judgement(int judge[],int a[],int n);
void percolatedown(int heap[],int i,int n);
void heapsort(int initial[],int judge[],int heap[],int n);
void insertsort(int initial[],int judge[],int insert[],int n);
void print(int a[],int n);
int main(){
    int n,i;
    int initial[N],judge[N];
    int insert[N],heap[N];
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&initial[i]);
    }
    for(i=0;i<n;i++){
        scanf("%d",&judge[i]);
    }
    insertsort(initial,judge,insert,n); /*判断是否为insert排序的中间结果*/
    heapsort(initial,judge,heap,n);     /*判断是否为heap排序的中间结果*/
}
void initial_(int a[],int initial[],int n){
    int i;
    for(i=0;i<n;i++){
        a[i]=initial[i];
    }
}
int judgement(int judge[],int a[],int n){
    int i;
    for(i=0;i<n;i++){
        if(a[i]!=judge[i])
            return 0;
    }
    return 1;
}
/*调整最小堆的最小值*/
void percolatedown(int heap[],int i,int n){ 
    int child,temp;
    for(temp=heap[i];2*i+1<n;i=child){
        child=2*i+1;
        if(child!=n-1&&heap[child+1]>heap[child])
            child++;
        if(temp<heap[child])
            heap[i]=heap[child];
        else
            break;
    }
    heap[i]=temp;
}
/*进行堆排序并进行比较*/
void heapsort(int initial[],int judge[],int heap[],int n){
    initial_(heap,initial,n);
    int i,temp;
    for(i=n/2;i>=0;i--)
        percolatedown(heap,i,n);
    for(i=n-1;i>0;i--){
        temp=heap[0];
        heap[0]=heap[i];
        heap[i]=temp;
        percolatedown(heap,0,i);
        if(judgement(judge,heap,n)){
            printf("Heap Sort\n");
            i--;
            if(i>0){
                temp=heap[0];
                heap[0]=heap[i];
                heap[i]=temp;
                percolatedown(heap,0,i);
            }
            print(heap,n);
            return;
        }
    }
}
void insertsort(int initial[],int judge[],int insert[],int n){
    int i,j;
    int temp;
    initial_(insert,initial,n);
    for(i=1;i<N;i++){
        temp=insert[i];
        for(j=i;j>0&&insert[j-1]>temp;j--)
            insert[j]=insert[j-1];
        insert[j]=temp;
        if(judgement(judge,insert,n)){
            printf("Insertion Sort\n");
            i++;
            if(i+1<N){
                temp=insert[i];
                for(j=i;j>0&&insert[j-1]>temp;j--)
                    insert[j]=insert[j-1];
                insert[j]=temp;
            }
            print(insert,n);
            return;
        }
    }
}
/*输出结果*/
void print(int a[],int n){
    int i;
    for(i=0;i<n-1;i++)
        printf("%d ",a[i]);
    printf("%d",a[i]);
}