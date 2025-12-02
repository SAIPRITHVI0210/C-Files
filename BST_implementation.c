#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node* create(int value){
    struct node *newnode;
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode -> data = value;
    newnode -> left = NULL;
    newnode -> right = NULL;
    return newnode;
}

struct node* insert(struct node *root,int value){
    if(root == NULL){
        return create(value);
    }
    if(value < root -> data){
        root -> left = insert(root -> left,value);
    }
    else{
        root -> right = insert(root -> right,value);
    }
    return root;
}

void inorder(struct node *root){
    if(root == NULL){
        return;
    }
    inorder(root -> left);
    printf("%d ",root -> data);
    inorder(root -> right);
}

void preorder(struct node *root){
    if(root == NULL){
        return;
    }
    printf("%d ",root -> data);
    preorder(root -> left);
    preorder(root -> right);
}

void postorder(struct node *root){
    if(root == NULL){
        return;
    }
    postorder(root -> left);
    postorder(root -> right);
    printf("%d ",root -> data);
}

struct node* findMin(struct node *root){
    while(root -> left != NULL){
        root = root -> left;
    }
    return root;
}

struct node* findMax(struct node *root){
    while(root -> right != NULL){
        root = root -> right;
    }
    return root;
}

struct node* deleteNode(struct node *root,int key){
    if(root == NULL){
        return root;
    }
    if(key < root -> data){
        root -> left = deleteNode(root -> left,key);
    }
    else if(key > root -> data){
        root -> right = deleteNode(root -> right,key);
    }
    else{
        //Node with no child or 1 child
        if(root -> left == NULL){
            struct node *temp = root -> right;
            free(root);
            return temp;
        }
        else if(root -> right == NULL){
            struct node *temp = root -> left;
            free(root);
            return temp;
        }
        // Node with 2 children (Using inorder predecessor)
        /*struct node *temp = findMax(root -> left);
        root -> data = temp -> data;
        root -> left = deleteNode(root -> left,temp -> data);*/

        // Node with 2 children (Using inorder successor)
        struct node *temp = findMin(root -> right);
        root -> data = temp -> data;
        root -> right = deleteNode(root -> right,temp -> data);
    }
}

void kthSmallestUtil(struct node *root,int key,int *count,int *result){
    if(root == NULL || *count > key){
        return;
    }
    kthSmallestUtil(root -> left,key,count,result);

    (*count)++;
    if(*count == key){
        *result = root -> data;
        return;
    }
    kthSmallestUtil(root -> right,key,count,result);
}

int kthSmallest(struct node *root,int key){
    int count = 0,result = -1;
    kthSmallestUtil(root,key,&count,&result);
    return result;
}

int main() {
    struct node *root = NULL;

    // Insert elements
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");

    // Delete a node
    printf("\nDeleting node 20...\n");
    root = deleteNode(root, 20);

    printf("Inorder after deletion: ");
    inorder(root);
    printf("\n");

    printf("\nDeleting node 50...\n");
    root = deleteNode(root, 50);

    printf("Inorder after deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}