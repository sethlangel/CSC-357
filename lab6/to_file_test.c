#include<stdio.h>
#include<stdlib.h>
int main(){
	for(int i = 1; i <= 101; i++){
		if(i % 2 == 0){
			printf("\t%d\n", i);
		}
	}

	return 0;
}
