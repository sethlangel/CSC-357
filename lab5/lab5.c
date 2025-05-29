#include<stdio.h>
#include<string.h>
char * xstrcpy(char *dest, char *src){
	char *orig_dest = dest;	

	while(*src != '\0'){
		*dest = *src;

		src++;
		dest++;
	}	

	*dest = '\0';

	return orig_dest;
}

int xstrcmp(const char *s1, const char *s2){
	while(*s1 != '\0' && *s2 != '\0'){
		if(*s1 != *s2){
			return *s1 - *s2;
		}
	
		s1++;
		s2++;
	}

	return *s1 - *s2;

	
}
int main(int argc, char *argv[]){

	char xtest[10];
	char test[10];
	xstrcpy(xtest, argv[1]);
	strcpy(test, argv[1]);
	printf("xstrcpy: %s\n", xtest);
	printf("strcpy: %s\n", test);
	
	printf("xstrcmp: %d\n", xstrcmp(argv[1], argv[2]));
	printf("strcmp: %d\n", strcmp(argv[1], argv[2]));
	return 0;
}
