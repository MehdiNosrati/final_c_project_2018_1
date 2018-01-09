#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
/*
 *c 2017-2018 final project
 *Mehdi NS
 */

//struct definitions
struct node
{
    char  w[50];
    struct node * next;
} ;
typedef struct
{
    char name[20];
    int score;
} user;

//global variables
FILE *fp;
char  topics[50] ;
struct node * words;
//prototypes
void menu();
void lists();
void open(char*);
struct node * creatlist(char *);
void  add_end(struct node *, char * );
char * randomchoose(char *);
int cntwords(char *);
void initplayground(int);



int main()
{
    srand(time(NULL));
    system("color 30");
    user u;
    printf("enter name:");
    scanf("%s",u.name);
    char * top;
    char matchword [50];
    char choice[50];
    //manu
    int op,dash,i;
    menu();
    scanf("%d",&op);
    switch (op)
    {
    case 1:
        lists();

        printf("type in topic name:");
        scanf("%s",choice);
        open(choice);
        strcpy(matchword,randomchoose(choice));
        dash=strlen(matchword);
        initplayground(dash);


        break;
        //case 2: load();
    }

     /*   while (words->next!=NULL)
        {
            printf("%s\n",words->w);
            words=words->next;
        }
        */

    return 0;
}
void menu()
{
    printf("enter operation to be done:\n");
    printf("<1> new game\n<2>load game\n");
}
void lists()
{

    fp=fopen("AVAILABLE_TOPICS.txt","r");
    if (fp==NULL)
    {
        printf("cannot open the file!");
        exit(-1);
    }

    while (feof(fp)==0)
    {

        fgets(topics,50,fp);
        printf("<>    %s\n",topics);

    }

    fclose(fp);


}

void open (char * ch)
{
    words=(struct node *)malloc(sizeof(struct node));
    char  wor[50];
    FILE * fto;
    fto=fopen(ch,"r");

    fscanf(fto,"%s",wor);
    words=creatlist(wor);
    while (feof(fto)==0)
    {
        fscanf(fto, "%s", wor);
        add_end(words,wor);
    }

    fclose(fto);


}
struct node * creatlist(char * i)
{
    struct node *nn;
    nn=(struct node *)malloc(sizeof(struct node));
    strcpy(nn->w, i);
    nn->next=NULL;
    return nn;
}
void  add_end(struct node *list, char * i)
{
    struct node * newnode=(struct node *) malloc(sizeof(struct node));
    struct node * cur;

    for (cur=list ; cur->next!=NULL ; cur=cur->next);

    strcpy(newnode->w, i);
    cur->next=newnode;
    newnode->next=NULL;

}
char * randomchoose(char * choice)
{
    int i,n;
    char retword[50];
    n=cntwords(choice);
    n=rand()%(n+1);
    struct node * tmp;
    tmp=words;
    for (i=0; i<n ; i++)
        tmp=tmp->next;

    strcpy(retword,tmp->w);
    delnode (tmp);
    return retword;

}

int cntwords(char * i)
{
    FILE * fto;
    int cnt=0;
    char tmp[50];
    fto=fopen(i,"r");
    while (feof(fto)==0)
    {
        fscanf(fto,"%s",tmp);
        cnt++;

    }
    fclose(fto);

    return cnt;
}
void delnode(struct Node *n)
{

    if(words == n)
    {
        if(words->next == NULL)
        {
            printf("There is only one node. The list can't be made empty ");
            return;
        }


        strcpy(words->w , words->next->w);


        n = words->next;


        words->next = words->next->next;


        free(n);

        return;
    }



    struct node *prev = words;
    while(prev->next != NULL && prev->next != n)
        prev = prev->next;


    if(prev->next == NULL)
    {
        printf("\n Given node is not present in Linked List");
        return;
    }

    prev->next = prev->next->next;


    free(n);

    return;
}

void initplayground(int dash)
{
    int i;
    for (i=0 ; i<dash ; i++)
        printf(" %c ",177);
}

