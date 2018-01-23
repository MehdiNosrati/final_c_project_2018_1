#include <stdio.h>
#include <stdlib.h>


struct node
{
    char w[20];
    struct node * next;
};

struct node * words;
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
char * randomchoose(char * choice)
{
    int i,n;
    char retword[50];
    n=cntwords(choice);
    if (n==1)
        return words->w;
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

int main()
{
    int i;
    open("fruits.txt");
    for (i=0 ; i<6 ; i++);
     printf("%s\n",randomchoose("fruits.txt"));
    return 0;
}
