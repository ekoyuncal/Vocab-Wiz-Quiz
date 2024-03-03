#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    char type[10];
    char eng_mean[50];
    char tr_mean[50];
} Word;

void wordSave() {
    char file_name[50];
    printf("Enter the name of the file to be saved: ");
    scanf("%s", file_name);

    FILE *opened_file = fopen(file_name, "a");
    if (opened_file == NULL) {
        printf("File could not be opened!\n");
        return;
    }

    while(1){
        Word new_word;
        printf("Enter the type of the word (N, Adj, etc.) or 'exit' to finish: ");
        scanf("%s", new_word.type);
        if (strcmp(new_word.type, "exit") == 0) break;

        printf("Enter the word in English: ");
        scanf("%s", new_word.eng_mean);

        printf("Enter the meaning of the word in Turkish: ");
        scanf("%s", new_word.tr_mean);
        getchar();

        //Check
        printf("You have entered: %s %s %s. Save? (Y/N): ", new_word.type, new_word.eng_mean, new_word.tr_mean);
        char confirmation;
        scanf(" %c", &confirmation);
        if (confirmation == 'Y' || confirmation == 'y') {
            fprintf(opened_file, "%s %s %s\n", new_word.type, new_word.eng_mean, new_word.tr_mean);
            printf("Word saved successfully.\n");
        }
        else {
            printf("Word not saved. Please re-enter the word.\n");
        }
    }
    fclose(opened_file);
}

int loadWords(const char* fileName, Word words[], int maxWords) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("File could not be opened!\n");
        return 0;
    }

    int count = 0;
    while (count < maxWords && fscanf(file, "%s %s %s", words[count].type, words[count].eng_mean, words[count].tr_mean) == 3) {
        count++;
    }

    fclose(file);
    return count;
}

void quiz(Word words[], int wordCount) {
    srand(time(NULL)); // rand start 
	
	int i;
    for (i = 0; i < wordCount; i++) {
        int correctAnswer = rand() % 3;
        int wrongAnswer1, wrongAnswer2;

        do {
            wrongAnswer1 = rand() % wordCount;
        } while (wrongAnswer1 == i);

        do {
            wrongAnswer2 = rand() % wordCount;
        } while (wrongAnswer2 == i || wrongAnswer2 == wrongAnswer1);

        printf("What is the meaning of '%s'?\n", words[i].eng_mean);
        int j;
        for (j = 0; j < 3; j++) {
            if (j == correctAnswer) {
                printf("%c) %s\n", 'A' + j, words[i].tr_mean);
            } else if (j == (correctAnswer + 1) % 3) {
                printf("%c) %s\n", 'A' + j, words[wrongAnswer1].tr_mean);
            } else {
                printf("%c) %s\n", 'A' + j, words[wrongAnswer2].tr_mean);
            }
        }

        char userAnswer;
        printf("Your answer: ");
        scanf(" %c", &userAnswer);
        getchar();

        if (userAnswer - 'A' == correctAnswer) {
            printf("Correct!\n\n");
        } else {
            printf("Wrong! The correct answer was %c) %s\n\n", 'A' + correctAnswer, words[i].tr_mean);
        }
    }
}

void wordLearn() {
    char fileName[50];
    printf("Enter the name of the file to learn from: ");
    scanf("%s", fileName);

    Word words[100]; // Max 100 Word
    int wordCount = loadWords(fileName, words, 100);

    if (wordCount > 0) {
        quiz(words, wordCount);
    } else {
        printf("No words to learn.\n");
    }

}

int main(){

    //wordSave();
	wordLearn();



    return 0;
}
