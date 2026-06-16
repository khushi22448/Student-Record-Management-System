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
    char subject[5][30];
};
int main()
{
    int choice=0;
    while(1)
    {
    printf("\n\t\t\t====Student Record Management System====\n");
    printf("\n\t\t\t1.Add student");
    printf("\n\t\t\t2.Delete student");
    printf("\n\t\t\t3.Display all student");
    printf("\n\t\t\t4.Update student");
    printf("\n\t\t\t5.Search student");
    printf("\n\t\t\t6.Exit\n");
    printf("\t\t\tEnter your choice: ");
    scanf("%d",&choice);
     if(choice<1||choice>6)
    {
        printf("\n Wrong choice");
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
      break;*/
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
    
    }
 }
}
return 0;
}
  void addStudent()
    { 
    
        struct Student s;
        s.total=0;
        int i=0;
        char confirm=0;
        FILE*p;
        p=fopen("student.txt","wb");
        if(p==NULL)
        {
            printf("\n Sorry file not found");
            exit(0);
        }
        do
        {
        printf("\n\t\t\t===Add Student Information===\n");
        fflush(stdin);
        printf("\n\t\t\tEnter name of student:");
        gets(s.name);
        fflush(stdin);
        printf("\n\t\t\tEnter address:");
        gets(s.address);
        fflush(stdin);
        printf("\n\t\t\tEnter id :");
        scanf("%d",&s.id);
        fflush(stdin);
        printf("\n\t\t\tMarks\n");
        for(i=0;i<5;i++)
        {
           fflush(stdin);
		   printf("\n\t\t\tEnter Subject name:");
           gets(s.subject[i]);
           fflush(stdin);
           printf("\n\t\t\t Enter marks:");
           scanf("%f",&s.marks[i]);
           s.total=s.total+s.marks[i];
        }
        s.percentage=s.total/5;
        printf("\n\t\t\tTotal Percentage : %f",s.percentage);
        printf("\n\t\t\t**Record Added Succesfully**");
        fflush(stdin);
         fwrite(&s,sizeof(s),1,p);
        printf("\n\t\t\tAdd more students(y/n)?");
        scanf(" %c",&confirm);
        printf("\n\t\t\t----------------------------------------");
        fflush(stdin);
    }
    while(confirm=='y'||confirm=='Y');
        
        fclose(p);  
    }
    void displayStudent()
    {
       struct Student b;
       FILE*p;
       p=fopen("student.txt","rb");
        if(p==NULL)
        {
            printf("\n Sorry file not found");
            exit(0);
        }
        printf("\n\t\t\t===Student Information===\n");
        printf("\n\t\t\tName\tAddress\tId\tPercentage\n");
		while(fread(&b,sizeof(b),1,p))
        {
		printf("\n\t\t\t%s\t%s\t%d\t%f",b.name,b.address,b.id,b.percentage);
         
     	}
        fclose(p);


    }
