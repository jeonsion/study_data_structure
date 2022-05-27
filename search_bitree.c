#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode{
    element key;
    struct TreeNode *left, *right;
}TreeNode;

TreeNode *search(TreeNode * node, element key)  {
    if(node == NULL)     return NULL;
    
    if(key==node->key)
        return node;
    else if(key < node->key)  
        return search(node->left, key);
    else
        return search(node->right, key);
}

TreeNode *new_node(element item)    {
    TreeNode* temp= (TreeNode *)malloc(sizeof(TreeNode));
    temp ->key = item;
    temp->left=temp->right = NULL;
    return temp;
}

TreeNode *insert_node(TreeNode* root, element key)  {
    if(root ==NULL) return new_node(key);
        
    if(key < root->key)
        root->left = insert_node(root->left, key);
    else if(key > root->key)  
        root->right = insert_node(root->right, key);
    else    {
         printf("\n 트리에 동일 키가 있습니다 !");
    }
    return root;
}

TreeNode* min_value_node(TreeNode *node)    {
    TreeNode*current = node;
    while(current->left!=NULL)  {
        current = current ->left;
    }
    return current;
}

void inorder(TreeNode *root)      { //중위순회(LVR)하면 키값은 오름차순으로 정렬됨
    if(root)    {
        inorder(root->left);
        printf("[%d] ", root->key);
        inorder(root->right);
    }
}

TreeNode *delete_node(TreeNode *root, element key)  {
    if(root ==NULL) return NULL;
        
    if(key>root->key)                                       // 키가 루트보다 크면 오른쪽 서브 트리에서 삭제
        root->right = delete_node(root->right, key);
    else if(key<root->key)
        root->left =delete_node(root->left, key);
    else {                                                  //키와 루트가 동일한 경우 해당 노드 삭제
        if(root->left == NULL && root->right == NULL){       //차수가 0인 경우
            free(root);
            return NULL;
        }
        else if( root->left ==NULL || root->right == NULL)  {
            if(root->left == NULL)   {
                TreeNode *temp = root->right;
                free(root);
                return temp;
            }
            else{
                TreeNode*temp = root->left;
                free(root);
                return temp;
            }
        }
        else    {
            TreeNode *temp = min_value_node(root->right);
            root->key= temp->key;
            root->right = delete_node(root->right , temp->key);
        }
    }
    return root;
}

int main()  {
    TreeNode * root = NULL;
    TreeNode * tmp = NULL;

    root = insert_node(root,30);
    root = insert_node(root,20);
    root = insert_node(root,10);
    root = insert_node(root,40);
    root = insert_node(root,50);
    root = insert_node(root,60);
    root = insert_node(root,35);

    printf("이진탐색트리 중위 순회 결과\n");
    inorder(root);
    printf("\n\n");

    tmp = search(root, 30);
    if(tmp != NULL)
        printf("이진탐색트리에서 30을 발견함 \n\n");
    else    
        printf("이진탐색트리에서 30을 발견못함\n\n");
    
    tmp = search(root, 90);
    if(tmp != NULL)
        printf("이진탐색트리에서 90을 발견함 \n\n");
    else    
        printf("이진탐색트리에서 90을 발견못함\n\n");
    
    root = delete_node(root, 60);
    inorder(root);  printf("\n\n");
    
    root = delete_node(root, 20);
    inorder(root);  printf("\n\n");
    
    root = delete_node(root, 30);
    inorder(root);  printf("\n\n");
    
}