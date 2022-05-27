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
         printf("\n Ʈ���� ���� Ű�� �ֽ��ϴ� !");
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

void inorder(TreeNode *root)      { //������ȸ(LVR)�ϸ� Ű���� ������������ ���ĵ�
    if(root)    {
        inorder(root->left);
        printf("[%d] ", root->key);
        inorder(root->right);
    }
}

TreeNode *delete_node(TreeNode *root, element key)  {
    if(root ==NULL) return NULL;
        
    if(key>root->key)                                       // Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ������ ����
        root->right = delete_node(root->right, key);
    else if(key<root->key)
        root->left =delete_node(root->left, key);
    else {                                                  //Ű�� ��Ʈ�� ������ ��� �ش� ��� ����
        if(root->left == NULL && root->right == NULL){       //������ 0�� ���
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

    printf("����Ž��Ʈ�� ���� ��ȸ ���\n");
    inorder(root);
    printf("\n\n");

    tmp = search(root, 30);
    if(tmp != NULL)
        printf("����Ž��Ʈ������ 30�� �߰��� \n\n");
    else    
        printf("����Ž��Ʈ������ 30�� �߰߸���\n\n");
    
    tmp = search(root, 90);
    if(tmp != NULL)
        printf("����Ž��Ʈ������ 90�� �߰��� \n\n");
    else    
        printf("����Ž��Ʈ������ 90�� �߰߸���\n\n");
    
    root = delete_node(root, 60);
    inorder(root);  printf("\n\n");
    
    root = delete_node(root, 20);
    inorder(root);  printf("\n\n");
    
    root = delete_node(root, 30);
    inorder(root);  printf("\n\n");
    
}