#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMBER_OF_WORDS 2344

typedef struct word{
    char slots[5];
    char forbidden[5][5];
    char grays[5][100];
    int numAmarelas[5];
    int numGrays[5];
} Word;

void deleteWord(char** possibleWords, int *n, int key) {
  	free(possibleWords[key]);
    for (int j = key; j < *n - 1; j++) {
        possibleWords[j] = possibleWords[j + 1];
    }
  
    (*n)--; 
}

int grayExistsInArrays(Word *word, char x){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < word->numGrays[i]; j++)
            if(word->grays[i][j] == x) return 1;
    }
    return 0;
}

int grayExistsInYellows(Word *word, char x){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < word->numAmarelas[i]; j++)
            if(word->forbidden[i][j] == x) return 1;
    }
    return 0;
}

int letterChance(char letter){
    switch (letter) {
        case 'A':
            return 906;
        case 'B':
            return 266;
        case 'C':
            return 446;
        case 'D':
            return 370;
        case 'E':
            return 1053;
        case 'F':
            return 206;
        case 'G':
            return 299;
        case 'H':
            return 377;
        case 'I':
            return 646;
        case 'J':
            return 27;
        case 'K':
            return 202;
        case 'L':
            return 645;
        case 'M':
            return 298;
        case 'N':
            return 548;
        case 'O':
            return 672;
        case 'P':
            return 345;
        case 'Q':
            return 29;
        case 'R':
            return 835;
        case 'S':
            return 617;
        case 'T':
            return 667;
        case 'U':
            return 456;
        case 'V':
            return 148;
        case 'W':
            return 193;
        case 'X':
            return 37;
        case 'Y':
            return 416;
        case 'Z':
            return 35;
    }
    return 0;
}

void getColors(char *firstColor, char *secondColor, char *thirdColor, char *fourthColor, char *fifthColor){
    scanf(" %c", firstColor);
    scanf(" %c", secondColor);
    scanf(" %c", thirdColor);
    scanf(" %c", fourthColor);
    scanf(" %c", fifthColor);

    if(*firstColor == 'G' &&
       *secondColor == 'G' &&
       *thirdColor == 'G' &&
       *fourthColor == 'G' &&
       *fifthColor == 'G'){
        
        printf("Congrats!!!\n");
        exit(0);
    }
}

void convertToWord(char firstColor, char secondColor, char thirdColor, char fourthColor, char fifthColor, Word *currWord, char *lastWord){
    char colors[5] = { firstColor, secondColor, thirdColor, fourthColor, fifthColor };

    for (int i = 0; i < 5; i++) {
        if (colors[i] == 'G')
            currWord->slots[i] = lastWord[i];
        
        else if (colors[i] == 'Y')
            currWord->forbidden[i][currWord->numAmarelas[i]++] = lastWord[i];
        
        else if(!grayExistsInArrays(currWord, lastWord[i]))
            currWord->grays[i][currWord->numGrays[i]++] = lastWord[i];
    }
}

char** getWordsFromFile(){
    FILE* words;
    char* currWord = malloc(8*sizeof(char));
    int i = 0;
    char **possibleWords = malloc(NUMBER_OF_WORDS * sizeof(char*));

    for(int j = 0; j < NUMBER_OF_WORDS; j++)
        possibleWords[j] = malloc(8*sizeof(char));
    

    words = fopen("words.txt", "r");
    
    if (words == NULL) {
        printf("The file is not opened.");
    }

    else{
        while (i < NUMBER_OF_WORDS && fgets(currWord, 8, words)) {
            currWord[strcspn(currWord, "\n")] = '\0';
            strcpy(possibleWords[i++], currWord);

        }
    }

    fclose(words);
    free(currWord);
    return possibleWords;
}

int letterExists(char *palavra, char letra){
    for(int i = 0; i < 5; i++)
        if(palavra[i] == letra) return 1;

    return 0;
}

void handleGreenYellowGray(char **possibleWords, Word *currWord, int *n) {
    int i, j;
    for (i = 0; i < 5; i++) {
        int j = 0;
        while (j < *n) {
            int removed = 0;

            if(currWord->slots[i] != ' ' && currWord->slots[i] != possibleWords[j][i]){
                deleteWord(possibleWords, n, j);
                removed = 1;
            }

            if(!removed && currWord->numAmarelas[i] > 0){
                for(int k=0; k < currWord->numAmarelas[i]; k++){
                    char forbiddenLetter = currWord->forbidden[i][k];
                    if(possibleWords[j][i] == forbiddenLetter || !letterExists(possibleWords[j], forbiddenLetter)){
                        deleteWord(possibleWords, n, j);
                        removed = 1;
                        break;
                    }
                }
            }

            if(!removed){
                for(int k=0; k < currWord->numGrays[i]; k++){
                    char grayLetter = currWord->grays[i][k];
                    if(possibleWords[j][i] == grayLetter){
                        deleteWord(possibleWords, n, j);
                        removed = 1;
                        break;
                    }
                    else if(!letterExists(currWord->slots, grayLetter) && !grayExistsInYellows(currWord, grayLetter) && letterExists(possibleWords[j], grayLetter)){
                        deleteWord(possibleWords, n, j);
                        removed = 1;
                        break;
                    }
                }
            }
            if(!removed) j++;
        }

    }
}

int repetedLettersAux(char *palavra, int n, char letra){
    for(int i = 0; i < n; i++)
        if(palavra[i] == letra) return 1;

    return 0;
}

int repetedLetters(char* word){
    char *letters = malloc(5*sizeof(char));
    int res = 0;
    int n = 0;
    for(int i = 0; i < 5; i++){
        if(repetedLettersAux(letters, n, word[i])){
            res += letterChance(word[i]);
        }
        else
            letters[n++] = word[i];

    }
}

char* selectWord(char **possibleWords, int n){
    if (n <= 0) return NULL;

    int bestWordPos;
    int bestWordVal = 0;
    int currWordVal = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 5; j++)
            currWordVal += letterChance(possibleWords[i][j]);
        currWordVal -= repetedLetters(possibleWords[i]);
        if(currWordVal > bestWordVal){
            bestWordVal = currWordVal;
            bestWordPos = i;
        }
        currWordVal = 0;
    }
    
    return possibleWords[bestWordPos];
}

int main(){
    int N = 0;
    int n = NUMBER_OF_WORDS;
    char firstColor, secondColor, thirdColor, fourthColor, fifthColor;
    char lastWord[8] = "AUDIO";
    char **possibleWords;
    
    possibleWords = getWordsFromFile();

    Word *currWord = malloc(sizeof(Word));

    for(int i = 0; i < 5; i++){
        currWord->numGrays[i] = 0;
    }
    
    for (int i = 0; i < 5; i++)
        for(int j = 0; j < 100; j++)
            currWord->grays[i][j] = ' ';

    for (int i = 0; i < 5; i++)
        currWord->slots[i] = ' ';

    for(int i = 0; i < 5; i++){
        currWord->numAmarelas[i] = 0;
        for(int j = 0; j < 5; j++)
            currWord->forbidden[i][j] = ' ';
    }

    while (N++ < 5){

        printf("Use the word %s\n\n", lastWord);

        getColors(&firstColor, &secondColor, &thirdColor, &fourthColor, &fifthColor);
        
        convertToWord(firstColor, secondColor, thirdColor, fourthColor, fifthColor, currWord, lastWord);
        handleGreenYellowGray(possibleWords, currWord, &n);
        char *next = selectWord(possibleWords, n);
        if (next == NULL) {
            printf("Word not found.\n");
            exit(1);
        }
        strcpy(lastWord, next);

        for(int teste = 0; teste < n; teste++){
            printf("%s\n", possibleWords[teste]);
        }
    }
    printf("Use the word %s\n\n", lastWord);
    free(currWord);
    free(possibleWords);
    return 0;
}

