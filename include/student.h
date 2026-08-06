#ifndef STUDENT_H
#define STUDENT_H

#define SIZE_NAME 50
#define INITIAL_CAPACITY 10          /* capacite initiale qui sera allouee dynamiquement dans le programme */
#define DATA_FILE "data/students.txt"

typedef struct {
    int id;
    char firstname[SIZE_NAME];
    char lastname[SIZE_NAME];
    float GPA;
} Student;

/* studentList est maintenant un pointer alloue dynamiquemant */
extern Student *studentList;
extern int studentCount;
extern int studentCapacity;
extern int hasUnsavedChanges;

/* liberation de la memoire de la liste */
int initStudentList(int initialCapacity);
void freeStudentList(void);

void addStudent(int id, const char *firstname, const char *lastname, float GPA);

int searchById(int id);

void showAllStudent(void);
void showOneStudent(const Student *e);

int deleteStudent(int id);
int saveOnFile(const char *fileName);
int chargeFromFile(const char *fileName);

#endif
