#include "game.h"

#define terminate 0
#define still 1


//function to create the world
//return the world pointer if the world created correctly
int **create(){
    int x;
    int **cells;
    int a=0;
    
    while(a==0){
    printf("Please choose the way of initialization\n1)input\n2)click\nChoice:");
    x=optionChoice();
    if(x==1){
        getsize();
       cells = input_create();
       a=1;
    }
    else if(x==2){
        getsize();
        cells=click_create();
        a=1;
    }
    else{
        printf("Please input 1 or 2\n");
    }
    }
    return cells;

}



//game evolve to the terminal
//return 1 if the world is not end when exit
//return 0 when the world is end
int run_terminal(int**cells){
    
     int q=1;
    int d=-100;
    int delaytime=1000;
    int **last=NULL;
    bool quit=true;
    int**my=NULL;
    int x=0;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) { return -1; }

	// 创建窗口
	SDL_Window *sdlWindow = SDL_CreateWindow("drawRandRect",  SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, Width*100, High*100, SDL_WINDOW_SHOWN);
	if (!sdlWindow) { return -1; }

	// 创建渲染器
	SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
	if (!sdlRenderer) { return -1; }

	// 创建纹理
	SDL_Texture *sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width*100, High*100);
	if (!sdlTexture) { return -1; }

    printf("The origin world:\n");
    show(sdlRenderer,sdlWindow,sdlTexture, cells);
    
    SDL_Event event;

         while(quit){
             while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:{
                    quit=false;
                    break;
                }
                 case SDL_KEYDOWN:{
                    switch(event.key.keysym.sym)
                    {
                          case SDLK_UP:{
                            printf("speed up");
                            if(delaytime<=10){
                                delaytime = 10;
                            }
                            delaytime = delaytime-10;
                            printf(" %d\n", delaytime);
                            break;
                        }    
                       
                      
                    }
                }

               
            }
        }

        if(last!=NULL){
        d=judge(cells,last);
        }
        if(d==0&&x==0){
            x=1;
            printf("It is terminate\n");
            printf("Close the window to continue\n");
        }
         show(sdlRenderer,sdlWindow,sdlTexture, cells);
         SDL_Delay(delaytime);
        if(d!=0){
        printf("step %d:\n",q);
        free(last);
        last=copy(cells);
        updateWithoutInput(cells);
         printf("\n");
         q+=1;  
    }
         }
        
               my=copy(cells);
               updateWithoutInput(my);
               d=judge(my,last);
               if(d==0){
                   freecell(my);
                   freecell(last);
                    close(sdlWindow,sdlTexture,sdlRenderer);
                   return terminate;
               }
               else{
                  freecell(my);
                   freecell(last);
                    close(sdlWindow,sdlTexture,sdlRenderer);
                   return still;
               }
         
}

//input world to evolve for input steps
//return 1 if the world is not end when exit
//return 0 when the world is end
int run_step(int **cells,int y)

{
    int x=0;
    int d=-100;
    int **last=NULL;
    int delaytime=1000;
    int **my=NULL;
    bool quit=true;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) { return -1; }

	// 创建窗口
	SDL_Window *sdlWindow = SDL_CreateWindow("drawRandRect",  SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, Width*100, High*100, SDL_WINDOW_SHOWN);
	if (!sdlWindow) { return -1; }

	// 创建渲染器
	SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
	if (!sdlRenderer) { return -1; }

	// 创建纹理
	SDL_Texture *sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width*100, High*100);
	if (!sdlTexture) { return -1; }

    printf("The origin world:\n");
    show(sdlRenderer,sdlWindow,sdlTexture, cells);
    
    SDL_Event event;

    //certain step	
        int z=0;
        while(quit){
          
          while(quit){
             while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:{
                    quit=false;
                    break;
                }
                 case SDL_KEYDOWN:{
                    switch(event.key.keysym.sym)
                    {
                          case SDLK_UP:{
                            printf("speed up");
                            if(delaytime<=10){
                                delaytime = 10;
                            }
                            delaytime = delaytime-10;
                            printf(" %d\n", delaytime);
                            break;
                        }    
                       
                      
                    }
                }

               
            }
        }
          }

        if(last!=NULL){
           d=judge(cells,last);
        } 
           if(d==0&&x==0){
               x=1;
            printf("It is terminate\n");
             printf("Close the window to continue\n");
              
           }
           if(z<y){
            printf("step %d:\n",z+1);
           }
            z++;
            show(sdlRenderer,sdlWindow,sdlTexture, cells);
            SDL_Delay(delaytime);
           if(d!=0&&z<y){         
           free(last);
           last=copy(cells);
            updateWithoutInput(cells);
        if(z==y-1){
              
                 printf("The step is up\n");
                 printf("Please close the window to continue\n");
               
           }
           }
          
         
    
        }
    my=copy(cells);
               updateWithoutInput(my);
               d=judge(my,last);
                
               if(d==0){
                   freecell(my);
                   freecell(last);
                      close(sdlWindow,sdlTexture,sdlRenderer);
                   return terminate;
               }
               else{
                  freecell(my);
                   freecell(last);
                      close(sdlWindow,sdlTexture,sdlRenderer);
                   return still;
               }
        

}



//function of  whole process of a world's evolution
//return 1 if the world is not end when exit
//return 0 when the world is end
int  game(int ** cell){
    int result;
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
      result= run_terminal(cell);
      if(result==terminate){
          return terminate;
      }
      else{
          return still;
      }
     }
     
     else{
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
   result=run_step(cell,x);
    if(result==terminate){
       
          return terminate;
      }
      else{
       
          return still;
      }
        
     }
   return 1;
}



//The whole game system
void  whole_game(char * filename){
    FILE *file=fopen("my.txt","r+");
   
    int **cell=load(file);
    fclose(file);
    FILE *close=fopen("my.txt","w");
    int result;
    int x;
    int a;
     while(1){
         a=0;
        result=game(cell);
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






