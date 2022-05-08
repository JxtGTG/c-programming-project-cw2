#include<stdio.h>
#include"myutility.h"

 





int * load(FILE* file){
    char buff[100];
    int High;
    int Width;
    char c;
     if (file == NULL ){
    printf("Error\nBook file does not exist");
	return 1;
     }

    char c=fgetc(file);
    if(c!=EOF){
        rewind(file);

    fgets(buff,100,file);
    sscanf(buff,"%d",High);

    fgets(buff,100,file);
    sscanf(buff,"%d",Width);
    int cells[High][Width];
        
	for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){
            c=fgetc(file);
            sscanf(c,"%d",cells[i][j]);
        }
    }
    printf("Previous world loaded successfully\n");
    return cells;
    }
    else{
        int a=0;
        int x;
        int b=0;
        printf("File is empty\nPlease input the initial size\n");
        while(a==0){
        printf("Please input the height of the world\nHeight:\n");
        x=optionChoice;
        if(x==-1){
       printf("\n You should input an Integer \n");
       continue;
        }
        if(x<=1){
            printf("\n Height should be larger than 1 \n");
            continue;
        }
        a=1;
        High=x;
        }
         while(b==0){
        printf("Please input the width of the world\nWidth:\n");
        x=optionChoice;
        if(x==-1){
       printf("\n You should input an Integer \n");
       continue;
        }
        if(x<=1){
            printf("\n Width should be larger than 1 \n");
            continue;
        }
        b=1;
        Width=x;
        }
        int cells[High][Width];
        int d=0;
        
        for(int z=0;z<High;z++){
           printf("Please input the cells state for the row %d\n",z+1);
           printf("Notice:0 for dead and 1 for alive,you can choose to input like \"11011\" or \"1 0 1 0 1\"\n");
           scanf("%[^\n]",buff);
           getchar();
           if(strlen(buff)!=Width){
               printf("please input %d numbers\n",Width);
           }
           for(int i=0;i<strlen(buff);i++){
               if(s)
           }
        
        }
        printf("\n World created successfully \n");
        

        return cells;
    }

}

void store(FILE* file,int *cells[]){
    int High=sizeof(cells)/sizeof(cells[0]);
    int Width=sizeof(cells[0])/sizeof(cells[0][0]);
    fprintf(file,"%d\n",High);
    fprintf(file,"%d\n",Width);
    for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){      
            fprintf(file,"%d",cells[i][j]);
            
        }
    }
}







void startup(int *cells[])  
{
    int High=sizeof(cells)/sizeof(cells[0]);
    int Width=sizeof(cells[0])/sizeof(cells[0][0]);
    int i,j;
    for(i=0;i<High;i++)
        for(j=0;j<Width;j++)
            cells[i][j]=1;                         

}
void show(int *cells[])     
{
    int High=sizeof(cells)/sizeof(cells[0]);
    int Width=sizeof(cells[0])/sizeof(cells[0][0]);
    int i,j;
    for(i=0;i<High;i++)
    {
        for(j=0;j<Width;j++)
        {
            if(cells[i][j]==1)
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
    Sleep(5000);            
}
void updateWithoutInput(int *cells[])           
{
    int High=sizeof(cells)/sizeof(cells[0]);
    int Width=sizeof(cells[0])/sizeof(cells[0][0]);
    int i,j;
    int li,lj;
    int lx[8]={1,-1,0,0,1,-1,-1,1};
    int ly[8]={0,0,1,-1,1,-1,1,-1};
    int NeibourNumber;
    int temp[High][Width];
    for(i=0;i<High;i++)
    {
        for(j=0;j<Width;j++)
        {    
            int num=0;
            for(int k=0;k<8;k++){
                li = i + lx[k];
                lj = j + ly[k];
                if(li>=0&&li<High&&lj>=0&&lj<Width&&cells[li][lj]==1){
                    num+=1;
                }
            }
              if ((cells[i][j] == 1 && 2 <= num &&num<=3) || ( cells[i][j] == 0 && num == 3)){
                  temp[i][j]=1;
              }
              else{
                  temp[i][j]=0;
              }

           
        }
    }
    for(i=0;i<High;i++)
        for(j=0;j<Width;j++)
            cells[i][j]=temp[i][j];
}

int main()
{
    startup();
    while(1)
    {
        show();
        updateWithoutInput();
        printf("\n");
        printf("\n");
    }
}