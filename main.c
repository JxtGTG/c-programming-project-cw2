#include<stdio.h>


 





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
    return cells;
    }
    else{
        printf("File is empty\n");
        return 0;
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