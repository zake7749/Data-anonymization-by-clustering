#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

double arr[10000][20];
double sh[10000][20];
int cluster[100][10000];
int cluindex[100];
double gm[100][20];
double max[20];
double min[20];
double sum[20];
int col,row;

void GuessMean(int cluster);
void Datatrans();
void Init();
void Kmeans(int clu);
void Randchange(int clu);

int main()
{
    int clu,i,j;
    printf("Input the scale (Col*Row):");
    scanf("%d %d",&col,&row);
    printf("\nInput the Cluster number:");
    scanf("%d",&clu);
    Init();
    Datatrans();
    /*
    for(i=0;i<col;i++)
    {
        printf("Max[%d]:%lf\t",i,max[i]);
        printf("Min[%d]:%lf\t",i,min[i]);
        printf("Sum[%d]:%lf",i,sum[i]);
        printf("\n");
    }*/
    GuessMean(clu);
    Kmeans(clu);
    printf("Kmeans done.\n");
    printf("Cluster is:\n");
    for(i=0;i<clu;i++)
    {
        if(cluindex[i])
            printf("Cluster #.%d:\n",i);
        for(j=0;j<cluindex[i];j++)
        {
            printf("%d ",cluster[i][j]);
        }
        if(j>0)printf("\n");
    }
    Randchange(clu);
    printf("Out put the file as ann.txt\n");
    FILE* op=fopen("anonymity.txt","w+");
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            fprintf(op,"%lf\t",arr[i][j]);
        }
        fprintf(op,"\n");
    }
    printf("Result had printed.\n");
}

void Init()
{
    FILE* in;
    int i=0,j=0;
    char temp[100];
    in = fopen("demo.txt","r+");
    while(i<row)
    {
        fscanf(in,"%lf %lf %lf %lf",&arr[i][0],&arr[i][1],&arr[i][2],&arr[i][3]);
        i++;
    }
    for(i=0;i<col;i++)
    {
        max[i]=-99999999.99;
        min[i]=99999999.99;
    }
}

void Datatrans()
{
    int i,j,k;
    double temp;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if(max[j]<arr[i][j])
                max[j]=arr[i][j];
            if(min[j]>arr[i][j])
                min[j]=arr[i][j];
        }
    }
    for(i=0;i<col;i++)
    {
        printf("Max[%d]:%lf\t",i,max[i]);
        printf("Min[%d]:%lf\t",i,min[i]);
        printf("\n");
    }
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if(0.0==arr[i][j])sh[i][j]=0.0;
            else
            {
                sh[i][j]=((arr[i][j]-min[j])/(max[j]-min[j]))*100;
            }
        }
    }

    FILE* tp=fopen("debug.txt","w+");
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            fprintf(tp,"%lf\t",sh[i][j]);
        }
        fprintf(tp,"\n");
    }
}

void GuessMean(int cluster)
{
    int i,j,index;
    double pf=1000.0;//This value must be impossible to pass the while loop.
    int temp;
    srand(time(NULL));
    //to determine the initial Gravity point.
    //Node num = cluster num.
    for(i=0;i<cluster;i++)
    {
        for(j=0;j<col;j++)
        {
            while(pf>95||pf<5)//Range should be consider data by data.
            {
                pf=(double)rand()/(RAND_MAX+1.0000);
                pf*=100;
            }
            gm[i][j]=pf;
            pf=1000.0;//Reset pf to a impossible value.
        }
    }
    printf("Guess done.\n");
    for(i=0;i<cluster;i++)
    {
        printf("#%d.GM\n",i);
        for(j=0;j<col;j++)
        {
            printf("%lf ",gm[i][j]);
        }
        printf("\n");
    }
}

void Kmeans(int clu)
{
    int i,j,k;
    int run=100000;
    double md=500000.0;//min distance.
    double nd=0.0;//distance of the selected node in k loop.
    int belongstowho;//This node should belongs to which cluster ?
    while(run--)
    {
        for(i=0;i<100;i++)
        {
            cluindex[i]=0;
        }
        for(i=0;i<row;i++)
        {
            for(j=0;j<clu;j++)
            {
                for(k=0;k<col;k++)
                {
                    nd+=(gm[j][k]-sh[i][k])*(gm[j][k]-sh[i][k]);
                }
                if(nd<md)
                {
                    belongstowho=j;
                    md=nd;
                }
                nd=0.0;
            }
            cluster[belongstowho][cluindex[belongstowho]++]=i;
            md=500000.0;
        }
        /*printf("This time Cluster is:\n");
        for(i=0;i<clu;i++)
        {
            for(j=0;j<cluindex[i];j++)
            {
                printf("%d",cluster[i][j]);
            }
            if(j>0)printf("\n");
        }*/
        //GET NEW Gravity Point
        for(i=0;i<clu;i++)
        {
            double tempfix=0.0;
            double tgp[col];
            for(j=0;j<col;j++)
                tgp[j]=0.0;
            for(j=0;j<cluindex[i];j++)
            {
                tempfix+=1.0;
                for(k=0;k<col;k++)
                {
                    tgp[k]+=sh[cluster[i][j]][k];
                }
            }
            if(j!=0)//This cluster have at least 1 member.
            {
                for(k=0;k<col;k++)
                {
                    gm[i][k]=tgp[k]/tempfix;
                }
            }
        }
        /*printf("New GP:\n");
        for(i=0;i<clu;i++)
        {
            for(j=0;j<col;j++)
            {
                printf("%lf\n",gm[i][j]);
            }
            printf("\n");
        }*/
    }
}

void Randchange(int clu)
{
    int i,j,k;
    int c,temp;
    srand(time(NULL));
    for(i=0;i<clu;i++)
    {
        for(j=0;j<cluindex[i];j++)
        {
            for(k=0;k<col;k++)
            {
                c=(rand()%cluindex[i]);
                temp=arr[cluster[i][j]][k];
                arr[cluster[i][j]][k]=arr[cluster[i][c]][k];
                arr[cluster[i][c]][k]=temp;
            }
        }
    }
    printf("Change had done.\n");
}
