#include<stdlib.h>
#include<stdio.h>
typedef struct node *tree;
struct node
{
    int data,flag; /*The value of flag is used to judgement whether the node is a red node or not*/
    tree left,right; /*Poont to the left and right child*/
};
/* Build the binary search tree
root point to the tree and x is the value of the node*/
tree build_tree(tree root,int x){
    if(root==NULL){
        root=malloc(sizeof(struct node));
        root->data=abs(x);       /*Store the absolute value of x as the value of the node*/
        if(x>0)  root->flag=0;   /* If the node is a red node, then the value of flag is 1, otherwise the value is 0*/
        else root->flag=1;   
        root->left=NULL;    /*Point to the NULL pointer*/
        root->right=NULL;
    }
    /*According to the size of the value to determine its insertion position*/
    else if(abs(x)<root->data){ 
        root->left=build_tree(root->left,x); /*Recurse left*/
    }
    else{
        root->right=build_tree(root->right,x);/*Recurse right*/
    }
    return root; /*return the root node*/
}
/*Determine whether the fourth property is satisfied*/
int judge1(tree root){
    if(root==NULL)
        return 1;
    if(root->flag==1){ /*Determine whether the child node is a black node*/
        if(root->left!=NULL&&root->left->flag==1)
            return 0;
        if(root->right!=NULL&&root->right->flag==1)
            return 0;
    }
    return judge1(root->left)&&judge1(root->right); /*Recursive traversal*/
}
/*Determine whether the fifth property is satisfied*/
int judge2(tree root){
    int left_height,right_height;
    if(root==NULL)
        return 1;
    else{
        left_height=sum(root->left); /*Obtain the numbers of black nodes on the path from any node to the leaf node*/
        right_height=sum(root->right);
    }
    if(left_height!=right_height) /*If it is not equal, it means that the number of black nodes is not equal*/
    return 0;
    return judge2(root->right)&&judge2(root->left);
}
/*Take the maximum of the two values*/
int max(int a,int b){
    if(a>b) return a;
    else return b;
}
/*Obtain the numbers of black nodes on the path from any node to the leaf node*/ 
int sum(tree root){
    int left_height,right_height;
    if(root==NULL)
        return 0;
    /*Recursive left and right subtrees*/
    left_height=sum(root->left);
    right_height=sum(root->right);
    /*Determine whether the current node is a black node, and calculate the number of black nodes*/
    if(root->flag==1)
    return max(left_height,right_height); /*Take the larger value on the left and right sides*/
    else
    return max(left_height,right_height)+1;
}
/*Free the memory space*/
void free_tree(tree root){
    if(root==NULL){
        return ;
    }
    /*Free memory from the leaf node*/
    free_tree(root->left);
    free_tree(root->right);
    free(root); 
}
int main(){
    int number,n,x;
    tree root;
    scanf("%d",&n);
    if(n==0) /*If the operation is illegal, output"This is not promised"*/
    printf("This is not promised\n");
    else{
        while(n!=0){
        scanf("%d",&number);
        if(number==0){
           printf("This is not promised\n"); /*If the operation is illegal, output"This is not promised"*/
           break;
        }
        /*Initialize the root node*/
        root=NULL;
        /*Build the tree*/
        for(int i=0;i<number;i++){
            scanf("%d",&x);
            root=build_tree(root,x);
        }
         /*Determine whether the second or the fourth or the fifth properties are not satisfied*/
        if(root->flag==1||judge1(root)==0||judge2(root)==0)
            printf("No\n");
        else
            printf("Yes\n");
        n--;
        free_tree(root);
        } 
    }
    return 0;
}