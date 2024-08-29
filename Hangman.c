//This is a simple word guess project in C.The program will select a word randomly from a predefined list, and the player will have a limited number of attempts to guess the word by entering letters one at a time.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ATTEMPTS 6
#define WORD_LIST_SIZE 5

// List of words to choose from
const char *wordList[WORD_LIST_SIZE] = {"computer", "programming", "hangman", "algorithm", "network"};

// Function to pick a random word from the word list
const char *chooseWord() {
    srand(time(0));
    return wordList[rand() % WORD_LIST_SIZE];
}

// Function to display the current state of the word being guessed
void displayWord(char *guessedWord, int wordLength) {
    for (int i = 0; i < wordLength; i++) {
        printf("%c ", guessedWord[i]);
    }
    printf("\n");
}

// Function to check if the player has guessed the word
int isWordGuessed(char *guessedWord, int wordLength) {
    for (int i = 0; i < wordLength; i++) {
        if (guessedWord[i] == '_') {
            return 0;
        }
    }
    return 1;
}

// Main function to run the Hangman game
int main() {
    const char *word = chooseWord();
    int wordLength = strlen(word);
    char guessedWord[wordLength];
    int attemptsLeft = MAX_ATTEMPTS;
    int alreadyGuessed[26] = {0};  // Track guessed letters (26 letters in the alphabet)

    // Initialize the guessed word with underscores
    for (int i = 0; i < wordLength; i++) {
        guessedWord[i] = '_';
    }

    printf("Welcome to Hangman!\n");

    while (attemptsLeft > 0) {
        printf("\nAttempts remaining: %d\n", attemptsLeft);
        displayWord(guessedWord, wordLength);

        printf("Guess a letter: ");
        char guess;
        scanf(" %c", &guess);

        // Convert guess to lowercase
        guess = tolower(guess);

        // Check if the letter has already been guessed
        if (alreadyGuessed[guess - 'a']) {
            printf("You already guessed that letter!\n");
            continue;
        }
        alreadyGuessed[guess - 'a'] = 1;

        // Check if the guessed letter is in the word
        int correctGuess = 0;
        for (int i = 0; i < wordLength; i++) {
            if (word[i] == guess) {
                guessedWord[i] = guess;
                correctGuess = 1;
            }
        }

        if (!correctGuess) {
            attemptsLeft--;
            printf("Incorrect guess! The letter '%c' is not in the word.\n", guess);
        }

        // Check if the word has been completely guessed
        if (isWordGuessed(guessedWord, wordLength)) {
            printf("\nCongratulations! You've guessed the word: %s\n", word);
            break;
        }
    }

    if (attemptsLeft == 0) {
        printf("\nGame Over! You've run out of attempts. The word was: %s\n", word);
    }

    return 0;
}