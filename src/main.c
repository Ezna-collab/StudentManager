#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "../include/student.h"


#define DATA_FILE "data/students.txt"

void Buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void){
    chargeFromFile(DATA_FILE);

    int choice;
    do{
        printf("\n================STUDENT MANAGER===================\n");
        printf("1. Add student.\n");
        printf("2.Search a student.\n");
        printf("3.Show all the students.\n");
        printf("4.Delete a student.\n");
        printf("5.save.\n");
        printf("0.exit.\n");
        printf("Choose : ");
        scanf("%d", &choice);
        Buffer();


        switch (choice){
            case 1 :{
                int id;
                char lastname[SIZE_NAME],firstname[SIZE_NAME];
                float GPA;

                printf("ID : ");
                scanf("%d", &id);
                //viderBuffer();
                printf("Lastname: ");
                fgets(lastname, SIZE_NAME, stdin);
                lastname[strcspn(lastname, "\n")] = '\0';
                printf("Firstname: ");
                fgets(firstname, SIZE_NAME, stdin);
                firstname[strcspn(firstname, "\n")] = '\0';
                printf("GPA : ");
                scanf("%f", &GPA);
                Buffer();
 
                addStudent(id, lastname, firstname, GPA);
                break;
            }
            case 2: {
                int id;
                printf("Enter student ID: ");
                scanf("%d", &id);
                Buffer();
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
                int id;
                printf("Enter student ID: ");
                scanf("%d", &id);
                Buffer();
                deleteStudent(id);
                break;
            }
            case 5:
                saveOnFile(DATA_FILE);
                break;
             case 0:
                printf("Save before leaving...\n");
                sauvegarderDansFichier(DATA_FILE);
                printf("GOODBYE !\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}

