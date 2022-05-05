#include<stdio.h>

#define High 25                     
#define Width 50

int cells[High][Width];        

void startup()  
{
    int i,j;
    for(i=0;i<=High;i++)
        for(j=0;j<=Width;j++)
            cells[i][j]=1;                         
 
 
    HideCursor();
}
void show()     
{
    gotoxy(0,0);
    int i,j;
    for(i=1;i<High;i++)
    {
        for(j=0;j<Width;j++)
        {
            if(cells[i][j]==1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    Sleep(200);            
}
void updateWithoutInput()           
{
    int i,j;
    int NeibourNumber;
    int temp[High][Width];
    for(i=1;i<High;i++)
    {
        for(j=1;j<Width;j++)
        {
            NeibourNumber=cells[i-1][j-1]+cells[i-1][j]+cells[i-1][j+1]+cells[i][j-1]+cells[i][j+1]+cells[i+1][j-1]+cells[i+1][j]+cells[i+1][j+1];
            if(NeibourNumber==3)            
                temp[i][j]=1;
            else if(NeibourNumber==2)      
                        temp[i][j]=cells[i][j];
            else
                temp[i][j]=0;
        }
    }
    for(i=1;i<High;i++)
        for(j=1;j<Width;j++)
            cells[i][j]=temp[i][j];
}
int main()
{
    startup();
    while(1)
    {
        show();
        updateWithoutInput();
    }
}