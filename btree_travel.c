#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
    element data;
    struct TreeNode* left, *right;
}TreeNode;

TreeNode n1 = {1, NULL, NULL};
TreeNode n2 = {4,  &n1, NULL};
TreeNode n3 = {16, NULL, NULL};
TreeNode n4 = {25,NULL, NULL};
TreeNode n5 = {20, &n3, &n4};
TreeNode n6 = {15,  &n2, &n5};
TreeNode *root = &n6;

void preorder(TreeNode * root)   {      //전위 순회
    if(root!= NULL) {
        printf("%d ", root->data);       //노드 방문
        preorder(root->left);           //왼쪽 서브트리 순회
        preorder(root->right);          //오른쪽 서브트리 순회
    }
}

void inorder(TreeNode *root)    {
    if(root != NULL)    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void postorder(TreeNode * root) {
    if(root != NULL)    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}
int main()  {
    printf("중위순회: ");
    inorder(root);
    printf("\n");

    printf("전위순회: ");
    preorder(root);
    printf("\n");

    printf("후위순회: ");
    postorder(root);
    printf("\n");
}