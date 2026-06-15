#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void addStudent();
void deleteStudent();
void displayStudent();
void updateStudent();
void searchStudent();
struct Student{
    char name[50];
    char address[40];
    int id;
    float marks[5];
    float total;
    float percentage;
    char subject[5];
};
int main()
{
    int choice=0;
    nepal:
    printf("\n====Student Record Management System====\n");
    printf("1.Add student\n");
    printf("2.Delete student\n");
    printf("3.Display all student\n");
    printf("4.Update student\n");
    printf("5.Search student\n");
    printf("6.Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);
     if(choice<1||choice>6)
    {
        printf("\n Wrong choice");
        goto nepal;
    }
    else
    {
    switch(choice)
    {
      case 1:
      addStudent();
      break;
      case 2:
      deleteStudent();
      break;
      case 3:
      displayStudent();
      break;
      case 4:
      updateStudent();
      break;
      case 5:
      searchStudent();
      break;
      case 6:
      exit(0);
      return 0;
    }
}
}
  void addStudent()
    { 
    
        struct student s;
        s.total=0;
        int i=0;
        FILE*p;
        p=fopen("student.txt","a");
        if(p==NULL)
        {
            printf("\n Sorry file not found");
            exit(0);
        }
        printf("\n===Add Student Information===\n");
        printf("\n Enter name of student:");
        gets(s.name);
        fflush(stdin);
        printf("\n Enter address:");
        gets(s.address);
        fflush(stdin);
        printf("\n Enter id :");
        scanf("%d",&s.id);
        fflush(stdin);
        printf("\n Marks\n");
        for(i=0;i<5;i++)
        {
           printf("\n Enter subject name:");
           gets(s[i].subject);
           fflush(stdin);
           printf("\n Enter marks:");
           scanf("%f",&s.marks[i]);
           s.total=s.total+s.marks[i];
        }
        s.percentage=s.total/5;
        printf("\n Total Percentage : %f/n",s.percentage);
        fflush(stdin);
        fwrite(&s,sizeof(s),1,p);
        fclose(p);
  
    }
