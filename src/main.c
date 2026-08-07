#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>   // for strcasecmp
#include "../include/student.h"

#define DATA_FILE "data/students.txt"

/* The following functions provide a safe way to read user input and ensure data integrity */

// Reads an integer safely and within the bounds we set.
int readInt(const char *message, int min, int max) {
    char buffer[100];
    long value;
    char *endptr;

    while (1) {
        printf("%s", message);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Read error.\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[0] == '\0') {
            printf("Please enter a value, it cannot be empty.\n");
            continue;
        }

        value = strtol(buffer, &endptr, 10);

        if (*endptr != '\0') {
            printf("Invalid input. Please enter a whole number.\n");
            continue;
        }

        if (value < min || value > max) {
            printf("Value out of range. Please enter a number between %d and %d.\n", min, max);
            continue;
        }

        return (int)value;
    }
}

// Reads a float safely, within bounds.
float readFloat(const char *message, float min, float max) {
    char buffer[100];
    float value;
    char *endptr;

    while (1) {
        printf("%s", message);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Read error.\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[0] == '\0') {
            printf("Please enter a value, it cannot be empty.\n");
            continue;
        }

        value = strtof(buffer, &endptr);

        if (*endptr != '\0') {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (value < min || value > max) {
            printf("Value out of range. Please enter a number between %.2f and %.2f.\n", min, max);
            continue;
        }

        return value;
    }
}

// Reads a non-empty string (firstname/lastname for exemple), with max size
void readString(const char *message, char *dest, int size) {
    while (1) {
        printf("%s", message);

        if (fgets(dest, size, stdin) == NULL) {
            printf("Read error.\n");
            continue;
        }

        // If no \n found, the line was too long: flush the rest of the buffer
        if (strchr(dest, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        } else {
            dest[strcspn(dest, "\n")] = '\0';
        }

        if (dest[0] == '\0') {
            printf("This field cannot be empty.\n");
            continue;
        }

        return;
    }
}

// Asks a yes/no question, returns 1 for yes, 0 for no
int askYesNo(const char *message) {
    char buffer[100];

    while (1) {
        printf("%s (y/n): ", message);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Read error.\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[0] == '\0') {
            printf("Please answer y or n.\n");
            continue;
        }

        if (strcasecmp(buffer, "y") == 0 || strcasecmp(buffer, "yes") == 0) {
            return 1;
        }
        if (strcasecmp(buffer, "n") == 0 || strcasecmp(buffer, "no") == 0) {
            return 0;
        }

        printf("Invalid answer. Please type y or n.\n");
    }
}

/* This is the "UI" of the program, in this function we manage the main menu and user interactions */
int main(void){

    if (!initStudentList(INITIAL_CAPACITY)) {
        return 1;
    }

    chargeFromFile(DATA_FILE);


    /* The user will be presented a menu of differents actions that are available in the program
    * The user can choose an action by entering the corresponding number. The program will then execute the chosen action.
    * The menu will keep appearing until the user chooses to exit the program.
    */
    int choice;
    do{
        printf("\n================STUDENT MANAGER====================\n");
        printf("1. Add student.\n");
        printf("2. Search a student.\n");
        printf("3. Show all the students.\n");
        printf("4. Delete a student.\n");
        printf("5. save.\n");
        printf("0. exit.\n");
        printf("====================================================\n");
        printf("\n");
        choice = readInt("Choose : ", 0, 5);

        switch (choice){
            case 1 :{
                int id = getNextId();
                char lastname[SIZE_NAME], firstname[SIZE_NAME];
                float GPA;

                printf("ID : %d\n", id);
                readString("Firstname: ", firstname, SIZE_NAME);
                readString("Lastname: ", lastname, SIZE_NAME);
                GPA = readFloat("GPA : ", 0.0f, 4.0f);

                addStudent(id, firstname, lastname, GPA);
                break;
            }
            case 2: {
                int id = readInt("Enter student ID: ", 1001, 999999);
                int index = searchById(id);
                if (index != -1) {
                    showOneStudent(&studentList[index]);
                } else {
                    printf("Student not found.\n");
                }
                break;
            }
            case 3:
                showAllStudent();
                break;
            case 4: {
                int id = readInt("Enter student ID: ", 1001, 999999);
                deleteStudent(id);
                break;
            }
            case 5:
                saveOnFile(DATA_FILE);
                break;
            case 0:
                if (hasUnsavedChanges) {
                    if (askYesNo("You have unsaved changes. Do you want to save before exiting?")) {
                        saveOnFile(DATA_FILE);
                    }
                }
                printf("GOODBYE ! See you later.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    freeStudentList();
    return 0;
}