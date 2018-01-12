#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
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
user u;
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
int play(int,char *);
int corword(char,int, int );
void quit();
int roword();
void topicgen();

int main()
{
    srand(time(NULL));
    system("color 30");

    printf("enter name:");
    scanf("%s",u.name);
    char * top;
    char matchword [50];
    char choice[50];
    //manu
    int op,i;
    int dash;
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
        printf("%s\n",matchword);
        initplayground(dash);
        play(dash,matchword);



        break;
        //case 2: load();

        case 3: topicgen();
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
    printf("<1> new game\n<2> load game\n<3> topic generator");
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


        strcpy(words->w, words->next->w);


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
char pg[50];
void initplayground(int dash)
{
    int i;
    for (i=0 ; i<dash ; i++)
       {
        pg[i]='-';
        printf(" %c ",pg[i]);
       }
        printf("\n");
}

int play (int dash,char * mw)
{
    char tmp[dash];
    strcpy(tmp,mw);
    char ent;
    while (1)
    {
        ent=getch();
        if (ent=='Q')
            quit();
        int i,j,k;
        for (i=0 ; i<dash ; i++)
            if (ent==tmp[i])
                corword(ent,i,dash);
       //  else
              //  roword();   ///last edit


    }


}

int corword(char en,int n,int dash)
{

    int i;

    for (i=0 ; i<dash ; i++)
       if (pg[i]=='-')
         pg[i]='-';

    pg[n]=en;
    for (i=0 ; i<dash ; i++)
        printf(" %c ",pg[i]);
    printf("      correct!\n");
}

void quit()
{
    printf("\nu sure u want to quit the game? (y/n) ");
    char op,cp;
    op=getch();
    if (op=='y')
    {
        printf("\nsave the game? (y/n)");
        cp=getch();
        if (cp=='y')
        {
            FILE * save;
            save=fopen("save.txt","a");
            fprintf(save,"\n%s",u.name);
            fclose(save);
            exit(10);

        }
        else
            exit(5);


    }
    else
        return;
}

void topicgen()
{
    FILE *topic;
    printf("\n\n please enter topic name: ");
    char tname[30];
    scanf("%s",tname);

    printf("please enter number of words u want to add");
    int num;
    scanf("%d",&num);;
    printf("\n please enter the words u want to be added into this topic:\n");
    topic=fopen(tname,"w");
    int i;
    char wo[50];
    for (i=0 ; i<num ; i++)
        {scanf("%s",wo);
        fprintf(topic,"%s\n",wo);
        }
        printf("topic generation dona!");
        fclose(topic);
        FILE * tpc;
        tpc=fopen("AVAILABLE_TOPICS.txt","a");
        fprintf(tpc,"\n%s",tname);
        fclose(tpc);
}

