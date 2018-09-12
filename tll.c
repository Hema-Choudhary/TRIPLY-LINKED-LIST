#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct node
{
 int val;
 struct node *next,*prev,*big;
}node;

node *head=NULL,*temp2=NULL,*temp=NULL,*small=NULL,*temp1=NULL;

void del(int);
void insert(node *);
void trav(void);
void create (int);
void searchB(node *); 
void delmul(node *,int);

void create(int n)
{
 int i;
 for(i=0;i<n;i++)
 {
  node *new=(node*)malloc(sizeof(node));
  fprintf(stdout,"\nEnter the val:");
  fscanf(stdin,"%d",&new->val);
  new->next=NULL;
  new->prev=NULL;
  new->big=NULL;

   if(head == NULL)
  {
   head=temp=small=new;
  }
  else
  {
   temp->next=new;
   new->prev=temp;
   temp=new;
   searchB(new);
  } 
 }
}

void searchB(node *ptr)
{
 int f=0;
 temp1=small;
 if(temp1->val > ptr->val)
 {
  ptr->big=temp1;
  small=ptr;
  f=1;
 }
 else if((temp1->val <= ptr->val) && temp1->big==NULL && (temp1 == small))
 {
   temp1->big=ptr;
   f=1;
 }
 else
 {
 for(temp1=small;temp1->big != NULL;temp1=temp1->big)
  {
   if((temp1->val <= ptr->val) && (temp1->big->val > ptr->val))
   {
    ptr->big=temp1->big;
    temp1->big=ptr;
    break;
    f=1;
   }
  }
 }
 if(temp1->big==NULL && f!=1)
 {
 temp1->big=ptr;
 }
}


void trav(void)
{
 fprintf(stdout,"\nThe Elements are:\n");
 for(temp1=head;temp1 != NULL;temp1=temp1->next)
 {
  if(temp1->big==NULL)
  fprintf(stdout,"\n Element :%d\t Big : %d",temp1->val,0);
  else
  fprintf(stdout,"\n Element :%d\t Big : %d",temp1->val,temp1->big->val);
 }
}

void delmul(node *ptr,int val)
{ 
 node * t2=NULL;
  if(ptr->big != NULL)
  {
  if(ptr->big->val==val)
   {
   t2=ptr->big;
  
   if(t2==head)
    {
    head=head->next;
    head->prev=NULL;
   }
  
  if(t2->next==NULL)
  {
   t2->prev->next=NULL;
   temp=t2->prev;
  }
  if(t2->next != NULL && t2->prev != NULL)
  {
   t2->prev->next=t2->next;
   t2->next->prev=t2->prev;
  }
  ptr->big=t2->big;
  free(t2);
   delmul(ptr,val);  
  }
 }
}

void del(int val)
{ 
  
 node *t1;
 
 if(val < small->val)
  return;

 if(small->val==val)
 {
  t1=small; 
  
 if(small->big==NULL)
  {
  small=head=temp=NULL;
  }
 else
 {
  if(small->big->val==val)
   delmul(small,val);
   if(small==head)
   {
    if(small->next==NULL)
    {
     small=head=temp=NULL; 
    }
    else
    {
    head=head->next;
    head->prev=NULL;
    }
   }
   else if(small->next==NULL)
   {
    small->prev->next=NULL;
    temp=small->prev;
   }
   else
   {
   small->prev->next=small->next;
   small->next->prev=small->prev;
   }
   small=small->big;
  }
  free(t1);
 }
 else
 {
  node* t2;
  t2=small;
   
   
  while(1)  
  {
  if(t2->big==NULL)
   break;
  
  if(t2->big->val==val)
   {
    delmul(t2,val);
    break;
   }
   t2=t2->big;
  }
 }
}

int main(void)
{
 int i,n,val;
 fprintf(stdout,"\nEnter the no of nodes:");
 fscanf(stdin,"%d",&n);
 create(n);
 trav();
 do
 {
 
 fprintf(stdout,"\n\n1)INSERT\n2)DELETE\n3)TRAVERSE\n4)EXIT\nENTER OPTION:");
 fscanf(stdin,"%d",&i);
 switch(i)
 {
 case 1:create(1);
        break;
 case 2:fprintf(stdout,"\nEnter the val:");
        fscanf(stdin,"%d",&val);
        del(val);
        break;
 case 3:trav();
        break;
 case 4:exit(0);
 }
 }while(i<=3);
 return 0;
}
