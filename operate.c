#include "operate.h"



//function for user to create the world in a input way
//return the pointer of the world if it is created correctly
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
           mydelete(buff);
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



//get the user's expectative world size
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


//for user to click for world creation
//return the pointer of the created world
int **click_create(){
    
    bool quit=true;
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
                    quit=false;
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


//function for the visualization of the world
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




//copy a world data to create a new world
//return the newly created world pointer
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


//Judge if the input two world are the same
//return 1 if they are different
//return 0 if they are same
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



//function to update the input world to the next generation
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


//free the allocated space for world
void freecell(int **cells){
    
    for(int i = 0; i < High; i++){
         
		free(cells[i]);
	}
  
    free(cells);
}


//close the SDL related element
void close(SDL_Window* sdlWindow,SDL_Texture*sdlTexture,SDL_Renderer * sdlRenderer){
    SDL_DestroyTexture(sdlTexture);			// 释放纹理
	SDL_DestroyRenderer(sdlRenderer);		// 释放渲染器
	SDL_DestroyWindow(sdlWindow);			// 释放窗口
}

//delete the input string's space
void  mydelete(char *str)
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

//change the cell to be alive state
void changeblack(int x,int y,int**cells){
    if(cells[x][y]==0){
        cells[x][y]=1;
    }
   
}


//change the cell to be dead state
void changewhite(int x,int y,int**cells){
    if(cells[x][y]==1){
        cells[x][y]=0;
    }
  
}



    



