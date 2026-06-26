#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void addStudent();
void deleteStudent();
void displayStudent();
void updateStudent();
void searchStudent();
void sortbyrank();
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
    printf("\n\033[1;4;33m\t\t\t==== Student Record Management System ====\033[0m\n");
    printf("\n\033[1;36m\t\t\t1.Add student\033[0m");
    printf("\n\033[1;36m\t\t\t2.Delete student\033[0m");
    printf("\n\033[1;36m\t\t\t3.Display all student\033[0m");
    printf("\n\033[1;36m\t\t\t4.Update student\033[0m");
    printf("\n\033[1;36m\t\t\t5.Search student\033[0m");
    printf("\n\033[1;36m\t\t\t6.Display student according to rank\033[0m");
    printf("\n\033[1;36m\t\t\t7.Exit\033[0m\n");
    printf("\t\t\tEnter your choice: ");
    scanf("%d",&choice);
     if(choice<1||choice>7)
    {
        printf("\n\033[1;31m Wrong choice\033[0m");
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
      sortbyrank();
      break;
      case 7:
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
        p=fopen("student.txt","ab");
        if(p==NULL)
        {
            printf("\n\033[1;31m Sorry file not found\033[0m");
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
        s.total=0;
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
        printf("\n\033[1;32m\t\t\t**Record Added Succesfully**\033[0m");
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
            printf("\n \033[1;31mSorry file not found\033[0m");
            exit(0);
        }
        printf("\n\033[1;32m\t\t\t====Student Information====\033[0m\n");
        printf("\n\t\t%-7s %-25s %-20s %-8s\n", "\033[1;34mID", "Name", "Address", "Percentage\033[0m\n");
		while(fread(&b,sizeof(b),1,p))
        {
		printf("\t\t%-7d %-25s %-20s %-8.2f\n",b.id,b.name,b.address,b.percentage);
         
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
            printf("\033[1;31m\nSorry file not opened!\033[0m");
            exit(0);
        }
        printf("\t\t\tEnter student ID: ");
        scanf("%d",&id);
        fflush(stdin);
        while(fread(&a,sizeof(a),1,p))
        {
            if(a.id==id)
            {
                found=1;
                printf("\n\033[1;32m\t\t\tStudent found!\033[0m\n");
                printf("\033[1;34m\t\t\tID: %d \n\t\t\tName: %s \n\t\t\tAddress: %s \n\t\t\tPercentage: %2f\033[0m",a.id,a.name,a.address,a.percentage);
                fflush(stdin);
                printf("\n\t\t\tAre you sure you want to delete this record? (Y/N): ");
                scanf("%c",&confirm);
                fflush(stdin);
                if(confirm=='y'||confirm=='Y')
                {
                    printf("\n\t\t\t\033[1;31mRecord deleted sucessfully!\033[0m");
                }
                else
                {
                    fwrite(&a,sizeof(a),1,temp);
                    printf("\n\033[1;32m\t\t\tDeletion Cancelled!\033[0m\n");
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
        rename("temp.txt", "student.txt");

    if(!found)
        printf("\n\033[1;31mStudent not found!\033[0m\n");
    }
    void searchStudent()
    {
        struct Student s;
        int id=0,found=0,i=0;
        FILE *p;
        p=fopen("student.txt","rb");
        if(p==NULL)
        {
            printf("\n\033[1;31mSorry file not opened!\033[0m");
            exit(0);
        }
        printf("\n\t\t\tEnter student ID: ");
        scanf("%d",&id);
        while(fread(&s,sizeof(s),1,p))
        {
            if(s.id==id)
            {
                found=1;
                printf("\n\033[1;32m\t\t\t======Student Information========\033[0m\n");
                printf("\033[1;34m\t\t\tID:\033[0m %d \n\033[1;34m\t\t\tName:\033[0m %s \n\033[1;34m\t\t\tAddress:\033[0m %s \n\033[1;34m\t\t\tPercentage:\033[0m %2f\n",s.id,s.name,s.address,s.percentage);
                printf("\n\033[1;34m\t\t\tMarks\n\033[0m");
                for(i=0;i<5;i++)
                {
                    printf("\t\t\t%s : %2f\n",s.subject[i],s.marks[i]);
                    fflush(stdin);
                }
            }
        }
        if(!found)
        {
            printf("\n\033[1;31mStudent not found!!\033[0m");
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
            printf("\033[1;31mSorry file not opened!\033[0m");
            exit(0);
        }
        printf("Enter student ID to update: ");
        scanf("%d",&id);
        while(fread(&s,sizeof(s),1,p))
        {
            if(s.id==id)
            {
                found=1;
                printf("\n\033[1;32mCurrent Informtion\033[0m\n");
                printf("\033[1;34mID:\033[0m %d \n\033[1;34mName:\033[0m %s \n\033[1;34mAddress:\033[0m %s \n\033[1;34mPercentage:\033[0m %f\n",s.id,s.name,s.address,s.percentage);
                printf("\033[1;34m\tMarks\033[0m\n");
                for(i=0;i<5;i++)
                {
                    printf("%s : %f\n",s.subject[i],s.marks[i]);
                    fflush(stdin);
                }
        printf("\nWhat do you want to update?\n");
        printf("\n1.Name");
        printf("\n2.Address");
        printf("\n3.ID");
        printf("\n4.Marks");
        printf("\n5.All");
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
        fflush(stdin);
        if(choice<1||choice>5)
        {
            printf("\n\033[1;31m Wrong choice\033[0m");
        }
        else
        {
            switch(choice)
            {
                case 1:
                printf("Enter new name: ");
                gets(s.name);
                break;
                case 2:
                printf("Enter new address: ");
                gets(s.address);
                break;
                case 3:
                printf("Enter new ID: ");
                scanf("%d",&s.id);
                break;
                case 4:
                s.total=0;
                for(i=0;i<5;i++)
                {
                    printf("Enter new marks for %s : ",s.subject[i]);
                    scanf("%f",&s.marks[i]);
                    s.total+=s.marks[i];
                }
                s.percentage=s.total/5;
                printf("Percentage: %f",s.percentage);
                break;
                case 5:
                fflush(stdin);
                printf("Enter new name: ");
                gets(s.name);
                fflush(stdin);
                printf("Enter new address: ");
                gets(s.address);
                fflush(stdin);
                printf("Enter new ID: ");
                scanf("%d",&s.id);
                fflush(stdin);
                s.total=0;
                for(i=0;i<5;i++)
                {
                    printf("Enter new marks for %s : ",s.subject[i]);
                    scanf("%f",&s.marks[i]);
                    s.total+=s.marks[i];
                }
                s.percentage=s.total/5;
                printf("Percentage: %f",s.percentage);
                break;
            }
            printf("\n\033[1;32mRecord updated sucessfully!!\033[0m\n");
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
            printf("\n\033[1;31mStudent not found!!\033[0m\n");
        }
    }
    void sortbyrank()
    {
        FILE *p;
        p=fopen("student.txt","rb");
        if(p==NULL)
        {
            printf("\033[1;31mSorry file not opened!\033[0m");
            exit(0);
        }
        int capacity=10,count=0,i=0,j=0;
        struct Student *q;
        q=malloc(capacity*sizeof(struct Student));
        if(q==NULL)
        {
            printf("Sorry memory not allocated!");
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
            printf("\n\033[1;31mNo student found!!\033[0m");
            free(q);
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
        printf("\n\033[1;32m=== Student Ranking by Percentage ===\033[0m\n");
        printf("\n%-5s %-10s %-20s %-20s %-10s\n", "\033[1;34mRank", "ID", "Name", "Address", "Percentage\033[0m");
        for(i=0;i<count;i++)
        {
           printf("%-5d %-10d %-20s %-20s %-8.2f\n",i+1, q[i].id, q[i].name, q[i].address, q[i].percentage);

        }
        free(q);
    }
    