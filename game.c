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
    int button=0;
     int q=0;
    int d=-100;
    int delaytime=250;
    int **last=NULL;
    bool quit=true;
    int**my=NULL;
    int x=0;
   int swidth=30;
    int sheight=30;

    if(High>20||Width>20){
        swidth=10;
        sheight=10;
    }
    if(High<10&&Width<10){
        swidth=50;
        sheight=50;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) { return -1; }

	// 创建窗口
	SDL_Window *sdlWindow = SDL_CreateWindow("Game of life",  SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, Width*swidth,High*sheight, SDL_WINDOW_SHOWN);
	if (!sdlWindow) { return -1; }

	// 创建渲染器
	SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
	if (!sdlRenderer) { return -1; }

	// 创建纹理
	SDL_Texture *sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width*swidth, High*sheight);
	if (!sdlTexture) { return -1; }

   printf("press enter to start or stop\n");
   
    
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
                            printf("\nspeed up");
                            if(delaytime<=10){
                                delaytime = 10;
                            }
                            delaytime = delaytime-10;
                            printf(" %d\n", delaytime);
                            break;
                        }  
                        case SDLK_DOWN:{
                            printf("\nspeed down");
                            if(delaytime>=250){
                                delaytime = 250;
                            }
                            delaytime = delaytime+10;
                           
                            break;
                        }    
                       
                      
                    }
                }
                 case SDLK_KP_ENTER:{
                     if(button==0){
                           button=1;
                     }
                     else{button=0;}
                            break;
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
        
        if(q==0&&button==1){
               printf("The origin world:\n");
        }
        if(q!=0&&d!=0&&button==1){
        printf("step %d:\n",q);
        }

        show(sdlRenderer,sdlWindow,sdlTexture, cells);
        SDL_Delay(delaytime);
        
        if(d!=0&&button==1){
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
    int button=0;
    int mm=0;
    int x=0;
    int d=-100;
    int **last=NULL;
    int delaytime=250;
    int **my=NULL;
    bool quit=true;

    int swidth=30;
    int sheight=30;

    if(High>20||Width>20){
        swidth=10;
        sheight=10;
    }
    if(High<10&&Width<10){
        swidth=50;
        sheight=50;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) { return -1; }

	// 创建窗口
	SDL_Window *sdlWindow = SDL_CreateWindow("Game of life",  SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, Width*swidth,High* sheight, SDL_WINDOW_SHOWN);
	if (!sdlWindow) { return -1; }

	// 创建渲染器
	SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
	if (!sdlRenderer) { return -1; }

	// 创建纹理
	SDL_Texture *sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width*swidth,High* sheight);
	if (!sdlTexture) { return -1; }

   
  
    
    SDL_Event event;
    printf("press enter to start or stop\n");
    //certain step	
        int z=0;
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
                            printf("\nspeed up");
                            if(delaytime<=10){
                                delaytime = 10;
                            }
                            delaytime = delaytime-10;
                           
                            break;
                        }  
                         case SDLK_DOWN:{
                            printf("\nspeed down");
                            if(delaytime>=250){
                                delaytime = 250;
                            }
                            delaytime = delaytime+10;
                           
                            break;
                        }   
                       
                      
                    }
                }
                 case SDLK_KP_ENTER:{
                              if(button==0){
                           button=1;
                     }
                     else{button=0;}
                            break;
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
           if(d!=0&&z<=y&&button==1){
               if(z==0){
                printf("The origin world:\n");
               }
            else{
                printf("step %d:\n",z);
            }
           }
            show(sdlRenderer,sdlWindow,sdlTexture, cells);
            SDL_Delay(delaytime);
           if(d!=0&&z<=y&&button==1){         
           free(last);
           last=copy(cells);
            updateWithoutInput(cells);
           }
           if(button==1){
             z++;
           }
           if(d!=0&&z>y&&mm==0){ 
               mm=1;
                 printf("The step is up\n");
                 printf("Please close the window to continue\n");  
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
                 
                printf("\nGame closed,Bye Bye\n");
                
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






