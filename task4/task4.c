// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

int digit_cnt(char* str){

	int count = 0;
	int i=0;
	while(str[i] != 0){

		if((str[i] >= '0') && (str[i] <= '9'))
			count++;

		i++;
	}

	return count;
}


int main(int argc, char** argv){

	// char s1[17] = {'a','a','b','b','a','b','a','1','2','3','b','a','a','c','c','a', 0};
	// char s2[8] = {'1','1','1','2','1','1','1', 0};
	// char s3[11] = {'0','1','2','3','4','5','6','7','8','9',0};
	// printf("s1: %d\n", digit_cnt(s1));
	// printf("s2: %d\n", digit_cnt(s2));
	// printf("s3: %d\n", digit_cnt(s3));
	
	return 0;
}
