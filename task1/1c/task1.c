#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
void displayFile();
void loadToMem();
void saveToFile();
void quit();

struct func{
  char *name;
  void (*fun)(void);
};

int size = 0;
char filename[100];
unsigned char* data_pointer = NULL;
int debug = OFF;

int main(int argc, char** argv){

	initializeBuffer(filename, 100);

	struct func funcs[] = {
							{"Toggle Debug Mode", togDebug},
							{"Set File Name", setFileName},
							{"Set Unit Size", setUnitSize},
							{"File Display", displayFile},
							{"Load Into Memory", loadToMem},
							{"Save Into File", saveToFile},
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

	if((funcIndex < 0) || (funcIndex >= 7)){
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

	if(data_pointer != NULL){
		free(data_pointer);
	}

	printf("quitting\n");
	exit(0);
}

void displayFile(){

	// //REMOVE ME********************
	// togDebug();
	// setFileName();
	// setUnitSize();
	// //REMOVE ME********************


	
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
		char buf[9+9];
		printf("Plaese enter <location> <length>\n");
		
		fgets(buf, 9+9, stdin);
		sscanf(buf, "%x %d",&location, &length);

		if(debug){

			fprintf(stderr, "You enterd:\n");
			fprintf(stderr, "\tLocation: %x\n", location);
			fprintf(stderr, "\tLength: %d\n", length);
		}

		unsigned char* bytesToDisplay = (unsigned char*) malloc(size*length);

		fseek(file, location, SEEK_SET);
		fread(bytesToDisplay, size, length, file);
		
		// int k;
		// for(k=0; k < length; k++){

		// 	int readBytes = fread(bytesToDisplay, size, 1, file);
		// 	if(readBytes < size)
		// 		break;

		// 	fseek(file, size, SEEK_CUR);
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


		unsigned char nibbles[4];
		printf("Decimal Representation:\n");
		for(i=0; i < (size*length); i += 2){


			nibbles[0] = (bytesToDisplay[i] & 0xf);
			nibbles[1] = (bytesToDisplay[i] >> 4);
			nibbles[2] = (bytesToDisplay[i+1] & 0xf);
			nibbles[3] = (bytesToDisplay[i+1] >> 4);

			int decNum = 0;
			int j;
			for(j=3; j >=0; j--){
				// printf("nibble[%d] = %d\n", j, nibbles[j]);

				decNum += (nibbles[j])*(pow(16, j));
			}

			printf("%d ", decNum);
		}

		printf("\n");

		free(bytesToDisplay);

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

void loadToMem(){

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
		char buf[9+9];
		printf("Plaese enter <location> <length>\n");
		
		fgets(buf, 9+9, stdin);
		sscanf(buf, "%x %d",&location, &length);

		if(data_pointer != NULL){
			free(data_pointer);
		}

		data_pointer = (unsigned char*) malloc(length);

		if(debug){

			fprintf(stderr, "\tfilename: %s\n", filename);
			fprintf(stderr, "\tLocation: %x\n", location);
			fprintf(stderr, "\tLength: %d\n", length);
			fprintf(stderr, "\tData_pointer: %p\n", data_pointer);
		}

		fseek(file, location, SEEK_SET);
		fread(data_pointer, 1, length, file);

		printf("Loaded %d bytes into %p\n", length, data_pointer);

		fclose(file);
	}
}

void saveToFile(){

	if(filename == NULL){
		fprintf(stderr, "File name is null!\n");		
	}
	else{

		FILE* file = fopen(filename, "r+");

		if(file == NULL){
			
			fprintf(stderr, "An error occured while attempting to open %s!\n", filename);
			return;
		}

		int source_address_int;
		unsigned char* source_address;
		int target_location;
		int length;
		char buf[9+9+9];
		printf("Plaese enter <source-address> <target-location> <length>\n");
		
		fgets(buf, 9+9+9, stdin);
		sscanf(buf, "%x %x %d",&source_address_int, &target_location, &length);
		// sscanf(buf, "%x %x %d",source_address, &target_location, &length);

		source_address = (unsigned char*) source_address_int;
		if(source_address == 0){

			source_address = data_pointer;
		}


		fseek(file, 0, SEEK_END);
		// fseek(file, 0L, SEEK_END);
		long fileSize = ftell(file);
		
		if(debug){

			fprintf(stderr, "\tfilename: %s\n", filename);
			fprintf(stderr, "\tfile size: %d\n", (int) fileSize);
			fprintf(stderr, "\tLocation: %x\n", target_location);
			fprintf(stderr, "\tLength: %d\n", length);
			fprintf(stderr, "\tData_pointer: %p\n", data_pointer);
			fprintf(stderr, "\tSource_address: %p\n", source_address);
		}

		if(fileSize < target_location){
			fprintf(stderr, "Target-location (%d) exceeds file size (%d)!\n",
								target_location,
								(int) fileSize);
			return;
		}

		fseek(file, target_location, SEEK_SET);
		int written = fwrite(source_address, 1, length, file);

		printf("Wrote %d bytes into %s from %p\n", written, filename, source_address);

		fclose(file);
	}
}