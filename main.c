#include<stdio.h>
#include"myutility.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <SDL2/SDL.h>

#define terminate 0
#define still 1
#define delay 100

int Width;
int High;
SDL_Renderer* renderer = NULL;
SDL_Window *window = NULL;

SDL_Texture* Texture = NULL;
SDL_Texture* Texture2 = NULL;
SDL_Surface* surface=NULL;

void init(){
 if (SDL_Init(SDL_INIT_VIDEO) != 0) 
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    
    atexit(SDL_Quit); // set for clean-up on exit
    SDL_CreateWindowAndRenderer(Width*100, High*100, 0, &window, &renderer);
    SDL_SetWindowTitle( window, "Circles eat squares");
    surface = SDL_CreateRGBSurface(0, Width*100, High*100, 32, 255, 255, 255, 255);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}





void show(int **cells)
{
    SDL_Rect rect;
    rect.x=0;
    rect.y=0;
    rect.h=100;
    rect.w=100;
    for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){
            if(cells[i][j]==0){
           
            SDL_FillRect(surface,&rect, SDL_MapRGB(surface->format, 255, 0, 0));
            printf("fuck");
            Texture = SDL_CreateTextureFromSurface(renderer,surface);
             printf("fuck");
             SDL_RenderCopy(renderer, Texture, NULL, &rect);
            //    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            //    SDL_RenderFillRect(renderer, &rect);
            //    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            //    SDL_RenderDrawRect(renderer, &rect);
           
               rect.x+=100;
               
            }
            if(cells[i][j]==1){
                // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                // SDL_RenderFillRect(renderer, &rect);
                //  SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                //  SDL_RenderDrawRect(renderer, &rect);
            SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 255, 255));
            Texture2 = SDL_CreateTextureFromSurface(renderer,surface);
             SDL_RenderCopy(renderer, Texture2, NULL, &rect);
                rect.x+=100;

                
            }
        }
        rect.x=0;
        rect.y+=100;
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(delay);
    return;
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



void updateWithoutInput(int **cells)           
{
   
    int i,j;
    int li,lj;
    int lx[8]={1,-1,0,0,1,-1,-1,1};
    int ly[8]={0,0,1,-1,1,-1,1,-1};
   
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


void freecell(int **cells){
    
    for(int i = 0; i < High; i++){
         
		free(cells[i]);
	}
  
    free(cells);
}

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
 

// void show(int **cells)     
// {
    
//     int i,j;
//     for(i=0;i<High;i++)
//     {
//         for(j=0;j<Width;j++)
//         {
//             if(cells[i][j]==1)
//                 printf("*");
//             else
//                 printf(".");
//         }
//         printf("\n");
//     }
//     Sleep(500);            
// }

int **create(){
    char buff[100];
    char c;
     int a=0;
        int x;
        int b=0;
        printf("Please input the initial size\n");
        while(a==0){
        printf("Please input the height of the world\nHeight:");
        x=optionChoice();
        if(x==-1){
       printf("\n You should input an Integer larger than 1 \n");
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
       printf("\n You should input an Integer larger than 1 \n");
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
              
               
              
               for(int k=0;k<Width;k++){
                   c=buff[k];
                   cells[z][k]=c-'0';;
                   
               }
               break;
           }
           }
        
        }
        printf("\nWorld created successfully \n");
        return cells;
    }





int ** load(FILE* file){

    char buff[100];
    char c;
    int j=0;
    int y;
    int **temp;
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
    temp=copy(cells);
    updateWithoutInput(cells);
    y=judge(cells,temp);
    free(cells);
    cells=copy(temp);
    free(temp);
    
    printf("Previous world loaded successfully\n");
    
    while(j==0){
    printf("previous world:\n");
    init();
    show(cells);
    if(y==0){
        printf("This world is terminated\n");
    }
    printf("Do you want to start with this?(0 for no and 1 for yes)\n");
    printf("Choice:");
    int m;
    m=optionChoice();
    
    if(m==-1){
             printf("\nYou should input 0 or 1\n\n");
                }
                else if(m!=0&&m!=1){
                    printf("please input 0 or 1\n\n");
                    continue;
                }
                else if(m==1){
                    return cells;
                }
                else if(m==0){
                    j=1;
                    int a=0;
                
        int x;
        int b=0;
        printf("Please input the initial size\n");
        while(a==0){
        printf("Please input the height of the world\nHeight:");
        x=optionChoice();
        if(x==-1){
       printf("\n You should input an Integer larger than 1\n");
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
       printf("\n You should input an Integer larger than 1\n");
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
               char m;
               for(int k=0;k<Width;k++){
                   m=buff[k];            
                   cells[z][k]=m-'0';
               }
               break;
           }
           }
        
        }
        printf("\nWorld created successfully \n");
        return cells;
                }
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
       printf("\n You should input an Integer larger than 1 \n");
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
       printf("\n You should input an Integer larger than 1 \n");
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
              
               char m;
              
               for(int k=0;k<Width;k++){
                   m=buff[k];
                   
                   cells[z][k]=m-'0';
                   
               }
               break;
           }
           }
        
        }
        printf("\nWorld created successfully \n");
        return cells;
    }
    return NULL;
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


int  game(FILE* file,int ** cell){
   int **last=NULL;
    int **my;
   int q;
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
   else if(x!=1&&x!=2){
       printf("\nYou should input a 1 or 2 \n");
            continue;
   }
   else{
       a=1;
   }
     }
     if(x==2){
       q=0;
    while(1){
       if(last!=NULL){
        d=judge(cell,last);
        if(d==0){
            printf("It is terminate\n");
            return terminate;
        }
       }    
       if(q==0){
           printf("The origin world:\n");
            last=copy(cell);
            show(cell);
            updateWithoutInput(cell);
            printf("\n");
            q+=1;
       }
       else{
        printf("step %d:\n",q);
        free(last);
        last=copy(cell);
        show(cell);
        updateWithoutInput(cell);
         printf("\n");
         q+=1;
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
       printf("\nYou should input an integer larger than 0 \n\n");
            continue;
          }
          else if(x<=0){
               printf("\nThe number should over 0 \n\n");
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
             printf("\nplease input 0 or 1\n\n");
                }
                else if(z!=0&&z!=1){
                    printf("please input 0 or 1\n\n");
                }
                else if(z==1){
                    m=1;
                }
                else if(z==0){
                 printf("The world is terminated\n");
                      freecell(last);
                  return terminate;
                }
                }
            
        }
          
           printf("step %d:\n",i+1);
           show(cell);
           freecell(last);
           last=copy(cell);
           if(i!=x-1){
           printf("\n");        
           }
           else{
               printf("The step is up\n");
               my=copy(cell);
               updateWithoutInput(my);
               d=judge(my,last);
               
                
               if(d==0){
                   freecell(my);
                   freecell(last);
                   return terminate;
               }
               else{
                  freecell(my);
                   freecell(last);
                   return still;
               }
           }
          
         }
     }
   return 1;
}

void  game2(char * filename){
    FILE *file=fopen("my.txt","r+");
   
    int **cell=load(file);
    fclose(file);
    FILE *close=fopen("my.txt","w");
    int result;
    int x;
    int a;
     while(1){
         a=0;
        init();
        result=game(file,cell);
        if(result==terminate){
            while(a==0){
            printf("This world is terminated\n");
            printf("Do you want to play a new game?(0 for quit and 1 for yes)\n");
            printf("Choice:");
             x=optionChoice();
          if(x==-1){
            printf("\nplease input 0 or 1\n\n");
                  continue;
             }
             else if(x!=0&&x!=1){
                 printf("\nplease input 0 or 1\n\n");
                 continue;
             }
            else{
                 a=1;
             }
        }
        if(x==0){
             printf("\nGame closed,Bye Bye\n");
             store(close,cell);
             freecell(cell);
             fclose(close);
             return;
        }
        if(x==1){
            free(cell);
           cell = create();
           continue;
        }
        }
        if(result==still){
            while(a==0){
             printf("This world is not terminated\n");           
             printf("Please choose an option\n1)Quit the game\n2)Still use it for another game\n3)Create a new world\n");
             printf("Choice:");
             x=optionChoice();
             if(x==-1){
            printf("\nPlease input 1 or 2 or 3\n\n");
                  continue;
             }
             else if(x==1){
                printf("\nGame closed,Bye Bye\n\n");
                
                 store(close,cell);
               
                 freecell(cell);
                
                 fclose(close);
                  return;
             }
             else if(x==2){  
                
                 a=1;
             }
             else if(x==3){
                freecell(cell);
                cell=create();   
                a=1;
             }
             else{
                 printf("Please input 1 or 2 or 3\n"); 
                 continue;
             }
             

            }
        }
     }
    
}



int main(int argc, char **argv)
{
    
    char user[100]="my.txt";
    // strcpy(user,argv[1]);
    game2(user);
    return 0;
}