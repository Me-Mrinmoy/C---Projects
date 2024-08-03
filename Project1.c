// This is a simple number guess game between you and computer--

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Initialize the random number generator with the current time as the seed
    srand(time(0));

    // Generate a random number between 1 and 100
    int random_number = (rand() % 100) + 1;
    int no_of_guesses = 0;
    int guesses;

    // Print the random number
    // printf("Random number between 1 and 100: %d\n", random_number);

    do
    {
        printf("Guess the number");
        scanf("%d", &guesses);
        if (guesses > random_number)
        {
            printf("Enter a lower number:");
        }
        else if (guesses<random_number)
        {
            printf("Enter a higher number:");
        }
        no_of_guesses++;
    } while (guesses != random_number);

    printf("You guessed the number is %d guesses", no_of_guesses);

    return 0;
}
