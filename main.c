#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define C "                    "
void addStudent();
void deleteStudent();
void displayStudent();
void updateStudent();
void searchStudent();
void sortbyrank();
int checkduplicateid(int);
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
        printf("\n\033[1;4;33m"C"==== Student Record Management System ====\033[0m\n");
        printf("\n\033[1;36m"C"1. Add student\033[0m\n");
        printf("\033[1;36m"C"2. Delete student\033[0m\n");
        printf("\033[1;36m"C"3. Display all students\033[0m\n");
        printf("\033[1;36m"C"4. Update student\033[0m\n");
        printf("\033[1;36m"C"5. Search student\033[0m\n");
        printf("\033[1;36m"C"6. Display students by rank\033[0m\n");
        printf("\033[1;36m"C"7. Exit\033[0m\n");
        printf( C"Enter your choice: ");
        scanf("%d",&choice);
        if(choice<1||choice>7)
        {
            printf("\n\033[1;31m"C"Wrong choice\033[0m\n");
        }
        else
        {
            switch(choice)
            {
                case 1: addStudent();  
			    break;
                case 2: deleteStudent();
			     break;
                case 3: displayStudent();
				break;
                case 4: updateStudent();
				 break;
                case 5: searchStudent();
				 break;
                case 6: sortbyrank();    
				break;
                case 7: exit(0);
            }
        }
    }
    return 0;
}
int checkduplicateid(int id)
{
    struct Student temp;
    FILE *p;
    p=fopen("student.txt","rb");
    if(p==NULL)
    {
        printf("\n\033[1;31m"C"Sorry file not found\033[0m\n");
        exit(0);
    }
    while(fread(&temp,sizeof(temp),1,p))
    {
        if(temp.id==id)
        {
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return 0;
}
void addStudent()
{
    struct Student s;
    s.total=0;
    int i=0,j=0;
    char confirm=0;
    int valid;
    FILE *p;
    p=fopen("student.txt","ab");
    if(p==NULL)
    {
        printf("\n\033[1;31m"C"Sorry file not found\033[0m\n");
        exit(0);
    }
	do
    {
        printf("\n\033[1;32m"C"=== Add Student Information ===\033[0m\n\n");
        do
		{
			valid=1;
			fflush(stdin);
		    printf(C"Enter name of student: ");
            gets(s.name);
           for(i=0;s.name[i]!='\0';i++)
           {
           	if(!(isalpha(s.name[i])||(s.name[i])==' '))
           	{
           		valid=0;
           		break;
			}
		   }
		   if(valid==0)
		   {
		   	 printf("n\033[1;31m"C"Invalid name!\033[0m\n");
		   }
       	}
		while(valid==0);
        fflush(stdin);
        printf(C"Enter address: ");
        gets(s.address);
        fflush(stdin);
        do
        {
            fflush(stdin);
            printf(C"Enter id: ");
            scanf("%d",&s.id);
            if(s.id <= 0)
            {
                printf("\033[1;31m"C"Invalid ID! Must be positive.\033[0m\n");
            }
            else if(checkduplicateid(s.id))
            {
                printf("\033[1;31m"C"This ID already exists! Enter a unique ID.\033[0m\n");
                s.id = -1;
            }
            fflush(stdin);
        } 
		while (s.id<=0||checkduplicateid(s.id));
        fflush(stdin);
        printf("\n"C"--- Marks ---\n");
        s.total=0;
        for(i=0;i<5;i++)
        {
            fflush(stdin);
            do
			{
			  valid=1;
			 fflush(stdin);
		     printf(C"Enter subject: ");
             gets(s.subject[i]);
            for(j=0;s.subject[i][j]!='\0';j++)
           {
           	if(!(isalpha(s.subject[i][j])||(s.subject[i][j])==' '))
           	{
           		valid=0;
           		break;
			}
		   }
		   if(valid==0)
		   {
		   	 printf("n\033[1;31m"C"Invalid subject!\033[0m\n");
		   }
       	}
		while(valid==0);
        printf(C"Enter marks: ");
        scanf("%f",&s.marks[i]);
        s.total=s.total+s.marks[i];
        }
        s.percentage=s.total/5;
        printf("\n"C"Total Percentage: %.2f\n", s.percentage);
        printf("\033[1;32m"C"** Record Added Successfully **\033[0m\n");
        fflush(stdin);
        fwrite(&s,sizeof(s),1,p);
        printf(C"Add more students? (y/n): ");
        scanf(" %c",&confirm);
        printf(C"----------------------------------------\n");
        fflush(stdin);
    }
    while(confirm=='y'||confirm=='Y');
    fclose(p);
}
void displayStudent()
{
    struct Student b;
    FILE *p;
    p=fopen("student.txt","rb");
    if(p==NULL)
    {
        printf("\n\033[1;31m"C"Sorry file not found\033[0m\n");
        exit(0);
    }
    printf("\n\033[1;32m"C"==== Student Information ====\033[0m\n\n");
    printf(C"\033[1;34m%-7s %-25s %-20s %-10s\033[0m\n", "ID", "Name", "Address", "Percentage");
    while(fread(&b,sizeof(b),1,p))
    {
        printf(C"%-7d %-25s %-20s %-10.2f\n", b.id, b.name, b.address, b.percentage);
    }
    fclose(p);
}

void deleteStudent()
{
    struct Student a;
    int id=0,found=0;
    char confirm=0;
    FILE *p,*temp;
    p=fopen("student.txt","rb");
    temp=fopen("temp.txt","wb");
    if(p==NULL||temp==NULL)
    {
        printf("\033[1;31m"C"Sorry file not opened!\033[0m\n");
        exit(0);
    }
    printf(C"Enter student ID: ");
    scanf("%d",&id);
    fflush(stdin);
    while(fread(&a,sizeof(a),1,p))
    {
        if(a.id==id)
        {
            found=1;
            printf("\n\033[1;32m"C"Student found!\033[0m\n");
            printf("\033[1;34m"C"ID: %d\n"C"Name: %s\n"C"Address: %s\n"C"Percentage: %.2f\033[0m\n",
                   a.id, a.name, a.address, a.percentage);
            fflush(stdin);
            printf(C"Are you sure you want to delete? (Y/N): ");
            scanf("%c",&confirm);
            fflush(stdin);
            if(confirm=='y'||confirm=='Y')
            {
                printf("\n\033[1;31m"C"Record deleted successfully!\033[0m\n");
            }
            else
            {
                fwrite(&a,sizeof(a),1,temp);
                printf("\n\033[1;32m"C"Deletion Cancelled!\033[0m\n");
            }
        }
        else
        {
            fwrite(&a,sizeof(a),1,temp);
        }
    }
    fclose(p);
    fclose(temp);
    remove("student.txt");
    rename("temp.txt","student.txt");
    if(!found)
        printf("\n\033[1;31m"C"Student not found!\033[0m\n");
}

void searchStudent()
{
    struct Student s;
    int id=0,found=0,i=0;
    FILE *p;
    p=fopen("student.txt","rb");
    if(p==NULL)
    {
        printf("\n\033[1;31m"C"Sorry file not opened!\033[0m\n");
        exit(0);
    }
    printf(C"Enter student ID: ");
    scanf("%d",&id);
    while(fread(&s,sizeof(s),1,p))
    {
        if(s.id==id)
        {
            found=1;
            printf("\n\033[1;32m"C"====== Student Information ======\033[0m\n\n");
            printf("\033[1;34m"C"ID:\033[0m %d\n", s.id);
            printf("\033[1;34m"C"Name:\033[0m %s\n", s.name);
            printf("\033[1;34m"C"Address:\033[0m %s\n", s.address);
            printf("\033[1;34m"C"Percentage:\033[0m %.2f\n", s.percentage);
            printf("\n\033[1;34m"C"--- Marks ---\033[0m\n");
            for(i=0;i<5;i++)
            {
                printf(C"%s : %.2f\n", s.subject[i], s.marks[i]);
                fflush(stdin);
            }
        }
    }
    if(!found)
    {
        printf("\n\033[1;31m"C"Student not found!\033[0m\n");
    }
    fclose(p);
}

void updateStudent()
{
    struct Student s;
    int id=0,choice=0,found=0,i=0;
    FILE *p;
    FILE *temp;
    p=fopen("student.txt","rb");
    temp=fopen("temp.txt","wb");
    if(p==NULL||temp==NULL)
    {
        printf("\033[1;31m"C"Sorry file not opened!\033[0m\n");
        exit(0);
    }
    printf(C"Enter student ID to update: ");
    scanf("%d",&id);
    while(fread(&s,sizeof(s),1,p))
    {
        if(s.id==id)
        {
            found=1;
            printf("\n\033[1;32m"C"Current Information\033[0m\n\n");
            printf("\033[1;34m"C"ID:\033[0m %d\n", s.id);
            printf("\033[1;34m"C"Name:\033[0m %s\n", s.name);
            printf("\033[1;34m"C"Address:\033[0m %s\n", s.address);
            printf("\033[1;34m"C"Percentage:\033[0m %.2f\n", s.percentage);
            printf("\n\033[1;34m"C"--- Marks ---\033[0m\n");
            for(i=0;i<5;i++)
            {
                printf(C"%s : %.2f\n", s.subject[i], s.marks[i]);
                fflush(stdin);
            }
            printf("\n"C"What do you want to update?\n");
            printf(C"1. Name\n");
            printf(C"2. Address\n");
            printf(C"3. ID\n");
            printf(C"4. Marks\n");
            printf(C"5. All\n");
            printf(C"Enter your choice: ");
            scanf("%d",&choice);
            fflush(stdin);
            if(choice<1||choice>5)
            {
                printf("\n\033[1;31m"C"Wrong choice\033[0m\n");
            }
            else
            {
                switch(choice)
                {
                    case 1:
                        printf(C"Enter new name: ");
                        gets(s.name);
                        break;
                    case 2:
                        printf(C"Enter new address: ");
                        gets(s.address);
                        break;
                    case 3:
                        do {
                            fflush(stdin);
                            printf(C"Enter new id: ");
                            scanf("%d",&s.id);
                            if(s.id <= 0)
                                printf("\033[1;31m"C"Invalid ID! Must be positive.\033[0m\n");
                            else if(checkduplicateid(s.id)) {
                                printf("\033[1;31m"C"This ID already exists! Enter a unique ID.\033[0m\n");
                                s.id = -1;
                            }
                            fflush(stdin);
                        } while (s.id<=0||checkduplicateid(s.id));
                        break;
                    case 4:
                        s.total=0;
                        for(i=0;i<5;i++) {
                            printf(C"Enter new marks for %s: ", s.subject[i]);
                            scanf("%f",&s.marks[i]);
                            s.total+=s.marks[i];
                        }
                        s.percentage=s.total/5;
                        printf(C"Percentage: %.2f\n", s.percentage);
                        break;
                    case 5:
                        fflush(stdin);
                        printf(C"Enter new name: ");
                        gets(s.name);
                        fflush(stdin);
                        printf(C"Enter new address: ");
                        gets(s.address);
                        fflush(stdin);
                        do {
                            fflush(stdin);
                            printf(C"Enter new id: ");
                            scanf("%d",&s.id);
                            if(s.id <= 0)
                                printf("\033[1;31m"C"Invalid ID! Must be positive.\033[0m\n");
                            else if(checkduplicateid(s.id)) {
                                printf("\033[1;31m"C"This ID already exists! Enter a unique ID.\033[0m\n");
                                s.id = -1;
                            }
                            fflush(stdin);
                        } while (s.id<=0||checkduplicateid(s.id));
                        fflush(stdin);
                        s.total=0;
                        for(i=0;i<5;i++) {
                            printf(C"Enter new marks for %s: ", s.subject[i]);
                            scanf("%f",&s.marks[i]);
                            s.total+=s.marks[i];
                        }
                        s.percentage=s.total/5;
                        printf(C"Percentage: %.2f\n", s.percentage);
                        break;
                }
                printf("\n\033[1;32m"C"Record updated successfully!\033[0m\n");
                fwrite(&s,sizeof(s),1,temp);
            }
        }
        else
        {
            fwrite(&s,sizeof(s),1,temp);
        }
    }
    fclose(p);
    fclose(temp);
    remove("student.txt");
    rename("temp.txt","student.txt");
    if(!found)
    {
        printf("\n\033[1;31m"C"Student not found!\033[0m\n");
    }
}

void sortbyrank()
{
    FILE *p;
    p=fopen("student.txt","rb");
    if(p==NULL)
    {
        printf("\033[1;31m"C"Sorry file not opened!\033[0m\n");
        exit(0);
    }
    int capacity=10,count=0,i=0,j=0;
    struct Student *q;
    q=malloc(capacity*sizeof(struct Student));
    if(q==NULL)
    {
        printf(C"Sorry memory not allocated!\n");
        exit(0);
    }
    struct Student temp;
    while(fread(&q[count],sizeof(struct Student),1,p))
    {
        count++;
        if(count>=capacity)
        {
            capacity*=2;
            q=realloc(q,capacity*sizeof(struct Student));
        }
    }
    fclose(p);
    if(count==0)
    {
        printf("\n\033[1;31m"C"No students found!\033[0m\n");
        free(q);
        return;
    }
    for(i=0;i<count-1;i++)
    {
        for(j=i+1;j<count;j++)
        {
            if(q[i].percentage<q[j].percentage)
            {
                temp=q[i];
                q[i]=q[j];
                q[j]=temp;
            }
        }
    }
    printf("\n\033[1;32m"C"=== Student Ranking by Percentage ===\033[0m\n\n");
    printf(C"\033[1;34m%-5s %-10s %-20s %-20s %-10s\033[0m\n", "Rank", "ID", "Name", "Address", "Percentage");
    for(i=0;i<count;i++)
    {
        printf(C"%-5d %-10d %-20s %-20s %-8.2f\n", i+1, q[i].id, q[i].name, q[i].address, q[i].percentage);
    }
    free(q);
}