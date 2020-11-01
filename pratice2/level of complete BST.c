#include <stdio.h>
#include <stdlib.h>
int b[1000];
int position=0;
void leavelorder(int root, int n, int a[])
{
    if(root<=n) {
        leavelorder(2*root,n,a);
        b[root]=a[position++];
        leavelorder(2*root+1,n,a);
    }
}

int main()
{
    int a[1000],n,x;
    int i,j;
    scanf("%d\n",&n);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(a[i]>a[j]){
                x=a[i];
                a[i]=a[j];
                a[j]=x;
            }
        }
    }
    leavelorder(1, n, a);
    for(i=1;i<=n;i++) {
        if(i==1) {
            printf("%d",b[i]);
        } else {
            printf(" %d",b[i]);
        }
    }

    return 0;
}