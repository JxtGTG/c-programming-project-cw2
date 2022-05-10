#include<stdio.h>
#include"myutility.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>


int Width;
int High;

int optionChoice( void ) {
    int option = -1;
    char line[800];

    // read in the current line as a string
    fgets(line,800,stdin);
   
    // atoi() converts string to integer, returns 0 if could not convert
    option = (int)atoi(line);
    
   
        
    
     if(strlen(line)>2&&option==0){
         return -1;
     }
     else{
         for(int i=0;i<strlen(line)-1;i++){
              if(isdigit(line[i])==0){
              return -1;
        }
                 }
        return option;
       
       
}
     }

  
    


void  delete(char *str)
{
	char *str_c=str;
	int i,j=0;
	for(i=0;str[i]!='\0';i++)
	{
		if(str[i]!=' ')
			str_c[j++]=str[i];
	}
	str_c[j]='\0';
	str=str_c;	
    
}
 

void show(int **cells)     
{
    
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
    Sleep(500);            
}



int ** load(FILE* file){

    char buff[100];
    char c;

     if (file == NULL ){
    printf("Error\nBook file does not exist");
	exit(0);
     }


    c=fgetc(file);
    if(c!=EOF){
        rewind(file);

   
    fgets(buff,100,file);
    High=(int)atoi(buff);
   
    fgets(buff,100,file);
    Width=(int)atoi(buff);
    int **cells;
    cells = (int **)malloc(High * sizeof(int *));
	for(int i = 0; i < High; i++){
		cells[i] = (int *)malloc(Width * sizeof(int));
	}
        
	for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){
            c=fgetc(file);
            cells[i][j]=c-'0';
        }
    }
    printf("Previous world loaded successfully\n");
    printf("previous world\n");
    show(cells);
    printf("Do you want to start with this?(0 for no and 1 for yes)\n");
    printf("Choice:");
    int m;
    m=optionChoice();
    
    if(m==-1){
             printf("\n You should input an Integer\n");
                }
                else if(m!=0&&m!=1){
                    printf("please input 0 or 1\n");
                }
                else if(m==1){
                    return cells;
                }
                else if(m==0){
                    int a=0;
        int x;
        int b=0;
        printf("Please input the initial size\n");
        while(a==0){
        printf("Please input the height of the world\nHeight:");
        x=optionChoice();
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
        printf("Please input the width of the world\nWidth:");
        x=optionChoice();
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
       int **cells;
       cells = (int **)malloc(High * sizeof(int *));
	for(int i = 0; i < High; i++){
		cells[i] = (int *)malloc(Width * sizeof(int));
	}
        int d=0;
        
        for(int z=0;z<High;z++){  
                  
           while(1){
            d=0; 
           printf("Please input the cells state for the row %d\n",z+1);
           printf("Notice:0 for dead and 1 for alive,you can choose to input like \"11011\" or \"1 0 1 0 1\"\n");
           scanf("%[^\n]",buff);
           getchar();         
           delete(buff);
           if(strlen(buff)!=Width){
               printf("please input %d numbers\n",Width);
               continue;
           }
           for(int i=0;i<strlen(buff);i++){     
               if(buff[i]!='0'&&buff[i]!='1'){
                printf("please input 0 or 1!\n");
                d=1;
                 break;
               }
                
           }
           if(d==1){
               continue;
           }
           else{
               char *p;
               char m;
              
               for(int k=0;k<Width;k++){
                   m=buff[k];
                   p=&m;
                   cells[z][k]=(int)atoi(p);
                   
               }
               break;
           }
           }
        
        }
        printf("\nWorld created successfully \n");
        return cells;
                }
    }

    else{
        int a=0;
        int x;
        int b=0;
        printf("File is empty\nPlease input the initial size\n");
        while(a==0){
        printf("Please input the height of the world\nHeight:");
        x=optionChoice();
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
        printf("Please input the width of the world\nWidth:");
        x=optionChoice();
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
       int **cells;
       cells = (int **)malloc(High * sizeof(int *));
	for(int i = 0; i < High; i++){
		cells[i] = (int *)malloc(Width * sizeof(int));
	}
        int d=0;
        
        for(int z=0;z<High;z++){  
                  
           while(1){
            d=0; 
           printf("Please input the cells state for the row %d\n",z+1);
           printf("Notice:0 for dead and 1 for alive,you can choose to input like \"11011\" or \"1 0 1 0 1\"\n");
           scanf("%[^\n]",buff);
           getchar();         
           delete(buff);
           if(strlen(buff)!=Width){
               printf("please input %d numbers\n",Width);
               continue;
           }
           for(int i=0;i<strlen(buff);i++){     
               if(buff[i]!='0'&&buff[i]!='1'){
                printf("please input 0 or 1!\n");
                d=1;
                 break;
               }
                
           }
           if(d==1){
               continue;
           }
           else{
               char *p;
               char m;
              
               for(int k=0;k<Width;k++){
                   m=buff[k];
                   p=&m;
                   cells[z][k]=(int)atoi(p);
                   
               }
               break;
           }
           }
        
        }
        printf("\nWorld created successfully \n");
        return cells;
    }

}



void store(FILE* file,int **cells){
    
    
    fprintf(file,"%d\n",High);
    fprintf(file,"%d\n",Width);
    for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){      
            fprintf(file,"%d",cells[i][j]);            
        }
    }
}



void startup(int **cells)  
{
   
    int i,j;
    for(i=0;i<High;i++)
        for(j=0;j<Width;j++)
            cells[i][j]=1;                         
}

void updateWithoutInput(int **cells)           
{
   
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

int judge(int **cells,int **lastcells){
    for(int i=0;i<High;i++){
      for(int j=0;j<Width;j++){
        if(cells[i][j]!=lastcells[i][j]){
            return 1;
        }
      }
    }
    return 0;
}

int ** copy(int **cells){
    int **my;
    my = (int **)malloc(High * sizeof(int *));
     
	for(int i = 0; i < High; i++){
		my[i] = (int *)malloc(Width * sizeof(int));
	}
    for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){
        my[i][j]=cells[i][j];
        }
    }
     
  
    return my;
}

void  game(FILE* file){
    int **last=NULL;
    int **cell=load(file);
   
    int d;
    
     int x;
     int a=0;
     int b=0;
     while(a==0){
     printf("Please choose the mode\n");
     printf("1-Set certain number of step\n");
     printf("2-Keep envolving\n");
     printf("Choice:");
      x=optionChoice();
   if(x==-1){
       printf("\nYou should input a digit \n");
            continue;
   }
   else{
       a=1;
   }
     }
     if(x==2){
         int q=1;
    while(1){
       if(last!=NULL){
        d=judge(cell,last);
        if(d==0){
            printf("It is terminate\n");
            return;
        }
       }    
       if(q==1){
           printf("The origin world:\n");
            last=copy(cell);
            show(cell);
            updateWithoutInput(cell);
            printf("\n");
            q+=1;
       }
       else{
        printf("step %d:\n",q);
        last=copy(cell);
        show(cell);
        updateWithoutInput(cell);
         printf("\n");
       }
    }
     }
     else{
         int m=0;
        int z;
        while(b==0){
         printf("Please input the number of evolution:");
          x=optionChoice();
          if(x==-1){
       printf("\nYou should input a digit \n");
            continue;
          }
          else{
              b=1;
          }
   }
        printf("The origin world:\n");
        show(cell);
        last=copy(cell);
        printf("\n"); 
        
         for(int i=0;i<x;i++){
              
          updateWithoutInput(cell);
           d=judge(cell,last);
           if(d==0){
            printf("It is terminate\n");
                m=0;
                while(m==0){
                printf("Do you want to show the next steps?(input 0 for quit and 1 for continue)\n");
                z=optionChoice();
                if(z==-1){
             printf("\n You should input an Integer\n");
                }
                else if(z!=0&&z!=1){
                    printf("please input 0 or 1\n");
                }
                else if(z==1){
                    m=1;
                }
                else if(z==0){
                 printf("The world is end\n");
                  return;
                }
                }
            
        }
          
           printf("step %d:\n",i+1);
           show(cell);
           last=copy(cell);
           if(i!=x-1){
           printf("\n");        
           }
           else{
               printf("The step is up\n");
               
           }
          
         }
     }

}

void  game2(FILE * file){
    int **cell=load(file);
     while(1){
        game(file);
     }
}



int main()
{
    FILE *user=fopen("my.txt","r+");
    game(user);
    fclose(user);
}