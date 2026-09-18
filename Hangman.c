#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TRIES 6
#define MAX_WORDS 15
#define MAX_GUESSED 26

/* ---------- DATA STRUCTURE ---------- */

typedef struct {
    const char *word;
    const char *hint;
} Word;

/* ---------- TECHNOLOGY WORDS ---------- */

Word technology[] = {
    {"PROGRAMMING", "Writing instructions that tell a computer what to do."},
    {"COMPUTER", "An electronic machine that processes information."},
    {"ALGORITHM", "A step-by-step procedure used to solve a problem."},
    {"DATABASE", "An organized collection of structured information."},
    {"NETWORK", "A group of connected computers that communicate with each other."},
    {"SOFTWARE", "Programs and instructions that run on a computer."},
    {"HARDWARE", "The physical components of a computer system."},
    {"JAVASCRIPT", "A popular programming language widely used for web development."},
    {"PYTHON", "A popular high-level programming language known for simplicity."},
    {"CYBERSECURITY", "The practice of protecting systems and data from digital attacks."},
    {"ARTIFICIAL", "Relating to something created by humans rather than occurring naturally."},
    {"ENCRYPTION", "The process of converting data into a secure, unreadable format."},
    {"INTERNET", "A global network connecting millions of computers."},
    {"ROBOTICS", "The field involving the design and development of robots."},
    {"CLOUD", "Technology that provides computing resources over the internet."}
};

/* ---------- SCIENCE WORDS ---------- */

Word science[] = {
    {"PHYSICS", "The study of matter, energy, motion and forces."},
    {"CHEMISTRY", "The study of substances and how they interact."},
    {"BIOLOGY", "The study of living organisms."},
    {"ASTRONOMY", "The study of stars, planets and objects in space."},
    {"GEOLOGY", "The study of Earth's structure and history."},
    {"GRAVITY", "The force that attracts objects toward one another."},
    {"MOLECULE", "A group of atoms bonded together."},
    {"ELECTRICITY", "The flow of electric charge."},
    {"EVOLUTION", "The process through which living organisms change over generations."},
    {"ECOSYSTEM", "A community of organisms interacting with their environment."},
    {"GENETICS", "The study of genes and heredity."},
    {"NEURON", "A specialized cell that transmits nerve signals."},
    {"VACCINE", "A biological preparation that helps develop immunity."},
    {"VOLCANO", "An opening in Earth's crust through which lava may erupt."},
    {"PHOTOSYNTHESIS", "The process plants use to convert light energy into chemical energy."}
};

/* ---------- SPORTS WORDS ---------- */

Word sports[] = {
    {"FOOTBALL", "A popular team sport played with a spherical ball."},
    {"CRICKET", "A bat-and-ball sport especially popular in India."},
    {"BASKETBALL", "A sport where players score by shooting a ball through a hoop."},
    {"TENNIS", "A racquet sport played using a ball over a net."},
    {"HOCKEY", "A sport played with a stick and a ball or puck."},
    {"BADMINTON", "A racquet sport played with a shuttlecock."},
    {"VOLLEYBALL", "A team sport where players hit a ball over a net."},
    {"SWIMMING", "A competitive sport performed in water."},
    {"ATHLETICS", "Sports involving running, jumping and throwing events."},
    {"BOXING", "A combat sport involving punches between two competitors."},
    {"WRESTLING", "A combat sport involving grappling and physical control."},
    {"CYCLING", "A sport involving competitive riding of bicycles."},
    {"BASEBALL", "A bat-and-ball game involving bases and runs."},
    {"ARCHERY", "A sport involving shooting arrows at a target."},
    {"GYMNASTICS", "A sport involving strength, flexibility, balance and coordination."}
};

/* ---------- FUNCTION DECLARATIONS ---------- */

void showTitle();
void showMainMenu();
int chooseCategory();
Word *getCategory(int category);
void clearScreen();
void drawHangman(int tries);
void displayWord(const char word[], const int revealed[]);
void displayGuessedLetters(const char guessed[], int count);
int isAlreadyGuessed(const char guessed[], int count, char letter);
int checkWin(const char word[], const int revealed[]);
int playRound(int category, int *score);
void showFinalStats(int score, int wins, int losses, int bestStreak);
char getPlayAgain();
void clearInputBuffer();

/* ========================================================= */
/*                         MAIN                              */
/* ========================================================= */

int main() {

    int score = 0;
    int wins = 0;
    int losses = 0;
    int currentStreak = 0;
    int bestStreak = 0;
    int choice;

    srand((unsigned int)time(NULL));

    while (1) {

        clearScreen();
        showTitle();
        showMainMenu();

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("\nInvalid input! Please enter a number.\n");
            printf("Press ENTER to continue...");
            getchar();
            continue;
        }

        clearInputBuffer();

        if (choice == 4) {
            break;
        }

        if (choice < 1 || choice > 4) {
            printf("\nInvalid choice! Please select 1-4.\n");
            printf("Press ENTER to continue...");
            getchar();
            continue;
        }

        int result = playRound(choice, &score);

        if (result == 1) {
            wins++;
            currentStreak++;

            if (currentStreak > bestStreak) {
                bestStreak = currentStreak;
            }
        }
        else {
            losses++;
            currentStreak = 0;
        }

        printf("\n----------------------------------------\n");
        printf("Current Score : %d\n", score);
        printf("Wins          : %d\n", wins);
        printf("Losses        : %d\n", losses);
        printf("Current Streak: %d\n", currentStreak);
        printf("----------------------------------------\n");

        printf("\nPress ENTER to return to the main menu...");
        getchar();
    }

    clearScreen();

    showTitle();

    showFinalStats(score, wins, losses, bestStreak);

    printf("\nThank you for playing Hangman!\n");
    printf("Keep guessing and keep improving!\n\n");

    return 0;
}

/* ========================================================= */
/*                     TITLE SCREEN                          */
/* ========================================================= */

void showTitle() {

    printf("\n");
    printf("============================================================\n");
    printf("                     HANGMAN GAME                           \n");
    printf("============================================================\n");
    printf("              Guess the word. Save the man!                 \n");
    printf("============================================================\n");
}

/* ========================================================= */
/*                     MAIN MENU                             */
/* ========================================================= */

void showMainMenu() {

    printf("\n");
    printf("                    MAIN MENU                              \n");
    printf("------------------------------------------------------------\n");
    printf("  1. Technology\n");
    printf("  2. Science\n");
    printf("  3. Sports\n");
    printf("  4. Exit Game\n");
    printf("------------------------------------------------------------\n");
}

/* ========================================================= */
/*                    CATEGORY                              */
/* ========================================================= */

int chooseCategory() {

    int choice;

    printf("\nChoose a category:\n");
    printf("  1. Technology\n");
    printf("  2. Science\n");
    printf("  3. Sports\n");
    printf("\nEnter choice: ");

    if (scanf("%d", &choice) != 1) {
        clearInputBuffer();
        return 0;
    }

    clearInputBuffer();

    return choice;
}

/* ========================================================= */
/*                    GET CATEGORY                           */
/* ========================================================= */

Word *getCategory(int category) {

    if (category == 1)
        return technology;

    if (category == 2)
        return science;

    if (category == 3)
        return sports;

    return NULL;
}

/* ========================================================= */
/*                    GAME ROUND                             */
/* ========================================================= */

int playRound(int category, int *score) {

    Word *selectedCategory;
    int randomIndex;

    selectedCategory = getCategory(category);

    if (selectedCategory == NULL) {
        printf("\nInvalid category!\n");
        return 0;
    }

    randomIndex = rand() % MAX_WORDS;

    const char *word = selectedCategory[randomIndex].word;
    const char *hint = selectedCategory[randomIndex].hint;

    int length = strlen(word);

    int revealed[length];

    char guessed[MAX_GUESSED];
    int guessedCount = 0;

    int tries = 0;
    char guess;

    for (int i = 0; i < length; i++) {
        revealed[i] = 0;
    }

    while (tries < MAX_TRIES) {

        clearScreen();

        showTitle();

        printf("\nCategory: ");

        if (category == 1)
            printf("TECHNOLOGY");
        else if (category == 2)
            printf("SCIENCE");
        else
            printf("SPORTS");

        printf("\n");
        printf("------------------------------------------------------------\n");

        drawHangman(tries);

        printf("\nHint: %s\n", hint);

        printf("\nWord: ");
        displayWord(word, revealed);

        printf("\nTries Remaining: %d / %d\n",
               MAX_TRIES - tries,
               MAX_TRIES);

        displayGuessedLetters(guessed, guessedCount);

        printf("\nEnter a letter: ");

        if (scanf(" %c", &guess) != 1) {
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        guess = toupper((unsigned char)guess);

        /* Check alphabet */

        if (!isalpha((unsigned char)guess)) {

            printf("\nPlease enter a valid alphabet letter.\n");
            printf("Press ENTER to continue...");
            getchar();

            continue;
        }

        /* Check duplicate */

        if (isAlreadyGuessed(guessed, guessedCount, guess)) {

            printf("\nYou already guessed '%c'!\n", guess);
            printf("Try a different letter.\n");
            printf("Press ENTER to continue...");
            getchar();

            continue;
        }

        guessed[guessedCount++] = guess;

        int found = 0;

        for (int i = 0; i < length; i++) {

            if (word[i] == guess) {
                revealed[i] = 1;
                found = 1;
            }
        }

        if (found) {

            printf("\nCorrect! '%c' is in the word.\n", guess);

            *score += 10;

            if (checkWin(word, revealed)) {

                clearScreen();

                showTitle();

                printf("\n");
                printf("============================================================\n");
                printf("                    YOU WON!                               \n");
                printf("============================================================\n");

                drawHangman(tries);

                printf("\nThe word was: %s\n", word);
                printf("You earned 10 points for this guess!\n");

                *score += 50;

                printf("Bonus: +50 points for solving the word!\n");

                printf("\nTotal Score: %d\n", *score);

                return 1;
            }

        }
        else {

            tries++;

            printf("\nWrong guess! '%c' is not in the word.\n", guess);
        }

        printf("\nPress ENTER to continue...");
        getchar();
    }

    clearScreen();

    showTitle();

    printf("\n");
    printf("============================================================\n");
    printf("                    GAME OVER                              \n");
    printf("============================================================\n");

    drawHangman(MAX_TRIES);

    printf("\nYou ran out of tries.\n");
    printf("The correct word was: %s\n", word);

    return 0;
}

/* ========================================================= */
/*                     DISPLAY WORD                          */
/* ========================================================= */

void displayWord(const char word[], const int revealed[]) {

    for (int i = 0; word[i] != '\0'; i++) {

        if (revealed[i])
            printf("%c ", word[i]);
        else
            printf("_ ");
    }

    printf("\n");
}

/* ========================================================= */
/*                 DISPLAY GUESSED LETTERS                   */
/* ========================================================= */

void displayGuessedLetters(const char guessed[], int count) {

    printf("\nGuessed Letters: ");

    if (count == 0) {
        printf("None");
    }
    else {

        for (int i = 0; i < count; i++) {
            printf("%c ", guessed[i]);
        }
    }

    printf("\n");
}

/* ========================================================= */
/*                CHECK DUPLICATE GUESS                      */
/* ========================================================= */

int isAlreadyGuessed(const char guessed[], int count, char letter) {

    for (int i = 0; i < count; i++) {

        if (guessed[i] == letter)
            return 1;
    }

    return 0;
}

/* ========================================================= */
/*                     CHECK WIN                             */
/* ========================================================= */

int checkWin(const char word[], const int revealed[]) {

    for (int i = 0; word[i] != '\0'; i++) {

        if (!revealed[i])
            return 0;
    }

    return 1;
}

/* ========================================================= */
/*                  HANGMAN DRAWING                         */
/* ========================================================= */

void drawHangman(int tries) {

    printf("\n");

    switch (tries) {

        case 0:

            printf("  +---+\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");

            break;

        case 1:

            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");

            break;

        case 2:

            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("=========\n");

            break;

        case 3:

            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|   |\n");
            printf("      |\n");
            printf("=========\n");

            break;

        case 4:

            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf("      |\n");
            printf("=========\n");

            break;

        case 5:

            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" /    |\n");
            printf("=========\n");

            break;

        case 6:

            printf("  +---+\n");
            printf("  |   |\n");
            printf("  X   |\n");
            printf(" /|\\  |\n");
            printf(" / \\  |\n");
            printf("=========\n");

            break;
    }
}

/* ========================================================= */
/*                    FINAL STATISTICS                       */
/* ========================================================= */

void showFinalStats(int score, int wins, int losses, int bestStreak) {

    printf("\n============================================================\n");
    printf("                     FINAL STATS                            \n");
    printf("============================================================\n");

    printf("\nTotal Score : %d\n", score);
    printf("Wins        : %d\n", wins);
    printf("Losses      : %d\n", losses);
    printf("Best Streak : %d\n", bestStreak);

    if (wins + losses > 0) {

        double winRate =
            ((double)wins / (wins + losses)) * 100;

        printf("Win Rate    : %.1f%%\n", winRate);
    }

    printf("\n============================================================\n");
}

/* ========================================================= */
/*                   CLEAR SCREEN                            */
/* ========================================================= */

void clearScreen() {

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* ========================================================= */
/*                CLEAR INPUT BUFFER                         */
/* ========================================================= */

void clearInputBuffer() {

    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}