#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Ali Mohamed 6268*/
/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 */
typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;
/*
 *
 */
typedef struct Node
{
    Process data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
    Node* head;
    Node* tail;
    int noOfItems;
} Queue;
Node* newNode(Process val)
{
    Node *n=malloc(sizeof(Node));
    n->data=val;
    n->next=NULL;
    return n;
}
Queue* init()
{
    Queue* q=malloc(sizeof(Queue));
    q->head=q->tail=NULL;
    q->noOfItems=0;
    return q;
}
/*
 *
 */
int isEmpty(Queue *q)
{
    if(!q->noOfItems)
        return 1;
    return 0;
}
/*
 *
 */
Process dequeue(Queue *q)
{

    if(q->head)
    {
        Process val=q->head->data;
        Node *temp=q->head;
        q->head=q->head->next;
        free(temp);
        q->noOfItems--;
        if(q->head==NULL)
            q->tail=NULL;
        return val;
    }
    Process error;
    error.remaining_time=-1;
    error.starting_time=-1;
    error.name=NULL;
    return error;

}

void enqeue(Queue *q,Process val)
{
    Node *n=newNode(val);
    if(!q->head)
        q->head=q->tail=n;
    else
    {
        q->tail->next=n;
        q->tail=n;
    }
    q->noOfItems++;
}
/*
 *
 */
void destroy(Queue *q)
{
    free(q);
}
/*
 * RoundRobin Scheduling
*/
void RoundRobin(char* filename)
{
    FILE *fp=fopen(filename,"r");
    if(!fp)
    {
        printf("failed to open file");
        return;
    }
    Process p[10];
    int i=-1,j;
    char *token=malloc(20);
    char *token1=malloc(20);
    char buffer[100];
    int watchingTime;
    while(!feof(fp))
    {
        fgets(buffer,100,fp);//reads line

        if(i==-1)
        {
            token1=strtok(buffer," ");
            while(token1!=NULL)
            {
                if(atoi(token1))
                {
                    watchingTime=atoi(token1);
                    i++;
                }
                token1=strtok(NULL," ");
            }

        }
        else
        {
            token=strtok(buffer," ");
            while(token!=NULL)
            {
                p[i].name=malloc(3);
                strcpy(p[i].name,token);
                token=strtok(NULL," ");
                p[i].starting_time=atoi(token);
                token=strtok(NULL," ");
                p[i].remaining_time=atoi(token);
                token=strtok(NULL," ");
                i++;
            }

        }

    }
    int pCounter=i;
    Process temp;
    Queue *q=init();
    for(i=0; i<watchingTime; i++)
    {

        for(j=0; j<pCounter; j++)
        {
            if(p[j].starting_time==i)
            {

                enqeue(q,p[j]);
            }
        }
        if(isEmpty(q))
        {
            printf("idle\t(%d-->%d)\n",i,i+1);

        }
        else
        {
            temp=dequeue(q);
            temp.remaining_time--;
            printf("%s\t(%d-->%d) ",temp.name,i,i+1);
            if(temp.remaining_time)
            {
                enqeue(q,temp);
            }
            else if(!temp.remaining_time)
                printf("%s aborts",temp.name);
            printf("\n");
        }
        if(i==watchingTime-1)
            printf("stop\n");
    }
    destroy(q);

}




int main()
{

    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}
