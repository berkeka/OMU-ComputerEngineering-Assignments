#include<stdio.h>
#include<stdlib.h>

char* studentNames[] = {"AAAA", "BBBB", "CCCC", "DDDD"};
int studentNumbers[] = {5, 1, 11 ,4444};

struct student {
  char* studentName;
  int studentNumber;
  struct student *nextStudent;
};

typedef struct student Student;

void addStudent(Student **headOfList, int studentNumber, char* studentName);
void deleteStudent(Student **headOfList, int studentNumber);
void printStudentList(Student *headOfList);
int getNumberOfStudents(Student* headOfList);

int main(void){
  Student* headOfList = NULL;
    //Add Students
  addStudent(&headOfList,studentNumbers[0],studentNames[0]);
  addStudent(&headOfList,studentNumbers[1],studentNames[1]);
  addStudent(&headOfList,studentNumbers[2],studentNames[2]);
  addStudent(&headOfList,studentNumbers[3],studentNames[3]);
  deleteStudent(&headOfList,studentNumbers[1]);

  printStudentList(headOfList);
  printf("Number of Students: %-5d\n",getNumberOfStudents(headOfList));

  return 0;
}

void addStudent(Student **headOfList, int studentNumber, char* studentName){
  Student* newStudent = (Student*)malloc(sizeof(Student));
  if(newStudent == NULL){
    printf("There is no space available for a new Student.");
    exit(EXIT_FAILURE);
  }
  else{
    newStudent->studentName = studentName;
    newStudent->studentNumber = studentNumber;

    Student* currentStudent = *headOfList;

    if(currentStudent == NULL || (*headOfList)->studentNumber >= newStudent->studentNumber){
      newStudent->nextStudent = *headOfList;
      *headOfList = newStudent;
    }
    else{
      while(currentStudent->nextStudent != NULL
        && currentStudent->nextStudent->studentNumber
        < newStudent->studentNumber){
               currentStudent = currentStudent->nextStudent;
             }
      newStudent->nextStudent = currentStudent->nextStudent;
      currentStudent->nextStudent = newStudent;
    }
  }
}
void deleteStudent(Student **headOfList, int studentNumber){
    Student* currentStudent = *headOfList;
    Student* previousStudent = NULL;
    if(currentStudent == NULL){
        printf("The list is empty");
        exit(EXIT_FAILURE);
    }
    else{
        while(currentStudent != NULL){
            if(currentStudent->studentNumber == studentNumber){
              if(previousStudent == NULL){
                (*headOfList) = currentStudent->nextStudent;
                free(currentStudent);
              }
              else{
                previousStudent->nextStudent = currentStudent->nextStudent;
                free(currentStudent);
              }
            }
            previousStudent = currentStudent;
            currentStudent = currentStudent->nextStudent;
        }
    }
}

void printStudentList(Student *headOfList){
  if(headOfList == NULL){
    printf("The list is empty.");
  }
  else{
    Student* currentStudent = headOfList;
    while(currentStudent != NULL){
      printf("Number: %-5d  Name: %-5s\n", currentStudent->studentNumber, currentStudent->studentName);
      currentStudent = currentStudent->nextStudent;
    }
  }
}

int getNumberOfStudents(Student *headOfList){
  Student* currentStudent = headOfList;
  if(currentStudent == NULL){
    return 0;
  }
  else{
    int count = 0;
    while(currentStudent != NULL){
      count++;
      currentStudent = currentStudent->nextStudent;
    }
    return count;
  }
}
