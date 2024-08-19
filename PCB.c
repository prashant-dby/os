#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

struct PCB{
    int id;
    char state[20];
    int time;
    struct PCB *next;
};
void enqueuepcb();
void dequeuepcb();
void display();

struct  PCB *head=NULL , *newnode=NULL , *temp=NULL ; 

void main (){
    int ch , cont=0;
    do
    {
        printf("1.Load the new PCB");
        printf("2.Remove the PCB completely");
        printf("3.List of PCBs");
        printf("Enter Your Choice ");
        scanf("%d", &ch);
        if (ch==1){
            enqueuepcb();
        }
        else if (ch==2){
            dequeuepcb();
        }
        else if (ch==3)
        {
            display();
        }
        
        else{
            printf("Invalid Choice");
            
        }
        printf("Do you want continue 1/0");
            scanf("%d", &cont);
    } while (cont==1);
    
}

void enqueuepcb(){
    newnode = (struct PCB *)malloc(sizeof(struct PCB));
    printf("Enter id,state,timeStamp");
    scanf("%d%s%d",&newnode->id,&newnode->state,&newnode->time);
    newnode->next=NULL;
    
if(head==NULL){
 head=newnode;   
}
else{
    temp=head;
    while (temp->next!=NULL) 
    {
        temp=temp->next;
    }
    temp->next=newnode;
}
}

void dequeuepcb(){
    head=head->next;

}

void display(){
    temp=head;
    while (temp->next!=NULL) 
    {
        printf("%d",temp->id);
        printf("%s\n",temp->state);
        temp=temp->next;
    }
printf("%d",temp->id);
        printf("%s",temp->state);
    
}

