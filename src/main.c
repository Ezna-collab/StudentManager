#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/student.h"

int main(void) {
    /* Allocation dinamique de la liste des etudiants */
    if (!initStudentList(INITIAL_CAPACITY)) {
        return 1;
    }

    chargeFromFile(DATA_FILE);

    int choix;
    do {
        printf("\n================================\n");
        printf(" Gestion des Etudiants\n");
        printf("================================\n");
        printf(" 1. Ajouter un etudiant\n");
        printf(" 2. Rechercher un etudiant\n");
        printf(" 3. Afficher tous les etudiants\n");
        printf(" 4. Supprimer un etudiant\n");
        printf(" 5. Sauvegarder\n");
        printf(" 6. Quitter\n");
        printf("================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                int id;
                char firstname[SIZE_NAME];
                char lastname[SIZE_NAME];
                float gpa;
                printf("ID : "); scanf("%d", &id);
                printf("Prenom : "); scanf("%49s", firstname);
                printf("Nom : "); scanf("%49s", lastname);
                printf("GPA : "); scanf("%f", &gpa);
                addStudent(id, firstname, lastname, gpa);
                break;
            }
            case 2: {
                int id;
                printf("ID a rechercher : "); scanf("%d", &id);
                int idx = searchById(id);
                if (idx >= 0) {
                    showOneStudent(&studentList[idx]);
                } else {
                    printf("Etudiant introuvable.\n");
                }
                break;
            }
            case 3:
                showAllStudent();
                break;
            case 4: {
                int id;
                printf("ID a supprimer : "); scanf("%d", &id);
                deleteStudent(id);
                break;
            }
            case 5:
                saveOnFile(DATA_FILE);
                break;
            case 6:
                if (hasUnsavedChanges) {
                    char rep;
                    printf("Modifications non sauvegardees. Sauvegarder avant de quitter ? (o/n) : ");
                    scanf(" %c", &rep);
                    if (rep == 'o' || rep == 'O') {
                        saveOnFile(DATA_FILE);
                    }
                }
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 6);

    /* Liberation de la memoire allouee dynamiquemant */
    freeStudentList();
    return 0;
}
