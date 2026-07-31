#ifndef STUDENT_H
#define STUDENT_H


#define MAX_STUDENTS 100
#define SIZE_NAME 50
#define DATA_FILE "students.txt"


typedef struct {
    int id;
    char firstname[SIZE_NAME];
    char lastname[SIZE_NAME];
    float GPA;
} Student;

extern Student studentList[MAX_STUDENTS];
extern int studentCount;


void addStudent(int id, const char *firstname, const char *lastname, float GPA);


int searchByNAme(const char *lastname);
int searchById(int id);

void showAllStudent(void);
void showOneStudent(const Student *e);


int deleteStudent(int id);
int saveOnFile(const char *fileName);
int chargeFromFile(const char *fileName);

#endif