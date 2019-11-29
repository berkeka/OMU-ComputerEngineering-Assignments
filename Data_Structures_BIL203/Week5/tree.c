#include<stdio.h>
#include<stdlib.h>

struct treeNode{
  int data;
  struct treeNode *leftTreeNode;
  struct treeNode *rightTreeNode;
};

typedef struct treeNode TreeNode;

void insertTreeNode(TreeNode **rootOfTree, int data);
void inorderTraversal(TreeNode *rootOfTree);
void postorderTraversal(TreeNode *rootOfTree);
void preorderTraversal(TreeNode *rootOfTree);
int findTreeMaximum(TreeNode *rootOfTree);
int findTreeMinimum(TreeNode *rootOfTree);

int main(void){
  TreeNode *rootOfTree = NULL;

  insertTreeNode(&rootOfTree, 38);
  insertTreeNode(&rootOfTree, 65);
  insertTreeNode(&rootOfTree, 12);
  insertTreeNode(&rootOfTree, 77);
  insertTreeNode(&rootOfTree, 100);
  insertTreeNode(&rootOfTree, -55);

  postorderTraversal(rootOfTree);
  printf("\n");
  inorderTraversal(rootOfTree);
  printf("\n");
  preorderTraversal(rootOfTree);
  printf("\n");

  printf("Maximum: %-5d\n",findTreeMaximum(rootOfTree));
  printf("Minimum: %-5d\n",findTreeMinimum(rootOfTree));

  return 0;
}

void insertTreeNode(TreeNode **rootOfTree, int data){
  TreeNode *currentTreeNode = (*rootOfTree);
  if (currentTreeNode == NULL){
    TreeNode* newTreeNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newTreeNode == NULL){
      printf("There is no memory.\n");
      exit(EXIT_FAILURE);
    }
    else{
      newTreeNode->data = data;
      newTreeNode->leftTreeNode = NULL;
      newTreeNode->rightTreeNode = NULL;
      (*rootOfTree) = newTreeNode;
    }
  }
  else{
    if(data < currentTreeNode->data){
      insertTreeNode(&(currentTreeNode->leftTreeNode), data);
    }
    else if(data > currentTreeNode->data){
      insertTreeNode(&(currentTreeNode->rightTreeNode), data);
    }
    else{
      printf("Duplicate data\n");
    }
  }
}

void inorderTraversal(TreeNode *rootOfTree){
  TreeNode *currentTreeNode = rootOfTree;
  if(currentTreeNode != NULL){
    inorderTraversal(currentTreeNode->leftTreeNode);
    printf("%-6d  ", currentTreeNode->data);
    inorderTraversal(currentTreeNode->rightTreeNode);
  }
}

void postorderTraversal(TreeNode *rootOfTree){
  TreeNode *currentTreeNode = rootOfTree;
  if(currentTreeNode != NULL){
    postorderTraversal(currentTreeNode->leftTreeNode);
    postorderTraversal(currentTreeNode->rightTreeNode);
    printf("%-6d  ", currentTreeNode->data);
  }
}

void preorderTraversal(TreeNode *rootOfTree){
  TreeNode *currentTreeNode = rootOfTree;
  if(currentTreeNode != NULL){
    printf("%-6d  ", currentTreeNode->data);
    preorderTraversal(currentTreeNode->leftTreeNode);
    preorderTraversal(currentTreeNode->rightTreeNode);
  }
}

int findTreeMaximum(TreeNode *rootOfTree){
  TreeNode *currentTreeNode = rootOfTree;
  while(currentTreeNode->rightTreeNode != NULL){
    currentTreeNode = currentTreeNode->rightTreeNode;
  }
  return (currentTreeNode->data);
}

int findTreeMinimum(TreeNode *rootOfTree){
  TreeNode *currentTreeNode = rootOfTree;
  while(currentTreeNode->leftTreeNode != NULL){
    currentTreeNode = currentTreeNode->leftTreeNode;
  }
  return (currentTreeNode->data);
}
