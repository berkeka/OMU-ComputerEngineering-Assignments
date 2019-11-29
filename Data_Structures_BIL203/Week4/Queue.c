#include<stdio.h>
#include<stdlib.h>

char* studentNames[] = {"AAAA", "BBBB", "CCCC"};
int studentNumbers[] = {1111, 2222, 3333};

struct student{
  int studentNumber;
  char* studentName;
  struct student *nextstudent;
};

typedef struct student Student;

void queueStudent(Student **headOfQueue, int studentNumber, char* studentName);
void dequeueStudent(Student **headOfQueue, Student *temporaryStudent);
void printQueue(Student *headOfQueue);

int main(void){
  Student* headOfQueue = NULL;
  Student* temporaryStudent = (Student*)malloc(sizeof(Student));

  queueStudent(&headOfQueue, studentNumbers[0], studentNames[0]);
  queueStudent(&headOfQueue, studentNumbers[1], studentNames[1]);
  queueStudent(&headOfQueue, studentNumbers[2], studentNames[2]);
  printQueue(headOfQueue);
  dequeueStudent(&headOfQueue, temporaryStudent);
  printf("Dequeued student-> Number: %-5d  Name: %-s\n",temporaryStudent->studentNumber,temporaryStudent->studentName);
  printQueue(headOfQueue);
  return 0;
}

void queueStudent(Student **headOfQueue, int studentNumber, char* studentName){
  Student* newStudent = (Student*)malloc(sizeof(Student));

  if(newStudent == NULL){
    printf("No space available for a new student.\n");
    exit(EXIT_FAILURE);
  }
  else{
    newStudent->studentName = studentName;
    newStudent->studentNumber = studentNumber;
    Student* currentStudent = *headOfQueue;
    if(currentStudent == NULL){
      newStudent->nextstudent = NULL;
      currentStudent = newStudent;
      (*headOfQueue) = currentStudent;
    }
    else{
      while(currentStudent != NULL){
        if(currentStudent->nextstudent == NULL){
          currentStudent->nextstudent = newStudent;
          newStudent->nextstudent = NULL;
        }
        currentStudent = currentStudent->nextstudent;
      }
    }
  }
}

void dequeueStudent(Student **headOfQueue, Student *temporaryStudent){
  Student *currentStudent = *headOfQueue;
  if(currentStudent == NULL){
    printf("The Queue is already empty.\n");
  }
  else{
    (*temporaryStudent) = *currentStudent;
    (*headOfQueue) = currentStudent->nextstudent;
    free(currentStudent);
  }
}

void printQueue(Student *headOfQueue){
  Student* currentStudent = headOfQueue;
  if(currentStudent == NULL){
    printf("The Queue is empty.\n");
  }
  else{
    while(currentStudent != NULL){
      printf("Number: %-5d   Name: %-s\n",currentStudent->studentNumber, currentStudent->studentName);
      currentStudent = currentStudent->nextstudent;
    }
  }
}
