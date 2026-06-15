#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Student{
    char name[50];
    char address[40];
    int id;
    float marks;
};
int main()
{
    int choice=0;
    printf("\n====Student Record Management System====\n");
    printf("1.Add student\n");
    printf("2.Delete student\n");
    printf("3.Display all student\n");
    printf("4.Update student\n");
    printf("5.Search student\n");
    printf("6.Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

}
