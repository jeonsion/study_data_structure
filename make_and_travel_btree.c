#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
    element  data;
    struct TreeNdoe* left, *right;
}TreeNode;

int sum = 0;

TreeNode *makeRootNode(element data, TreeNode * left, TreeNode *right)  {
    TreeNode* root;
    root->data = data;
    root->left = left;
    root->right = right;
    return root;
}