#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTIONS 10
#define MAX_SUBJECTS 3
#define MAX_DIFFICULTY 3  // Easy, Medium, Hard

typedef struct {
    char question[256];
    char options[4][100];
    int answer;
} Question;

typedef struct {
    char name[50];
    int score;
} UserScore;

Question subjects[MAX_SUBJECTS][MAX_DIFFICULTY][MAX_QUESTIONS];
UserScore userScores[10];
int userCount = 0;
char currentUserName[50];  // Store current player's name

void saveScoresToFile() {
    FILE *file = fopen("scores.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < userCount; i++) {
            fprintf(file, "%s %d\n", userScores[i].name, userScores[i].score);
        }
        fclose(file);
    } else {
        printf("Error saving scores.\n");
    }
}

void loadScoresFromFile() {
    FILE *file = fopen("scores.txt", "r");
    if (file != NULL) {
        userCount = 0;
        while (fscanf(file, "%s %d", userScores[userCount].name, &userScores[userCount].score) == 2) {
            userCount++;
        }
        fclose(file);
    }
}

void loadQuestionsFromFile() {
    FILE *file = fopen("questions.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open questions file.\n");
        return;
    }

    int subjectIndex, difficultyIndex, questionIndex[MAX_SUBJECTS][MAX_DIFFICULTY] = {0};
    char question[256], option1[100], option2[100], option3[100], option4[100];
    int answer;

    while (fscanf(file, "%d,%d,%255[^,],%99[^,],%99[^,],%99[^,],%99[^,],%d\n",
                  &subjectIndex, &difficultyIndex, question, option1, option2, option3, option4, &answer) == 8) {
        int qIdx = questionIndex[subjectIndex - 1][difficultyIndex - 1]++;
        strcpy(subjects[subjectIndex - 1][difficultyIndex - 1][qIdx].question, question);
        strcpy(subjects[subjectIndex - 1][difficultyIndex - 1][qIdx].options[0], option1);
        strcpy(subjects[subjectIndex - 1][difficultyIndex - 1][qIdx].options[1], option2);
        strcpy(subjects[subjectIndex - 1][difficultyIndex - 1][qIdx].options[2], option3);
        strcpy(subjects[subjectIndex - 1][difficultyIndex - 1][qIdx].options[3], option4);
        subjects[subjectIndex - 1][difficultyIndex - 1][qIdx].answer = answer - 1;
    }

    fclose(file);
}

void playQuiz(int subjectIndex, int difficultyIndex) {
    int score = 0, userAnswer;

    for (int i = 0; i < MAX_QUESTIONS; i++) {
        printf("\nQuestion %d: %s\n", i + 1, subjects[subjectIndex][difficultyIndex][i].question);
        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, subjects[subjectIndex][difficultyIndex][i].options[j]);
        }
        printf("Your answer (1-4): ");
        if (scanf("%d", &userAnswer) != 1 || userAnswer < 1 || userAnswer > 4) {
            printf("Invalid input. Please enter a number between 1 and 4.\n");
            while (getchar() != '\n');  // clear input buffer
            i--;  // ask the question again
            continue;
        }
        if (userAnswer - 1 == subjects[subjectIndex][difficultyIndex][i].answer) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong! The correct answer was: %s\n", subjects[subjectIndex][difficultyIndex][i].options[subjects[subjectIndex][difficultyIndex][i].answer]);
        }
    }

    printf("\nYour score: %d/%d\n", score, MAX_QUESTIONS);

    // Save the score with the user's name
    strcpy(userScores[userCount].name, currentUserName);
    userScores[userCount].score = score;
    userCount++;
    saveScoresToFile();
}

void viewScores() {
    int found = 0;
    printf("\n%s's Scores:\n", currentUserName);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userScores[i].name, currentUserName) == 0) {
            printf("Score: %d\n", userScores[i].score);
            found = 1;
        }
    }
    if (!found) {
        printf("No scores found for %s.\n", currentUserName);
    }
}

int main() {
    int choice;

    loadQuestionsFromFile();
    loadScoresFromFile();

    printf("Enter your name: ");
    scanf("%s", currentUserName);

    do {
        printf("\nWelcome to the Quiz Game, %s!\n", currentUserName);
        printf("1. Play Quiz\n");
        printf("2. View Scores\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid option.\n");
            while (getchar() != '\n');  // clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                printf("\nSelect a subject:\n");
                printf("1. Math\n2. Science\n3. History\n");
                int subjectChoice;
                if (scanf("%d", &subjectChoice) != 1 || subjectChoice < 1 || subjectChoice > MAX_SUBJECTS) {
                    printf("Invalid subject choice. Please try again.\n");
                    while (getchar() != '\n');  // clear input buffer
                    break;
                }

                printf("\nSelect a difficulty level:\n");
                printf("1. Easy\n2. Medium\n3. Hard\n");
                int difficultyChoice;
                if (scanf("%d", &difficultyChoice) != 1 || difficultyChoice < 1 || difficultyChoice > MAX_DIFFICULTY) {
                    printf("Invalid difficulty choice. Please try again.\n");
                    while (getchar() != '\n');  // clear input buffer
                    break;
                }

                playQuiz(subjectChoice - 1, difficultyChoice - 1);
                break;
            case 2:
                viewScores();
                break;
            case 3:
                printf("Exiting the game. Thank you for playing, %s!\n", currentUserName);
                break;
            default:
                printf("Invalid option. Please choose again.\n");
        }
    } while (choice != 3);

    return 0;
}