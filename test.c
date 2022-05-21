#include "unity.h"
#include "game.h"
#include "Load_store.h"
#include <stdio.h>
#include "utility.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

void test_judge(){
   int **cell;
   int **lastcell;
   int **lastcell2;
  int Width=5;
  int High=5;
  cell = (int **)malloc(High * sizeof(int *));
     
	for(int i = 0; i < High; i++){
		cell[i] = (int *)malloc(Width * sizeof(int));
	}
    for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){
        cell[i][j]=1;
        }
    }
    lastcell = (int **)malloc(High * sizeof(int *));
     
	for(int i = 0; i < High; i++){
		lastcell[i] = (int *)malloc(Width * sizeof(int));
	}
    for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){
        lastcell[i][j]=1;
        }
    }
     lastcell2 = (int **)malloc(High * sizeof(int *));
     
	for(int i = 0; i < High; i++){
		lastcell2[i] = (int *)malloc(Width * sizeof(int));
	}
    for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){
        lastcell2[i][j]=0;
        }
    }
   TEST_ASSERT_EQUAL_INT( 1, judge(cell,lastcell) );
   TEST_ASSERT_EQUAL_INT( 0, judge(cell,lastcell2) );
}

void test_copy(){
    int **cell;
   int **cell1;
   int **cell2;
   int **nullcell =NULL;
    cell = (int **)malloc(High * sizeof(int *));
	for(int i = 0; i < High; i++){
		cell[i] = (int *)malloc(Width * sizeof(int));
	}
    for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){
        cell[i][j]=1;
        }
    }
    cell1=copy(cell);
    cell2=copy(nullcell);

    TEST_ASSERT_EQUAL_INT( 1, judge(cell,cell1) );
    TEST_ASSERT_NULL(cell2);
}


void test_mydelete(){
   
   char string[50]=" 1 1 0 1 0";
   char string2[50]="11010";
   TEST_ASSERT_EQUAL_STRING( string, string2);
   mydelete(string);
   TEST_ASSERT_EQUAL_STRING( string, string2);

}


void test_changewhite(){
     int **cell;
      int Width=5;
  int High=5;
    cell = (int **)malloc(High * sizeof(int *));
     for(int i = 0; i < High; i++){
		cell[i] = (int *)malloc(Width * sizeof(int));
	}
    for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){
        cell[i][j]=1;
        }
    }
     TEST_ASSERT_EQUAL_INT( 1, cell[3][3] );

     changewhite(3,3,cell);

    TEST_ASSERT_EQUAL_INT( 0, cell[3][3] );
}


void test_changeblack(){
     int **cell;
      int Width=5;
  int High=5;
    cell = (int **)malloc(High * sizeof(int *));
     for(int i = 0; i < High; i++){
		cell[i] = (int *)malloc(Width * sizeof(int));
	}
    for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){
        cell[i][j]=0;
        }
    }
     TEST_ASSERT_EQUAL_INT( 0, cell[3][3] );

     changewhite(3,3,cell);

    TEST_ASSERT_EQUAL_INT( 1, cell[3][3] );
}



void test_freecell(){
     int **cell;
      int Width=5;
  int High=5;
    cell = (int **)malloc(High * sizeof(int *));
     for(int i = 0; i < High; i++){
		cell[i] = (int *)malloc(Width * sizeof(int));
	}
    for(int i=0;i<High;i++){
        for(int j=0;j<Width;j++){
        cell[i][j]=0;
        }
    }
    TEST_ASSERT_NOT_NULL(cell[3]);
     TEST_ASSERT_NOT_NULL(cell);
     TEST_ASSERT_NOT_NULL(cell[3]+1);
      freecell(cell);
       TEST_ASSERT_NULL(cell[3]);
     TEST_ASSERT_NULL(cell);
      TEST_ASSERT_NULL(cell[3]+1);
}

int main(void)
{
UNITY_BEGIN();
RUN_TEST(test_judge);

return UNITY_END();
}