#include <stdio.h>
#include <stdlib.h>

#define OFF 0
#define ON 1

void flushStdin();
void printFuncs();
void printGlobalVariables();
int getFuncRequest();


void togDebug();
void setFileName();
void setUnitSize();
void quit();

struct func{
  char *name;
  void (*fun)(void);
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
							{"Quit", quit},
							{NULL, NULL}
						};
	
	while(1){

		if(debug){
			printGlobalVariables();
		}

		printf("Choose action:\n");
		printFuncs(funcs);
		
		int funcIndex = getFuncRequest();

		if(funcIndex < 0){

			printf("Invalid input! Please try again\n");
		}
		else{

			funcs[funcIndex].fun();
		}
		

	}

	return 0;
}

void printFuncs(struct func funcs[]){

	int i=0;
	while(funcs[i].name != NULL){

		printf("%d-%s\n", i, funcs[i].name);
		i++;
	}
}

void printGlobalVariables(){

	printf("Global variables:\n");
	printf("\tUnit size: %d\n", size);

	int i;
	char tempFileName[100];
	for(i=0; i < 100; i++){
		tempFileName[i] = 0;
	}

	i=0;
	while(filename[i] != 0){

		tempFileName[i] = filename[i];
		if(tempFileName[i] == '\n'){
			
			tempFileName[i] = 0;
		}
		i++;
	}
	printf("\tFile name: %s\n", tempFileName);
	printf("\tBuffer address: %p\n", data_pointer);
}

int getFuncRequest(){

	int funcIndex;
	scanf("%d",&funcIndex);

	if((funcIndex < 0) || (funcIndex >= 4)){
		funcIndex = -1;
	}

	return funcIndex;
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

	flushStdin();

	printf("Plaese enter a file name\n");
	fgets(filename, 100, stdin);


	if(debug){
		printf("Debug: file name set to %s\n", filename);
	}
}

void flushStdin(){

	int a;
	while ((a = getchar()) != '\n' && a != EOF);
}

void setUnitSize(){

	int input;
	printf("Plaese enter a unit size(1|2|4)\n");
	scanf("%d",&input);
    
    if ((input==1) || (input==2) || (input==4)){
        
        size = input;

        if(debug){
			printf("Debug: set size to %d\n", size);
		}
    }
    else{
        printf("Invalid input! Size was not changed\n");
    }
}

void quit(){

	printf("quitting\n");
	exit(0);
}