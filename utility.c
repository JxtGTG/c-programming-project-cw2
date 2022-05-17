#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"


// read in a line of text and convert to an integer option

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

  
    
