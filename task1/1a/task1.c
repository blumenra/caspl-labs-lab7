#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define OFF 0
#define ON 1

void flushStdin();
void printFuncs();
void printGlobalVariables();
int getFuncRequest();
void initializeBuffer();
void printByte(char byte);

void togDebug();
void setFileName();
void setUnitSize();
void quit();
void displayFile();

struct func{
  char *name;
  void (*fun)(void);
};

int size = 0;
char filename[100];
struct func* data_pointer = NULL;
int debug = OFF;

int main(int argc, char** argv){

	initializeBuffer(filename, 100);

	struct func funcs[] = {
							{"Toggle Debug Mode", togDebug},
							{"Set File Name", setFileName},
							{"Set Unit Size", setUnitSize},
							{"Quit", quit},
							{"File Display", displayFile},
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

void initializeBuffer(char buf[], int length){

	int i;
	for(i=0; i < length; i++){
		buf[i] = 0;
	}
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
	printf("\tFile name: %s\n", filename);
	printf("\tBuffer address: %p\n", data_pointer);
}

int getFuncRequest(){
	char buf[3];
	fgets(buf, 3, stdin);
	
	int funcIndex;
	sscanf(buf, "%d",&funcIndex);

	if((funcIndex < 0) || (funcIndex >= 5)){
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

	// flushStdin();

	printf("Plaese enter a file name\n");
	fgets(filename, 100, stdin);

	//remove \n from filename
	int i=0;
	while(filename[i] != 0){
		if(filename[i] == '\n'){
			filename[i] = 0;
			break;
		}
		i++;
	}

	if(debug){
		printf("Debug: file name set to %s\n", filename);
	}
}

void flushStdin(){

	int a;
	while ((a = getchar()) != '\n' && a != EOF);
}

void setUnitSize(){

	
	char buf[3];
	printf("Plaese enter a unit size(1|2|4)\n");
	fgets(buf, 3, stdin);
	
	int input;
	sscanf(buf, "%d", &input);
    
    if ((input==1) || (input==2) || (input==4)){
        
        size = input;

        if(debug){
			printf("Debug: set size to %d\n", size);
		}
    }
    else{
        printf("%d is an invalid input! Size was not changed\n", input);
    }
}

void quit(){

	printf("quitting\n");
	exit(0);
}

void displayFile(){

	//REMOVE ME********************
	togDebug();
	setFileName();
	setUnitSize();
	//REMOVE ME********************


	
	if(filename == NULL){
		fprintf(stderr, "File name is null!\n");
	}
	else{
		FILE* file = fopen(filename, "r");

		if(file == NULL){
			
			fprintf(stderr, "An error occured while attempting to open %s!\n", filename);
			return;
		}

		int location;
		int length;
		char buf[6];
		printf("Plaese enter <location> <length>\n");
		
		fgets(buf, 6, stdin);
		sscanf(buf, "%x %d",&location, &length);

		if(debug){

			fprintf(stderr, "You enterd:\n");
			fprintf(stderr, "\tLocation: %x\n", location);
			fprintf(stderr, "\tLength: %d\n", length);
		}

		unsigned char* bytesToDisplay = (unsigned char*) malloc(size*length);

		fseek(file, location, SEEK_SET);
		// int i;
		// for(i=0; i < (size*length); i += size){

		fread(bytesToDisplay, size, length, file);
		// 	if(readBytes < size)
		// 		break;

		// 	fseek(file, SEEK_CUR, size);
		// }

		fclose(file);

		// printf("%x\n", bytesToDisplay[0]);
		// printf("%x\n", bytesToDisplay[1]);
		// printf("%x\n", bytesToDisplay[2]);
		// printf("%x\n", bytesToDisplay[3]);
		
		int i;
		printf("Hexadecimal Representation:\n");
		for(i=0; i < (size*length); i += 2){

			int j;
			for(j=i+1; j >= i; j--){

				printByte(bytesToDisplay[j]);
			}

			printf(" ");
		}

		printf("\n");


		printf("Decimal Representation:\n");
		for(i=0; i < (size*length); i += 2){

			

			printf(" ");
		}

		printf("\n");

	}
}

void printByte(char byte){

	unsigned char rightNibble = byte;
	unsigned char leftNibble = byte;
	
	rightNibble = (rightNibble & 0xf);
	leftNibble = (leftNibble >> 4);

	printf("%x", leftNibble);
	printf("%x", rightNibble);
}