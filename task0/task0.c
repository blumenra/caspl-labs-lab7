#include <stdio.h>
#include <stdlib.h>

#define OFF 0
#define ON 1

void togDebug();
void setFileName();

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
}