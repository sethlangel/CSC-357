#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"array_list.h"

ArrayList* array_list_new(){
	ArrayList *new_arr_list = (ArrayList*) malloc(sizeof(ArrayList));

	if(new_arr_list == NULL){
		printf("Error: Memory not allocated.");
		return NULL;
	}

	new_arr_list -> capacity = 0;
	new_arr_list -> length = 0;

	new_arr_list -> arr = (char **) malloc (init_capacity * sizeof(char*));

	if(new_arr_list -> arr == NULL){
		printf("Error: Memory not allocated");
		free(new_arr_list);
		return NULL;
	}

	return new_arr_list;	
}

void array_list_add_to_end(ArrayList* list, char *string){
	if(list -> length >= list -> capacity){
		char** new_arr = (char**) realloc(list->arr, list->capacity + 1 * sizeof(char*));

		if(new_arr == NULL){
			printf("Error: Memory not allocated");
			exit(1);
		}
		else{
			list -> arr = new_arr;
			list -> capacity = list -> capacity + 1;
		}
	}
 	list->arr[list->length]= string;
	list -> length++;	
}
