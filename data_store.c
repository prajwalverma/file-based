#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

struct emp
{
    char id[20];
    int salary;
};

void append();
void display();
void displayAll();
void modify();
void del();
int search();
void rremove();

char fname[]={"mydb.dat"};

void main()
{
    int ch;

    while(1)
    {

        printf("==================Employee Management System=============\n\n");

        printf("1. Append\n\n");
        printf("2. Modify\n\n");
        printf("3. Delete\n\n");
        printf("4. Display\n\n");
        printf("5. Display All\n\n");
        printf("6. Delete File\n\n");
        printf("0. Exit\n\n");

        printf("========================================================\n\n");

        printf("\nPlease enter your Choice:");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1: append();
            break;

            case 2: modify();
            break;

            case 3: del();
            break;

            case 4: display();
            break;

            case 5: displayAll();
            break;

            case 6: rremove();
            break;

            case 0: exit(0);
        }
        getch();
    }

}
void append()
{
    FILE *fp;
    struct emp t1;

    fp=fopen(fname,"ab");

    printf("\nEnter ID:");
    scanf("%s",t1.id);
    printf("\nEnter salary:");
    scanf("%d",&t1.salary);
    if(search(t1))
    {
        fwrite(&t1,sizeof(t1),1,fp);
    }
    else
    {
        printf("\n\nalready present");
    }
    fclose(fp);
}


void rremove()
{
    FILE *fp,*fp1;
    struct emp t;

    char name[20];
    char val[20];

    printf("\nDo you want to make copy of it (Y/N):");
    scanf("%s",val);

    if(strcmp(val,"Y")==0)
    {

        printf("\nEnter the New File Name:");
        fflush(stdin);
        scanf("%[^\n]",name);

        fp=fopen(name,"wb");
        fp1=fopen(fname,"rb");

        while(1)
        {
            fread(&t,sizeof(t),1,fp1);

            if(feof(fp1))
            {
                break;
            }
            fwrite(&t,sizeof(t),1,fp);
        }

        fclose(fp);
        fclose(fp1);

        remove(fname);

        strcpy(fname,name);
    }
    else
    {
        remove(fname);
    }
}

void modify()
{
    FILE *fp,*fp1;
    struct emp t,t1;
    int found=0,count=0;
    char id[20];

    fp=fopen(fname,"rb");
    fp1=fopen("temp.dat","wb");

    printf("\nEnter the Emp ID you want to Modify:");
    scanf("%s",id);

    while(1)
    {
        fread(&t,sizeof(t),1,fp);

        if(feof(fp))
        {
            break;
        }
        if(strcmp(id,t.id)==0)
        {
            found=1;
            printf("\nEnter Employee ID:");
            scanf("%s",t.id);

            fflush(stdin);
            printf("\nEnter Employee Salary:");
            scanf("%d",&t.salary);
            fwrite(&t,sizeof(t),1,fp1);
        }
        else
        {
            fwrite(&t,sizeof(t),1,fp1);
        }
    }
    fclose(fp);
    fclose(fp1);

    if(found==0)
    {
        printf("Sorry No Record Found\n\n");
    }
    else
    {
        fp=fopen(fname,"wb");
        fp1=fopen("temp.dat","rb");

        while(1)
        {
            fread(&t,sizeof(t),1,fp1);

            if(feof(fp1))
            {
                break;
            }
            fwrite(&t,sizeof(t),1,fp);
        }

    }
    fclose(fp);
    fclose(fp1);
}

void del()
{
    FILE *fp,*fp1;
    struct emp t,t1;
    int found=0,count=0;
    char id[20];

    fp=fopen(fname,"rb");
    fp1=fopen("temp.dat","wb");

    printf("\nEnter the Emp ID you want to Delete:");
    scanf("%s",id);

    while(1)
    {
        fread(&t,sizeof(t),1,fp);

        if(feof(fp))
        {
            break;
        }
        if(strcmp(id,t.id)==0)
        {
            found=1;
        }
        else
        {
            fwrite(&t,sizeof(t),1,fp1);
        }
    }
    fclose(fp);
    fclose(fp1);

    if(found==0)
    {
        printf("Sorry No Record Found\n\n");
    }
    else
    {
        fp=fopen(fname,"wb");
        fp1=fopen("temp.dat","rb");

        while(1)
        {
            fread(&t,sizeof(t),1,fp1);

        if(feof(fp1))
        {
            break;
        }
        fwrite(&t,sizeof(t),1,fp);
        }
    }
    fclose(fp);
    fclose(fp1);
}

void display()
{
    FILE *fp;
    struct emp t;
    int found=0;
    char id[20];

    fp=fopen(fname,"rb");
    if(fp != 0)
    {
        printf("\nEnter the Emp ID:");
        scanf("%s",id);

        while(1)
        {
            fread(&t,sizeof(t),1,fp);

            if(feof(fp))
            {
                break;
            }
            if(strcmp(id,t.id)==0)
            {
                found=1;
                printf("\n========================================================\n\n");
                printf("\t\t Employee Details of %s\n\n",t.id);
                printf("========================================================\n\n");

                printf("Salary\n\n");
                printf("%d\t\n\n",t.salary);

                printf("========================================================\n\n");
            }
        }
        if(found==0)
        {
            printf("\nSorry No Record Found");
        }
        fclose(fp);
    }
    else{
        printf("there is no file firstly create a file");
    }

}

int search(struct emp t1)
{
    FILE *fp;
    struct emp t;
    int found=0;

    fp=fopen(fname,"rb");

    while(1)
    {
        fread(&t,sizeof(t),1,fp);

        if(feof(fp))
        {
            break;
        }
        if(strcmp(t1.id,t.id)==0)
        {
            return 0;
        }
    }
    if(found==0)
    {
        return 1;
    }
    fclose(fp);
}
void displayAll()
{
    FILE *fp;
    struct emp t;

    fp=fopen(fname,"rb");
    if(fp != 0)
    {
        printf("\n========================================================\n\n");
        printf("\t\t All Employee Details\n\n");
        printf("========================================================\n\n");

        printf("ID\tSalary\n\n");

        while(1)
        {
            fread(&t,sizeof(t),1,fp);

            if(feof(fp))
            {
                break;
            }
            printf("%s\t",t.id);
            printf("%d\t\n\n",t.salary);

        }
        printf("========================================================\n\n");

        fclose(fp);
    }
    else
    {
        printf("there is no file firstly create a file");
    }

}
