
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_TRIES 6
#define MAX_WORD_LENGTH 20
#define MAX_WORDS 100

int main() {
    char word[MAX_WORD_LENGTH];
    char guessed[MAX_WORD_LENGTH];
    int tries = 0;
    int wordLength;
    int i, j;
    char guess;

    // Array nyimpen kata
    char wordList[MAX_WORDS][MAX_WORD_LENGTH];
    int numWords = 0;

    // Baca kata dari file wordlist.txt
    FILE *file = fopen("wordlist.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // baca kata dari file
    while (fgets(wordList[numWords], MAX_WORD_LENGTH, file) != NULL) {
        // Remove trailing newline character
        wordList[numWords][strcspn(wordList[numWords], "\n")] = '\0';
        numWords++;
    }

    fclose(file);

    // Seed number random generator
    srand(time(NULL));
    // milih kata random dari file
    int wordIndex = rand() % numWords;
    strcpy(word, wordList[wordIndex]);
    wordLength = strlen(word);

    // jumlah kata yang bakal ditebak jadi -
    for (i = 0; i < wordLength; i++) {
        guessed[i] = '-';
    }
    guessed[wordLength] = '\0';

    // Game loop
    while (tries < MAX_TRIES) {
        printf("Word: %s\n", guessed);
        printf("Tries left: %d\n", MAX_TRIES - tries);
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        // Cek huruf yang ditebak ada di kata atau ngga
        int found = 0;
        for (i = 0; i < wordLength; i++) {
            if (word[i] == guess) {
                guessed[i] = guess;
                found = 1;
            }
        }

        if (found) {
            printf("Good guess!\n");
        } else {
            printf("Wrong guess!\n");
            tries++;
        }

        // Print hangman kalo salah
        printf("   +---+\n");
        printf("   |   |\n");
        if (tries >= 1) {
            printf("   O   |\n");
        } else {
            printf("       |\n");
        }
        if (tries >= 2) {
            printf("   |   |\n");
        } else {
            printf("       |\n");
        }
        if (tries >= 3) {
            printf("  /    |\n");
        } else {
            printf("       |\n");
        }
        if (tries >= 4) {
            printf("  / \\  |\n");
        } else {
            printf("       |\n");
        }
        printf(" =========\n");

        // Cek kata udah ditebak belom
        if (strcmp(word, guessed) == 0) {
            printf("Congratulations! You guessed the word: %s\n", word);
            break;
        }
    }

    if (tries == MAX_TRIES) {
        printf("Game over! You ran out of tries. The word was: %s\n", word);
    }

    return 0;
}
