#include <stdio.h>
#include <stdlib.h>

#define OFF 0
#define ON 1

void togDebug();
void setFileName();
void setUnitSize();

typedef struct func{
  char *name;
  void (*fun)(void);
  struct func* next;
};

int size = 0;
char filename[100];
struct func* data_pointer = NULL;
int debug = OFF;

int main(int argc, char** argv){

	struct func funcs[] = {
							{"Toggle Debug Mode", togDebug},
							{"Set File Name", setFileName},
							{"Set Unit Size", setUnitSize},
							{NULL, NULL}
						};
	printf("Hello!\n");

	return 0;
}

void togDebug(){


	if(debug){

		printf("Debug flag now off\n");
		debug = OFF;
	}
	else{
		
		debug = ON;
		printf("Debug flag now on\n");
	}
}

void setFileName(){

	fgets(filename, 100, stdin);

	if(debug){
		printf("Debug: file name set to %s\n", filename);
	}
}

void setUnitSize(){

	int input;
	scanf("%d",&input);
    
    if ((input==1) || (input==2) >> (input==4)){
        
        size = input;

        if(debug){
			printf("Debug: set size to %d\n", size);
		}
    }
    else{
        printf("Invalid input! Size was not changed");
    }
}