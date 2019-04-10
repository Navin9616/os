#include<stdio.h>
#include<stdlib.h>
int time;
struct node  
{
 int execute;
 int ar,br,id,status;
 struct node *link;
};
struct node *start=NULL,*ptr=NULL;
struct compiled 
{
int id;
struct compiled *link;
};
struct compiled *first=NULL,*pt=NULL;
void push_compiled(int num) 
{
 struct compiled *temp=(struct compiled*)malloc(sizeof(struct compiled));
 temp->id=num;
 temp->link=NULL;
 if(first==NULL)
  first=temp;
 else
  {
    pt=first;
     while(pt->link!=NULL)
      pt=pt->link;
     pt->link=temp;
  }
}
void push(int id,int ar,int br)
{
 struct node *temp=(struct node*)malloc(sizeof(struct node));
 temp->id=id;
 temp->ar=ar;
 temp->br=br;
 temp->status=0;
 temp->execute=0;
 temp->link=NULL;
 if(start==NULL)
  start=temp;
 else
  {
    ptr=start;
     while(ptr->link!=NULL)
      ptr=ptr->link;
     ptr->link=temp;
  }
}
void display()
{
 pt=first;
  while(pt!=NULL)
  { printf("p[%d] ",pt->id); pt=pt->link; }
  printf("\n");
}
void pop(int id) 
{
 struct node *par;
 ptr=start;
 if(start->id==id)
  start=start->link;
 else
  {
   while(ptr!=NULL && id!=ptr->id)
    { par=ptr; ptr=ptr->link; }
   if(ptr!=NULL && id==ptr->id)
    par->link=ptr->link;
  }
}
int set_status() 
{
int found=0;
 ptr=start;
  while(ptr!=NULL)
   {
     if(ptr->ar<=time)
      { ptr->status=1; found=1; }
     ptr=ptr->link;
   }
return found;
}
int main()
{
int i,n,ar,br;
printf("number of Process: ");
scanf("%d",&n);
for(i=0;i<n;i++)
{
 printf("Process id: %d\n",i+1);
 printf("arrival Time: ");
 again_ar:
 scanf("%d",&ar);
  if(ar<0)         
    {
      printf("\nInvalid arrival time\nPlease enter it again\n\n");
      goto again_ar;
    }
 printf("Burst Time: ");
 again_br:
 scanf("%d",&br);
  if(br<0)         
    {
      printf("\nInvalid Burst time\nPlease enter it again\n\n");
      goto again_br;
    }
 push(i+1,ar,br);
}
int found,wait=0,k;
ptr=start;
while(ptr!=NULL)  
{
again:
k=set_status();
 if(k==0)
  {
    time++;
    wait++;
    goto again;
  }
 struct node *p=start;
  while(p!=NULL)    
  {
    if(p->status==1)
     {
       if(p->br>8 && p->execute==0) 
        {
          p->br=p->br-8;
          time+=8;
          p->execute=1;
        }
       else if(p->br<=8 && p->br>0 && p->execute==0)
        {
          time=p->br+time;
          p->br=0;
          push_compiled(p->id);
          p->execute=1;
          pop(p->id);
        }
      }
   p=p->link;
  }
}
ptr=start;
while(ptr!=NULL)
 {
  ptr->execute=0;
  ptr->status=0;
  ptr=ptr->link;
 } 
ptr=start;
while(ptr!=NULL)   
{
again_:
k=set_status();
 if(k==0)
  {
   time++;
   wait++;
   goto again_;
  }
 struct node *p=start;
  while(p!=NULL)
  {
    if(p->status==1)
     {
       if(p->br>16 && p->execute==0)
        {
          p->br-=16;
          time+=16;
          p->execute=1;
        }
       else if(p->br<=16 && p->br>0 && p->execute==0)
        {
          time+=p->br;
          p->br=0;
          push_compiled(p->id);
          p->execute=1;
        }
     }
   p=p->link;
  }
}
ptr=start;
while(ptr!=NULL)
 {
  ptr->execute=0;
  ptr->status=0;
  ptr=ptr->link;
 }
 struct node *p=start;
 while(p!=NULL)
  {
    if(p->br>0 && p->execute==0)
      {
       time+=p->br;
       p->br=0;
       push_compiled(p->id);
       p->execute=1;
      }
    p=p->link;
  }
printf("Execution: \n");
display();
return 0;
}
