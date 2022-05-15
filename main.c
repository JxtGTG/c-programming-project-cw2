#include<stdio.h>
#include"myutility.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <SDL2/SDL.h>

#include <stdbool.h>
#define terminate 0
#define still 1
#define delay 1000


int Width;
int High;
int key=1;


void input(void)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    SDL_PumpEvents();

    if (state[SDL_SCANCODE_UP]) {
        
    } 
    else if (state[SDL_SCANCODE_DOWN]) {
        key=0;
    } 
    else if (state[SDL_SCANCODE_LEFT]) {
        key=2;
    } 
    else if (state[SDL_SCANCODE_RIGHT]) {
        key=3;
    } 
    else if (state[SDL_SCANCODE_ESCAPE]) {
        exit(0);
    }
    return;
}


void show(SDL_Renderer* sdlRenderer,SDL_Window* sdlWindow,SDL_Texture* sdlTexture,int** cells){
       
    SDL_Rect rect;
    rect.x=0;
    rect.y=0;
    rect.h=100;
    rect.w=100;
    SDL_SetRenderTarget(sdlRenderer,sdlTexture); // 改变渲染目标为纹理
    SDL_SetRenderDrawColor(sdlRenderer,255,255,255,255); // 设置纹理颜色(颜色为RGBA)
    SDL_RenderClear(sdlRenderer); // 清空渲染器
    for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){
            if(cells[i][j]==0){
              
          
               SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
               SDL_RenderFillRect(sdlRenderer, &rect);
               SDL_SetRenderDrawColor(sdlRenderer, 100, 100, 100, 255);
               SDL_RenderDrawRect(sdlRenderer, &rect);
           
               rect.x+=100;
               
            }
            if(cells[i][j]==1){
              
                SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
                SDL_RenderFillRect(sdlRenderer, &rect);
                 SDL_SetRenderDrawColor(sdlRenderer, 100, 100, 100, 255);
                 SDL_RenderDrawRect(sdlRenderer, &rect);
       
                 rect.x+=100;
            }
        }
        rect.x=0;
        rect.y+=100;
    }
     SDL_SetRenderTarget(sdlRenderer, NULL);		// 恢复默认渲染目标,将要渲染的目标设置为默认窗口
	SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL)	;	// 将纹理数据复制给渲染器
    SDL_RenderPresent(sdlRenderer);
    // SDL_Delay();

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

void close(SDL_Window* sdlWindow,SDL_Texture*sdlTexture,SDL_Renderer * sdlRenderer){
    SDL_DestroyTexture(sdlTexture);			// 释放纹理
	SDL_DestroyRenderer(sdlRenderer);		// 释放渲染器
	SDL_DestroyWindow(sdlWindow);			// 释放窗口
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
 

void changeblack(int x,int y,int**cells){
    if(cells[x][y]==0){
        cells[x][y]=1;
    }
   
}
void changewhite(int x,int y,int**cells){
    if(cells[x][y]==1){
        cells[x][y]=0;
    }
  
}




int **click_create(){
    
    bool quit=TRUE;
    SDL_Init(SDL_INIT_EVERYTHING);

	// 创建窗口
	SDL_Window *sdlWindow = SDL_CreateWindow("drawRandRect",  SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, Width*100, High*100, SDL_WINDOW_SHOWN);


	// 创建渲染器
	SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);


	// 创建纹理
	SDL_Texture *sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width*100, High*100);
	SDL_Event event;
     int **cell;
       cell = (int **)malloc(High * sizeof(int *));
	for(int i = 0; i < High; i++){
		cell[i] = (int *)malloc(Width * sizeof(int));
	}
    for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){
            cell[i][j]=0;
        }
    }

   printf("Please click for the initialization of the world\n");
    printf("White for dead cell and black for live cell\n");
    printf("Left button of mouse for make cell alive and right button to make cell dead\n");
     printf("Please close the window when you finished to continue\n");
    while(quit){
   
    while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:{
                    quit=FALSE;
                    break;
                }   
                 case SDL_KEYDOWN:{
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP:{
                            printf("speed up");
                            
                           
                            break;
                        }
                        case SDLK_DOWN:{
                            printf("speed down");
                           
                            break;
                        }
                        case SDLK_SPACE:{
                           
                            break;
                        }
                        case SDLK_1:{
                           printf("1");
                            break;
                        }
                        case SDLK_2:{
                           printf("2");
                            break;
                        }
                        case SDLK_3:{
                           printf("3");
                            break;
                        }
                    }
                } 
               case SDL_MOUSEBUTTONDOWN:{
                    
                    int mouse_y = event.button.x/100;
                    int mouse_x = event.button.y/100;
                   
                    if(event.button.button == SDL_BUTTON_LEFT ){
                        changeblack(mouse_x,mouse_y,cell);
                    }
                    if(event.button.button == SDL_BUTTON_RIGHT ){
                        changewhite(mouse_x,mouse_y,cell);
                    }

                }
                case SDL_MOUSEMOTION:{
                      
                     int mouse_y = event.button.x/100;
                    int mouse_x = event.button.y/100;
                    if(event.button.button == SDL_BUTTON_LEFT ){
                        changeblack(mouse_x,mouse_y,cell);
                    }
                     if(event.button.button == SDL_BUTTON_X1 ){
                        changewhite(mouse_x,mouse_y,cell);
                    }

                }
               
            }
        }

    show(sdlRenderer,sdlWindow,sdlTexture, cell);
    }
   
    close(sdlWindow,sdlTexture,sdlRenderer);
    return cell;


}


void getsize(){
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
}

int **input_create(){
    char buff[100];
    char c;
    
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



int ** load(FILE* file){
   bool quit=TRUE;
    char buff[1000];
    char c;
    int j=0;
    int y;
    int m=100;
    int **temp;
    int xx=0;
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
         fgets(buff,1000,file);
         for(int j=0;j<Width;j++){
            c=buff[j];
            cells[i][j]=c-'0';
        }
    }
        
    temp=copy(cells);
    updateWithoutInput(cells);
    y=judge(cells,temp);
    freecell(cells);
    cells=copy(temp);
    freecell(temp);
    
    printf("Previous world loaded successfully\n");
    
    while(j==0){
    printf("previous world:\n");
    SDL_Init(SDL_INIT_EVERYTHING);

	// 创建窗口
	SDL_Window *sdlWindow = SDL_CreateWindow("drawRandRect",  SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, Width*100, High*100, SDL_WINDOW_SHOWN);


	// 创建渲染器
	SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);


	// 创建纹理
	SDL_Texture *sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width*100, High*100);
	SDL_Event sdlEvent;

    printf("The origin world(Close the window to continue):\n");
    while(quit){
   while (SDL_PollEvent(&sdlEvent)){
            switch (sdlEvent.type) {
                case SDL_QUIT:{
                    quit=FALSE;
                    break;
                }    
        
            }
        }

    show(sdlRenderer,sdlWindow,sdlTexture, cells);
   /////
    }
    close(sdlWindow,sdlTexture,sdlRenderer);

    if(y==0){
        printf("This world is terminated\n");
    }
    while(xx==0){
    printf("Do you want to start with this?(0 for no and 1 for yes)\n");
    printf("Choice:");
    
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
                    xx=1;
                   
                }
        
    }   
       int **cells;
       cells=create();
       
        printf("\nWorld created successfully \n");
        return cells;
                
    }
    }

    else{
      
        
        printf("File is empty\nPlease create the world\n");
      
       int **cells;
       cells=create();
    
        
        
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
            if(j<Width-1){    
            fprintf(file,"%d",cells[i][j]);  
            }
            else{
                    fprintf(file,"%d\n",cells[i][j]);  
            }          
        }
    }
}




int run2(int**cells){
    
     int q=1;
    int d=-100;
    int delaytime=1000;
    int **last=NULL;
    bool quit=TRUE;
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
                    quit=FALSE;
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



int run1(int **cells,int y)

{
    int x=0;
    int d=-100;
    int **last=NULL;
    int delaytime=1000;
    int **my=NULL;
    bool quit=TRUE;
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
                    quit=FALSE;
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
      result= run2(cell);
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
   result=run1(cell,x);
    if(result==terminate){
       
          return terminate;
      }
      else{
       
          return still;
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



int main(int argc, char **argv)
{
    
    char user[100]="my.txt";
    // strcpy(user,argv[1]);
    game2(user);
    return 0;
}