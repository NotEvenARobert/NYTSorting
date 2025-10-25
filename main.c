#include <stdio.h>
#include <stdlib.h>
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

    char* name;
    int scores[NUMGAMES];

} Player;

int compare(Player *ptrP1, Player *ptrP2, int key);
void mergeSort(Player **list, int n, int key);
// ... other prototypes ...
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

    // --- TODO: Call Sorting Function ---
    // mergeSort(playerList, n, sortKey); 
    // We'll add this for main1.c
    
    // ... or ...
    
    // quickSort(playerList, n, sortKey); 
    // We'll add this for main2.c

    // --- TODO: Print Output ---
    printf("%s Ranklist\n", GAMES[sortKey]);
    for(int c = 0; c < n; c++) {

        printf("%d. %-15s %d\n", 
               c + 1, 
               playerList[c]->name, 
               playerList[c]->scores[sortKey]);
      
    }


    // --- TODO: Free Memory ---
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

void freeMemory(Player **list, int n) {
    for(int d = 0; d < n; d++) {
      
        if(list[d] != NULL) {
          
            free(list[d]->name);
            free(list[d]);
          
        }
      
    }
    free(list);
  
}
