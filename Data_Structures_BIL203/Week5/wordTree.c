#include<stdio.h>
#include<stdlib.h>

char* surnames[] = {"doğan", "baştan", "kaptan", "özcan", "kalkan", "canan", "aslan", "iyigün", "aydın"};

struct treeNode{
  char* data;
  struct TreeNode *leftTreeNode;
  struct TreeNode *rightTreeNode;
};

typedef struct treeNode TreeNode;

void insertTreeNode(TreeNode **rootOfTree, char* data);
void inorderTraversal(TreeNode *rootOfTree);
void postorderTraversal(TreeNode *rootOfTree);
void preorderTraversal(TreeNode *rootOfTree);

int main(void){
  TreeNode *rootOfTree = NULL;
  int i = 0;
  while(surnames[i] != NULL){
    insertTreeNode(&rootOfTree, surnames[i]);
    i++;
  }

  inorderTraversal(rootOfTree);
  printf("\n\n");
  postorderTraversal(rootOfTree);
  printf("\n\n");
  preorderTraversal(rootOfTree);


  return 0;
}

void insertTreeNode(TreeNode **rootOfTree, char*data){
  TreeNode *currentTreeNode = (*rootOfTree);
  if(currentTreeNode == NULL){
    TreeNode *newTreeNode = (TreeNode*)malloc(sizeof(TreeNode));
    if(newTreeNode == NULL){
      printf("No space is available for another node.\n");
      exit(EXIT_FAILURE);
    }
    else{
      newTreeNode->data = data;
      newTreeNode->rightTreeNode = NULL;
      newTreeNode->leftTreeNode = NULL;
      (*rootOfTree) = newTreeNode;
    }
  }
  else{
    if(charCompare(currentTreeNode->data, data) == 1){
      insertTreeNode(&(currentTreeNode->leftTreeNode), data);
    }
    else if(charCompare(currentTreeNode->data, data) == 2){
      insertTreeNode(&(currentTreeNode->rightTreeNode), data);
    }
    else{
      printf("Duplicate data.\n");
    }
  }
}

void inorderTraversal(TreeNode *rootOfTree){
  TreeNode *currenTreeNode = rootOfTree;
  if(currenTreeNode != NULL){
    inorderTraversal(currenTreeNode->leftTreeNode);
    printf("%-s\n", (currenTreeNode->data));
    inorderTraversal(currenTreeNode->rightTreeNode);
  }
}

void postorderTraversal(TreeNode *rootOfTree){
  TreeNode *currentTreeNode = rootOfTree;
  if(currentTreeNode != NULL){
    postorderTraversal(currentTreeNode->leftTreeNode);
    postorderTraversal(currentTreeNode->rightTreeNode);
    printf("%-s\n", currentTreeNode->data);
  }
}

void preorderTraversal(TreeNode *rootOfTree){
  TreeNode *currentTreeNode = rootOfTree;
  if(currentTreeNode != NULL){
    printf("%-s\n", currentTreeNode->data);
    preorderTraversal(currentTreeNode->leftTreeNode);
    preorderTraversal(currentTreeNode->rightTreeNode);
  }
}

int charCompare(char *current, char *new){
  //Returns 1 if current > new
  //Returns 2 if current < new
  //Returns 0 if current = new
  int index = 0;
  for(index; current[index]; index++){
    if(current[index] > new[index]){
      return 1;
    }
    else if(current[index] < new[index]){
      return 2;
    }
    else{
      continue;
    }
  }
  return 0;
}
