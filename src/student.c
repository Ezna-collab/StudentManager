#include <stdio.h>
#include <string.h>
#include "student.h"

Student studentList[MAX_STUDENTS];
int studentCount = 0;

void addStudent(int id,const char *firstname, const char *lastname, float GPA){
    if(studentCount >= MAX_STUDENTS){
        printf("The list is full (max %d students)\n", MAX_STUDENTS);
        return;
    }
    if (searchById(id) != -1 ){
        printf("A student with ID: %d already exists.\n", id);
        return;
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
    printf("Student '%s %s' 'id: %d' have been added successfully.\n", firstname,lastname,id);
};



int searchById(int id){
    for (int s = 0; s < studentCount; s++){
        if (studentList[s].id == id){
            return s;
        }
        return -1;
    }
};

int searchByName(const char *lastname){
    for (int s = 0; s < studentCount; s++){
        if (strcmp(studentList[s].lastname,lastname)==0){
            return s;
        }
        return -1;
    }
};



void showOneStudent(const Student *e){
    printf("ID:%-5D Firstname:%-15s Lastname:%-15s GPA:%.2F"),
    e->id, e->firstname,e->lastname,e->GPA;
    return;
};



void showAllStudent(void){
    if (studentCount == 0){
        printf("There is no student yet.\n");
        return;
    }
    
    printf("=================STUDENTS LIST================\n");
    for (int s=0; s < studentCount; s++){
        showOneStudent(&studentList[s]);
        return;
    }
}




int deleteStudent(int id){
    int index = searchById(id);

    if (index == -1){
        printf("No Student with Id:%d\n", id);
        return 0;
    }

    for (int s = index; s < studentCount-1; s++){
        studentList[s] = studentList[s-1];
    }
    studentCount--;
    printf("Student with id:%d have been deleted successfully\n",id);
    return 1;
};


int saveOnFile(const char *fileName){
    FILE *f = fopen(fileName, "w");
    if (f == NULL){
        printf("Connot open %s as writing\n", fileName);
        return 0;
    }
    fprintf(f, "%d\n",studentCount);
    for ( int i = 0; i < studentCount; i++){
        fprintf(f,"%d;%s;%s;%.2f\n",
            studentList[i].id,
            studentList[i].firstname,
            studentList[i].lastname,
            studentList[i].GPA);
    }
    fclose(f);
    printf("%d student(s) saved on %s ");
    
};



int chargeFromFile(const char *fileName){

};