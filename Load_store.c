
#include"Load_store.h"

int Width;
int High;
//load the data from the specific file to create the world
//return the world pointer
int ** load(FILE* file){
   bool quit=true;
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
                    quit=false;
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




//saves the database of the last world in the specified file
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
