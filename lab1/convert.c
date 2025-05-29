#include<stdio.h>

int main(){
	float celsius;
	printf("Please enter a temperature in Celsius \n");
	scanf("%f", &celsius);

	float fahrenheit = celsius * 1.8 + 32;

	printf("%f C converted to F is: %ff \n", celsius, fahrenheit); 

	if(fahrenheit >= 100){
		printf("Warning: Heat Wave \n");
	} else if(fahrenheit >= 80 && fahrenheit <= 99){
		printf("Hot \n");
	} else if (fahrenheit >= 41 && fahrenheit <= 79){
		printf("Normal \n");
	} else if (fahrenheit >= 10 && fahrenheit <=40){
		printf("Cold \n");
	}	

	return 0;
}


