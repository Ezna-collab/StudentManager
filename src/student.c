#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/student.h"

Student *studentList = NULL;
int studentCapacity = 0;
int studentCount = 0;
int hasUnsavedChanges = 0;

/** initialization of the student list with a given initial capacity. Returns 1 on success, 0 on failure. 
 * using malloc to allocate memory for the student list for a better management of the memory. If the allocation fails, an error message is printed and 0 is returned.
 * If the allocation is successful, the studentCapacity is set to the initial capacity, studentCount is set to 0, and 1 is returned to indicate success.
*/
int initStudentList(int initialCapacity) {
    if (initialCapacity <= 0) {
        initialCapacity = INITIAL_CAPACITY;
    }

    studentList = malloc((size_t)initialCapacity * sizeof(Student));
    if (studentList == NULL) {
        printf("Erreur : allocation memoire impossible.\n");
        return 0;
    }

    studentCapacity = initialCapacity;
    studentCount = 0;
    return 1;
}


/** fonction to clear the student list when needed */
void freeStudentList(void) {
    free(studentList);
    studentList = NULL;
    studentCount = 0;
    studentCapacity = 0;
}

/** Ensure the student list has enough capacity for the specified number of students */
static int ensureCapacity(int necessary) {
    if (necessary <= studentCapacity) {
        return 1;
    }

    int newCapacity = (studentCapacity == 0) ? INITIAL_CAPACITY : studentCapacity * 2;
    while (newCapacity < necessary) {
        newCapacity *= 2; /* if the capacity exceeds the inital limit, it will be doubled */
    }

    Student *tmp = realloc(studentList, (size_t)newCapacity * sizeof(Student));
    if (tmp == NULL) {
        printf("Erreur : impossible d'agrandir la liste (memoire insuffisante).\n");
        return 0;
    }

    studentList = tmp;
    studentCapacity = newCapacity;
    return 1;
}


/** Setting automatically the ID for a new student
 * Remark: The initial ID is set to 1001 if the list is empty, otherwise it is set to the maximum existing ID + 1. 
 * This ensures that each student has a unique ID.
 */
int getNextId(void) {
    if (studentCount == 0) {
        return 1001;
    }
    int maxId = studentList[0].id;
    for (int i = 1; i < studentCount; i++) {
        if (studentList[i].id > maxId) {
            maxId = studentList[i].id;
        }
    }
    return maxId + 1;
}

/** Add a new student to the list */
void addStudent(int id,const char *firstname, const char *lastname, float GPA){

    if (!ensureCapacity(studentCount + 1)) {
        return; /* No extra memory */
    }


    Student new_student;
    new_student.id = id;
    strncpy (new_student.firstname,firstname,SIZE_NAME -1);
    new_student.firstname[SIZE_NAME -1] = '\0';
    strncpy (new_student.lastname,lastname,SIZE_NAME -1);
    new_student.lastname[SIZE_NAME -1] = '\0';
    new_student.GPA = GPA;
    

    studentList[studentCount] = new_student;
    studentCount++;
    hasUnsavedChanges = 1;
    printf("Student '%s %s' is added successfully.\n", firstname,lastname);
};



/** Search for a student by their ID */
int searchById(int id){
    for (int s = 0; s < studentCount; s++){
        if (studentList[s].id == id){
            return s;
        }
    }
    return -1;   
};


void showOneStudent(const Student *e){
    printf("ID:%-5d Firstname:%-15s Lastname:%-15s GPA:%.2f\n",
    e->id, e->firstname,e->lastname,e->GPA);
    return;
};


/** Display all students that are currently in the list */
void showAllStudent(void){
    if (studentCount == 0){
        printf("There is no student yet.\n");
        return;
    }
    
    printf("=================STUDENTS LIST================\n");
    for (int s=0; s < studentCount; s++){
        showOneStudent(&studentList[s]);
    }
    printf("----------------------------------------------\n");
    return;
    }


/** Delete a student and his/her information by their ID */
int deleteStudent(int id){
    int index = searchById(id);

    if (index == -1){
        printf("No Student with Id:%d\n", id);
        return 0;
    }

    for (int s = index; s < studentCount-1; s++){
        studentList[s] = studentList[s+1];
    }
    studentCount--;
    hasUnsavedChanges = 1;
    printf("Student with the id:%d have been deleted successfully\n",id);
    return 1;
};

/** Save the student list to the file "students.txt"*/
int saveOnFile(const char *filePath){
    FILE *f = fopen(filePath, "w");
    if (f == NULL){
        printf("Cannot open %s as writing\n", filePath);
        return 0;
    }
    fprintf(f, "%d - students\n",studentCount);
    for ( int i = 0; i < studentCount; i++){
        fprintf(f,"%d;%s;%s;%.2f\n",
            studentList[i].id,
            studentList[i].firstname,
            studentList[i].lastname,
            studentList[i].GPA);
    }
    fclose(f);
    hasUnsavedChanges = 0;
    printf("%d student(s) has/have been saved on %s\n ",studentCount, filePath);
    return 1;
}


/** Load the student list from the file "students.txt" */
int chargeFromFile(const char *fileName){
    FILE *f = fopen(fileName,"r");
    if(f==NULL){
        printf("no file %s has been found.\n", fileName);
        return 0;
    }
    int nb;
    if (fscanf(f,"%d - students\n",&nb)!=1){
        fclose(f);
        return 0;
    }

    if (!ensureCapacity(nb)) {
        fclose(f);
        return 0;
    }

    studentCount = 0;
    for (int i = 0; i < nb; i++) {
        Student e;
        if (fscanf(f, "%d;%49[^;];%49[^;];%f\n", &e.id, e.firstname, e.lastname, &e.GPA) == 4) {
            if (!ensureCapacity(studentCount + 1)) {
                break; /* No extra memory */
            }
            studentList[studentCount] = e;
            studentCount++;
        }
    }
    fclose(f);
    printf("%d student(s) has/have been charged from file '%s'\n", studentCount, fileName);
    return 1;
}