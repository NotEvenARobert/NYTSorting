#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <string.h> 

#define MAXSIZE 12
#define NUMGAMES 7
#define TOTAL 6
#define BASECASESIZE 30

const char GAMES[NUMGAMES][MAXSIZE+1] = {

    "Wordle", "Spelling Bee", "Crossword", 
    "Connections", "Strands", "Letter Boxed", "Total"

};

typedef struct Player {

    char *name;
    int scores[NUMGAMES];

} Player;

int compare(Player *ptrP1, Player *ptrP2, int key);
void swap(Player **ptrA, Player **ptrB);
int partition(Player **list, int low, int high, int key);
void quickSortRec(Player **list, int low, int high, int key);
void quickSort(Player **list, int n, int key);
void freeMemory(Player **list, int n);

int main(void) {

    int n;
    scanf("%d", &n);
    Player **playerList = (Player**)malloc(n * sizeof(Player*));
    if(playerList == NULL) {
      
        return 1;
      
    }

    char tempName[MAXSIZE + 2]; 
    for(int a = 0; a < n; a++) {
        
        playerList[a] = (Player*)malloc(sizeof(Player));
        if(playerList[a] == NULL) {

            freeMemory(playerList, a);
            return 1;
          
        }

        scanf("%s", tempName);
        playerList[a]->name = (char*)malloc((strlen(tempName) + 1) * sizeof(char));
        if(playerList[a]->name == NULL) {

            free(playerList[a]);
            freeMemory(playerList, a);
            return 1;
          
        }
        strcpy(playerList[a]->name, tempName);

        int totalScore = 0;
        for(int b = 0; b < TOTAL; b++) {
          
            scanf("%d", &playerList[a]->scores[b]);
            totalScore += playerList[a]->scores[b];
          
        }
        playerList[a]->scores[TOTAL] = totalScore;
          
    }

    int sortKey;
    scanf("%d", &sortKey);

    quickSort(playerList, n, sortKey); 

    printf("%s Ranklist\n", GAMES[sortKey]);
    for(int c = 0; c < n; c++) {

        printf("%d. %-15s %d\n", 
               c + 1, 
               playerList[c]->name, 
               playerList[c]->scores[sortKey]);
      
    }

    freeMemory(playerList, n);
    return 0;
  
}

int compare(Player *ptrP1, Player *ptrP2, int key) {

    int score1 = ptrP1->scores[key];
    int score2 = ptrP2->scores[key];
    if(score1 > score2) {
        
        return -1;
        
    } else if(score1 < score2) {
        
        return 1;
        
    } else {

        return strcmp(ptrP1->name, ptrP2->name);
        
    }
    
}

void insertionSort(Player **list, int low, int high, int key) {

    for(int e = low + 1; e <= high; e++) {
      
        Player *temp = list[e];
        int f = e - 1;
        while(f >= low && compare(list[f], temp, key) > 0) {
          
            list[f + 1] = list[f];
            f--;
          
        }
        list[f + 1] = temp;
      
    }
  
}

void swap(Player **ptrA, Player **ptrB) {
  
    Player *temp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = temp;
  
}

int partition(Player **list, int low, int high, int key) {

    int pivotIndex = low + (rand() % (high - low + 1));
    swap(&list[pivotIndex], &list[high]);
    Player* pivot = list[high];

    int g = low - 1; 
    for(int h = low; h < high; h++) {

        if(compare(list[h], pivot, key) <= 0) {
          
            g++;
            swap(&list[g], &list[h]);
          
        }
      
    }

    swap(&list[g + 1], &list[high]);
    return g + 1;
  
}

void quickSortRec(Player **list, int low, int high, int key) {

    if(high - low + 1 <= BASECASESIZE) {

        insertionSort(list, low, high, key);
        return;
      
    }

    if(low < high) {

        int pivotIndex = partition(list, low, high, key);
        quickSortRec(list, low, pivotIndex - 1, key);
        quickSortRec(list, pivotIndex + 1, high, key);
      
    }
  
}

void quickSort(Player **list, int n, int key) {

    srand(time(NULL)); 
    if(n > 0) {
      
        quickSortRec(list, 0, n - 1, key);
      
    }
  
}

void freeMemory(Player **list, int n) {
    
    for(int d = 0; d < n; d++) {
      
        if(list[d] != NULL) {
          
            free(list[d]->name);
            free(list[d]);
          
        }
      
    }
    free(list);
  
}
