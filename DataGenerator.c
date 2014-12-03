#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* op=fopen("dataset.txt","w+");
    srand(time(NULL));
    int limit=2026;
    int run=limit;
    int datadiv=2;
    int index=9;
    int ageindex=9;
    int bigopen[10000][20];
    int i=0,j,k;
    int block[10]={751,1275};
    int age[10]={1009,331,308,249,86,43};
    int ageset[10]={15,25,35,45,55,65};
    int edu[10]={348,676,967,35};
    int dataset[10]={1,0};    while(run--)
    {
        index=9;
        while(index==9||block[index]==0)
        {
            index=rand()%datadiv;
        }
        block[index]--;
        bigopen[i++][0]=dataset[index];
    }
    run=limit;
    int temp;
    datadiv=6;
    i=0;
    while(run--)
    {
        index=9;
        while(index==9||age[index]-1==-1)
        {
            index=rand()%datadiv;
        }
        age[index]--;
        bigopen[i][1]=ageset[index]+(rand()%10);
        switch(ageset[index])
        {
            case 15:
                bigopen[i][2]=10500+rand()%4000;
            break;
            case 25:
                bigopen[i][2]=13500+rand()%5000;
            break;
            case 35:
                bigopen[i][2]=14000+rand()%5000;
            break;
            case 45:
                bigopen[i][2]=14500+rand()%3000;
            break;
            case 55:
                bigopen[i][2]=14000+rand()%3000;
            break;
            case 65:
                bigopen[i][2]=11500+rand()%3000;
            break;
        }
        if(bigopen[i][2]>17000)
        {
            temp=40+rand()%50;
        }
        else if(bigopen[i][2]>16000)
        {
            temp=40+rand()%35;
        }
        else if(bigopen[i][2]>15000)
        {
            temp=30+rand()%35;
        }
        else if(bigopen[i][2]>14000)
        {
            temp=rand()%40;
        }
        else
        {
            temp=rand()%30;
        }
        if(temp>60) bigopen[i][3]=1;
        else if(temp>40)bigopen[i][3]=2;
        else if(temp>20&&bigopen[i][2]>18)bigopen[i][3]=3;
        else if(temp>0&&bigopen[i][2]>22)bigopen[i][3]=4;
        i++;
    }
    for(i=0;i<limit;i++)
    {
        for(j=0;j<4;j++)
        {
            fprintf(op,"%d\t",bigopen[i][j]);
        }
        fprintf(op,"\n");
    }
}
