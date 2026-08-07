#ifndef STUDENT_H
#define STUDENT_H


#define INITIAL_CAPACITY 10
#define SIZE_NAME 50
#define DATA_FILE "data/students.txt"


typedef struct {
    int id;
    char firstname[SIZE_NAME];
    char lastname[SIZE_NAME];
    float GPA;
} Student;

extern Student *studentList;
extern int studentCapacity;
extern int studentCount;
extern int hasUnsavedChanges;

int initStudentList(int initialCapacity);
void freeStudentList(void);
void addStudent(int id, const char *firstname, const char *lastname, float GPA);
int getNextId(void);

int searchById(int id);

void showAllStudent(void);
void showOneStudent(const Student *e);


int deleteStudent(int id);
int saveOnFile(const char *fileName);
int chargeFromFile(const char *fileName);

#endif