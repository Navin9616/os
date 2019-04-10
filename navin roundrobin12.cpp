#include<stdio.h>

int main()
{
      int i,no,ct=0,x,counter= 0,quantum; 
      int wt=0,tat=0,at[10],bt[10],temp[10]; 
      float awt,atat;
      printf("\nNumber of Processes:\t"); 
      scanf("%d",&no); 
      x = no; 
      for(i=0;i<no;i++) 
      {
            printf("\nData for process [%d]\n", i + 1);
            printf("Arrival Time:\t");
            scanf("%d", &at[i]);
            printf("Burst Time:\t");
            scanf("%d", &bt[i]); 
            temp[i] = bt[i];
      } 
      printf("\nQuantum:\t"); 
      scanf("%d",&quantum); 
      printf("Process ID   Burst Time   Turnaround Time  Waiting Time\n");
      for(ct=0,i=0;x!=0;) 
      { 
            if(temp[i]<=quantum && temp[i]>0) 
            { 
              ct=ct+temp[i]; 
              temp[i]=0; 
              counter=1; 
            } 
            else if(temp[i]>0) 
            { 
              temp[i]=temp[i]-quantum; 
              ct=ct+quantum; 
            } 
            if(temp[i]==0&&counter==1) 
            { 
              x--; 
              printf("\nProcess[%d] %d%d%d",i+1,bt[i],ct-at[i],ct-at[i]-bt[i]);
              wt=wt+ct-at[i]-bt[i]; 
              tat=tat+ct-at[i]; 
              counter=0; 
            } 
            if(i==no-1) 
               i=0; 
            else if(at[i+1]<=ct) 
               i++;
            else 
               i=0;
      } 
      awt=wt*1.0/no;
      atat=tat*1.0/no;
      printf("\nAverage Waiting Time:  %f", awt); 
      printf("\nAvg Turnaround Time:  %f\n", atat); 
      return 0; 
}
