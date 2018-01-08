#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef struct
{
    char name[20];
    int score;
} user;
FILE *fp;
void menu();
void lists();

int main()
{
    system("color 30");
    user u;
    printf("enter name:");
    scanf("%s",u.name);


    //manu
    int op;
    menu();
    scanf("%d",&op);
       lists();


    return 0;
}
void menu()
{
    printf("enter operation to be done:\n");
    printf("<1> new game\n<2>load game\n");
}
void lists()
{
    int i;
    fp=fopen("AVAILABLE_TOPICS.txt","r+");
    if (fp==NULL)
    {
        printf("cannot open the file!");
        exit(-1);
    }
    char  topics[50] ;

    for (i=0 ; i<5 ; i++)
    {

        fgets(topics,50,fp);
        printf("<%d> %s",i+1,topics);
    }

    fclose(fp);


}
