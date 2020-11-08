#include<stdlib.h>
#include<stdio.h>
typedef int array[10000]; /*以数组下标为电脑编号，数组值为其父节点*/
void union_by_size(array a); /*将有连接的电脑放到同一个集合*/
int find(array a,int x);/*寻找某个集合的根节点，以便判断某两个电脑是否同属于一个集合*/
void justify1(array a);/*判断某两个电脑是否输入同一集合*/
void justify2(array a,int n);/*判断整个网络是否全部连接*/
int main(){
    int n,i;
    char s;
    array a;
    scanf("%d",&n);
    for (i=1;i<=n;i++){     /*初始化存储数组*/
        a[i]=-1; /*-1代表这个集合有1个元素，同理-2代表有两个，以此类推*/
    }
    do{
        scanf("%c",&s);
        switch(s){
            case'I': union_by_size(a);break;
            case'C':justify1(a);break;
            case'S':justify2(a,n);break;
        }
    }while(s!='S');
    return 0;
}
void union_by_size(array a){
    int x,y,root1,root2;
    scanf("%d %d\n",&x,&y);
    
    root1=find(a,x);
    root2=find(a,y);
    /*根据集合所含元素的多少进行合并，将含有元素较少的合并到含有元素较多的，以减小整个集合的层数*/
    if(root1!=root2){
        if(a[root1]<a[root2]){
            a[root1]=a[root1]+a[root2];
            a[root2]=root1;
        }
        else{
            a[root2]=a[root2]+a[root1];
            a[root1]=root2;
        }
    }
}
int find(array a,int x){
    for(;a[x]>=0;x=a[x]);
    return x;
}
void justify1(array a){
    int x,y;
    scanf("%d %d\n",&x,&y);
    if(find(a,x)!=find(a,y)){
        printf("no\n");
    }
    else{
        printf("yes\n");
    }
}
void justify2(array a,int n){
    int i,count=0;
    for(i=1;i<=n;i++){
        if(a[i]<0)
        count++;
    }
    if(count==1)
    printf("The network is connected.\n");
    else
    printf("There are %d components.\n",count);
}