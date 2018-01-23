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
int highscore;
//prototypes
void menu();
void lists();
void open(char*);
struct node * creatlist(char *);
void  add_end(struct node *, char * );
char * randomchoose(char *,int);
int cntwords(char *);
void initplayground(int);
int play(int,char *,char *);
int corword(char,int, int );
void quit(char *);
int roword();
void topicgen();
void perso(int);         ///
int load(char *);
void quittopic (char * );

int main()
{
    srand(time(NULL));
    system("color 30");
    int score=0;
    printf("enter name:");
    scanf("%s",u.name);


    char * top;
    char matchword [50];
    char choice[50];

    //manu
    int op,i;
    int dash;

    while (1)
    {
        menu();
        scanf("%d",&op);
        int n;
        u.score=0;
        switch (op)
        {
        case 1:
            lists();

            printf("type in topic name:");
            scanf("%s",choice);
            open(choice);
            n=cntwords(choice);
            //topic start
            clock_t begin=clock();
            while (words->next!=NULL && n!=0)
            {
                strcpy(matchword,randomchoose(choice,n));
                n--;
                dash=strlen(matchword);
                printf("%s\n",matchword);
                initplayground(dash);
                u.score+=play(dash,matchword,choice);
                if (u.score>highscore)
                    highscore=u.score;



            }
            //topic ends
            clock_t end =clock();
            int timespent=(int)(end-begin)/CLOCKS_PER_SEC;
            printf("%d",timespent);
            if (u.score>highscore)
                highscore=u.score;
            highscore=u.score/timespent;
            quittopic(choice);


            break;
        case 2:
            lists();
            printf("type in topic name:");
            scanf("%s",choice);
            u.score=load(choice);
            if (u.score>highscore)
                highscore=u.score;
            printf("ur highest score was %d in %s topic \n",u.score,choice);
            open(choice);
            n=cntwords(choice);
            //topic start
            clock_t beginl=clock();
            while (words->next!=NULL&& n!=0)
            {
                strcpy(matchword,randomchoose(choice,n));
                n--;
                dash=strlen(matchword);
                printf("%s\n",matchword);
                initplayground(dash);
                u.score+=play(dash,matchword,choice);
                if (u.score>highscore)
                    highscore=u.score;


            }
            clock_t endl =clock();
            timespent=(int)(endl-beginl)/CLOCKS_PER_SEC;
            if (u.score>highscore)
                highscore=u.score;
            highscore=u.score/timespent;
            quittopic(choice);
            break;

        case 3:

            topicgen();
            break;




        }
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
char * randomchoose(char * choice,int cnw)
{
    int i,n=0;
    char retword[50];

    if (cnw==1)
        return words->w;
    while(n==0)
        n=rand()%(cnw+1);

    struct node * tmp;
    tmp=words;
    for (i=1; i<n ; i++)
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

    return cnt-1;
}
void delnode(struct node *n)
{

    if(strcmp(words->w, n->w)==0)
    {


        words=words->next;

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

int play (int dash,char * mw, char * choice)
{
    char tmp[dash];
    int rep=0;
    int wrongguess=0;
    int test=0;
    char entrd[dash];
    strcpy(tmp,mw);
    char ent;
    int remain=dash;
    int i,j,k;
    int scr=0;
    while (remain>0 && wrongguess<5)
    {
        rep=0;
        test=0;

        ent=getch();
        for (j=0 ; j<dash ; j++)
            if (ent==entrd[j])
            {
                printf("u have entered this character already ! \n");
                rep++;
            }
        if (ent=='Q')
            quit(choice);

        for (i=0 ; i<dash ; i++)
            if (ent==tmp[i])
            {
                corword(ent,i,dash);
                entrd[i]=ent;
                if (rep==0)
                    remain--;

                test++;
            }


        if (test==0)
        {
            wrongguess++;
            perso(wrongguess);
            printf("wrong choice! (%d / 5) to next word!\n",wrongguess);
        }




    }
    if (remain<=0)
    {
        scr=(3*dash)-(wrongguess);
        return scr;
    }
    else
        return 0;




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

void quit( char * choice)
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
            save(choice);
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
    topic=fopen(tname,"a");
    int i;
    char wo[50];
    for (i=0 ; i<num ; i++)
    {
        scanf("%s",wo);
        fprintf(topic,"%s\n",wo);
    }
    printf("topic generation dona!\n");
    fclose(topic);
    FILE * tpc;
    tpc=fopen("AVAILABLE_TOPICS.txt","a");
    fprintf(tpc,"\n%s",tname);
    fclose(tpc);
}

int load (char* ch)
{
    FILE *fs;
    fs=fopen ("save.txt","r");
    char search[30]="empty";
    char name [20]="empty";
    int emti=0,emti2=0;
    int score=0;




    while (strcmp (name,u.name)!=0 || strcmp(ch,search)!=0 )
    {
        while (feof(fs)==0)
        {
            fscanf(fs,"%s %s %d",name,search, &emti);
            if (strcmp(name,u.name)==0 && strcmp(search,ch)==0)
                if (score <= emti)
                    score=emti;
        }
    }

    fclose(fs);
    return score;

}
void quittopic(char * choice)
{
    printf("u wanna continue? (y/n)");
    char op,cp;
    op=getch();
    if (op=='y')
    {
        printf("ur score in %s topic was %d\n",choice, highscore);
        return;
    }
    else
    {
        printf("\nsave the game? (y/n)");
        cp=getch();
        if (cp=='y')
        {
            save(choice);
            exit(15);
        }
        else
            exit(20);
    }
}
void save (char * tpc)
{



    FILE *fs;
    fs=fopen("save.txt","a");
    fprintf(fs,"%s \n",u.name);
    fprintf(fs,"%s %d \n",tpc, highscore);
    fclose(fs);

}
void perso(int lv)
{
    FILE * shape;
    char buff[100];
    switch (lv)
    {
    case 1 :
        shape=fopen("1.txt","r");
        break;
    case 2 :
        shape=fopen("2.txt","r");
        break;
    case 3:
        shape=fopen("3.txt","r");
        break;
    case 4:
        shape=fopen("4.txt","r");
        break;
    case 5:
        shape=fopen("5.txt","r");
        break;
    }
        printf("\n");
        while (feof(shape)==0)
        {
            fgets(buff, 100, shape);
            printf("%s",buff);
        }

        fclose(shape);

    }




