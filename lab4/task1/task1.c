#include<ctype.h>
#include<stdio.h>
#include"task1.h"

void str_lower(char *orig, char *copy){
	int i = 0;

	while(orig[i] != '\0'){
		copy[i] = tolower(orig[i]);
		i++;
	}

	copy[i] = '\0';
}

void str_lower_mutate(char *orig){
	int i = 0;

	while(orig[i] != '\0'){
		orig[i] = tolower(orig[i]);
		i++;
	}
}
