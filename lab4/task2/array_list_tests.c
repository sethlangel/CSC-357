#include<stdio.h>
#include<unistd.h>
#include"checkit.h"
#include"array_list.h"
#define _GNU_SOURCE
int main(){
	ArrayList* arr_list = array_list_new(1);
	
	if(arr_list == NULL){
		printf("Error creating arrlist");
		return 1;
	}
	
	char str[50] = "Hello, Test";
	char *ptr;
	ptr = str;
	array_list_add_to_end(arr_list, ptr);
	checkit_string(str, *(arr_list->arr));	

	printf("%s\n", *(arr_list->arr));
	
	char str2[50] = "Test, Hello";
	char *ptr2;
	ptr2=str2;
	array_list_add_to_end(arr_list, ptr2);	
	printf("%s\n", *(arr_list -> arr + 1));
	checkit_string(str2, *(arr_list->arr+1));
	
	char str3[50] = "Test, Hello";
	char *ptr3;
	ptr3=str3;
	array_list_add_to_end(arr_list, ptr3);	
	printf("%s\n", *(arr_list -> arr + 2));

	checkit_string(str3, *(arr_list->arr+2));
	
	free(arr_list -> arr);
	free(arr_list);	
	return 0;
}
