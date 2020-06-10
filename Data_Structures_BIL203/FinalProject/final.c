#include<stdio.h>
#include<stdlib.h>

// map consists of arrays of chars
// For every item, value of index 0 is the name of the city and the rest are neighbours of that city
char map[][10] = {
  {'A', 'B', 'D', 'F', 'H'},
  {'B', 'A', 'C', 'J', 'R', 'I'},
  {'C', 'R', 'B', 'D', 'Q'},
  {'D', 'C', 'E', 'Q', 'A', 'P'},
  {'E', 'D', 'P', 'F', 'N'},
  {'F', 'A', 'N', 'E', 'M', 'G'},
  {'G', 'F', 'H', 'M', 'L'},
  {'H', 'A', 'G', 'I', 'L', 'K'},
  {'I', 'B', 'H', 'K', 'J'},
  {'J', 'B', 'I'},
  {'K', 'I', 'H'},
  {'L', 'H', 'G'},
  {'M', 'G', 'F'},
  {'N', 'F', 'E'},
  {'P', 'E', 'D'},
  {'Q', 'D', 'C'},
  {'R', 'C', 'B'}
};

struct roadNode{
  char cityName;
  struct roadNode *next;
};

typedef struct roadNode RoadNode;

void pushRoadToStack(RoadNode **headOfStack, char cityName);
void printStack(RoadNode *headOfStack, char secondCityName);
void popRoadFromStack(RoadNode **headOfStack);
void findPossibleRoads(RoadNode** allPossibleRoutes, char firstCityName, char secondCityName,RoadNode **resultStack);
int findCityInArray(int cityName);
int findCityInArray2(char firstDimension, char secondDimension);
int charIsAlreadyUsed(RoadNode *headOfStack, char cityName);
void solve(RoadNode ** headOfStack, char selectedCity,RoadNode **resultStack, char secondCityName, int i);
void addPathToResultStack(RoadNode **headOfStack, RoadNode **resultStack);
void getWantedPaths(RoadNode *resultStack,RoadNode **LongestPathStack, char firstCityName, char secondCityName, int maxLength);
void printThreeNeighboringPath(RoadNode *resultStack, char firstCityName, char secondCityName);
int findMaxRoadLength(RoadNode *resultStack, char secondCityName);

int main(void){
  RoadNode *headOfStack = NULL;
  RoadNode *resultStack = NULL;
  RoadNode *longestPathStack = NULL;
  RoadNode *threeNeigborStack = NULL;

  //Stacks that are now not reversed
  RoadNode *finalLongestPathStack = NULL;
  RoadNode *finalThreeNeighborStack = NULL;

  char firstCityName, secondCityName;
  // Get city names - assumes correct input
  printf("Enter the first city (uppercase)\n");
  scanf(" %c",&firstCityName);
  printf("Enter the second city (uppercase)\n");
  scanf(" %c",&secondCityName);

  findPossibleRoads(&headOfStack, firstCityName, secondCityName, &resultStack);

  //find the length of the longest Path
  int maxLength = findMaxRoadLength(resultStack,secondCityName);

  //Get the paths with the wanted length
  getWantedPaths(resultStack, &longestPathStack, firstCityName, secondCityName, maxLength);
  getWantedPaths(resultStack, &threeNeigborStack, firstCityName, secondCityName, 5);

  //Reverse the stacks
  addPathToResultStack(&longestPathStack, &finalLongestPathStack);
  addPathToResultStack(&threeNeigborStack, &finalThreeNeighborStack);

  //Print all the stacks
  printf("--- All possible paths\n");
  printStack(resultStack, secondCityName);
  printf("--- Longest possible path or paths.  Length = %d\n", maxLength);
  printStack(finalLongestPathStack, secondCityName);
  printf("--- Paths that have 3 neigbors between the start and finish\n");
  printStack(finalThreeNeighborStack, secondCityName);

  return 0;
}
void solve(RoadNode ** headOfStack, char selectedCity,RoadNode **resultStack, char secondCityName,int i){
  //Iterate to find a legal city
  for(i; map[findCityInArray(selectedCity)][i]; ++i){
    char currentCityName = map[findCityInArray(selectedCity)][i];
    if(!(charIsAlreadyUsed(*headOfStack, currentCityName))){
      //City is legal
      //Push city to stack

      pushRoadToStack(headOfStack, currentCityName);
      selectedCity = currentCityName;
      if(currentCityName == secondCityName){
        //Found a correct path

        addPathToResultStack(headOfStack, resultStack);
        char poppedCity = (*headOfStack)->cityName;
        popRoadFromStack(headOfStack);
        selectedCity = (*headOfStack)->cityName;
        i = findCityInArray2(selectedCity, poppedCity);
        // make a recursive call and continue searching for another city
        return solve(headOfStack, selectedCity, resultStack, secondCityName, i + 1);
      }
      return solve(headOfStack, selectedCity,resultStack,secondCityName, 0);
    }
    else{
      //City isnt legal
    }
  }
  //None of the neighbours are available
  //Pop one and search for another neighbor
  char poppedCity = (*headOfStack)->cityName;
  if((*headOfStack)->next == NULL){
    return;
  }
  popRoadFromStack(headOfStack);
  selectedCity = (*headOfStack)->cityName;
  i = findCityInArray2(selectedCity, poppedCity);
  return solve(headOfStack, selectedCity, resultStack, secondCityName, i + 1);
}

void findPossibleRoads(RoadNode** headOfStack,char firstCityName, char secondCityName,RoadNode **resultStack){
  pushRoadToStack(headOfStack, firstCityName);
  int i = 0;
  char selectedCity = map[findCityInArray(firstCityName)][i];
  solve(headOfStack, selectedCity, resultStack, secondCityName, i);

}
int findCityInArray(int cityName){
  // finds the index of the entered cityName
  int index;
  for(index = 0; map[index][0] != '\0'; index++){
    if(map[index][0] == cityName){
      return index;
    }
  }
  // IF returned -1 input isnt on the map
  return -1;
}
int findCityInArray2(char firstDimension, char secondDimension){
  int index;
  for(index = 0;map[findCityInArray(firstDimension)][index] != '\0';index++){
    if(map[findCityInArray(firstDimension)][index] == secondDimension){
      return index;
    }
  }
}

void pushRoadToStack(RoadNode **headOfStack,char cityName){
  RoadNode *newCity = (RoadNode*)malloc(sizeof(RoadNode));
  if(newCity == NULL){
    printf("No space available for another city");
    //EXIT
  }
  else{
    //push new city
    newCity->cityName = cityName;
    newCity->next = (*headOfStack);
    //make the added student head of the stack
    (*headOfStack) = newCity;
  }
}
void popRoadFromStack(RoadNode **headOfStack){
  RoadNode *currentCity = *headOfStack;
  if(currentCity == NULL){
    printf("Stack is already empty.\n");
  }
  else{
    (*headOfStack) = currentCity->next;
    free(currentCity);
  }
}
void printStack(RoadNode *headOfStack, char secondCityName){
  RoadNode *currentCity = headOfStack;
  if(currentCity == NULL){
    printf("Stack is empty\n");
  }
  else{
    int counter = 0;
    while(currentCity != NULL){
      if(currentCity->cityName == secondCityName){
        printf("%c\n", currentCity->cityName);
        counter++;
      }
      else{
        printf("%c --> ",currentCity->cityName);
      }
      currentCity = currentCity->next;
    }
    printf("Number of Routes: %d\n", counter);
  }
}
// Gets paths with the given length
void getWantedPaths(RoadNode *resultStack, RoadNode **longestPathStack, char firstCityName, char secondCityName, int maxLength){
  RoadNode *currentCity = resultStack;
  int counter = 1;
  while(currentCity != NULL){
    pushRoadToStack(longestPathStack, currentCity->cityName);
    if(currentCity->cityName == secondCityName){
      if(counter != maxLength){
        popRoadFromStack(longestPathStack);
        RoadNode *currentLongCity = (*longestPathStack);
        while(currentLongCity != NULL && currentLongCity->cityName != secondCityName){
          popRoadFromStack(longestPathStack);
          currentLongCity = currentLongCity->next;
        }
      }
      counter = 0;
    }
    counter++;
    currentCity = currentCity->next;
  }
}
// Finds the max path length
int findMaxRoadLength(RoadNode *resultStack, char secondCityName){
  RoadNode *currentCity = resultStack;
  int counter = 1;
  int max = 0;
  while(currentCity != NULL){
    if(currentCity->cityName == secondCityName){
      if(counter > max){
        max = counter;
      }
      counter = 0;
    }
    counter++;
    currentCity = currentCity->next;
  }
  return max;
}

int charIsAlreadyUsed(RoadNode *headOfStack, char cityName){
  RoadNode *currentCity = headOfStack;
  while(currentCity != NULL){
    if(currentCity->cityName == cityName){
      return 1;
    }
    currentCity = currentCity->next;
  }
  return 0;
}
void addPathToResultStack(RoadNode **headOfStack, RoadNode **resultStack){
  RoadNode *currentCity = *headOfStack;
  while(currentCity != NULL){
    pushRoadToStack(resultStack, currentCity->cityName);
    currentCity = currentCity->next;
  }
}
