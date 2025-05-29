#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
	typedef struct {
		char ** arr;
		size_t capacity;
		size_t length;
	} ArrayList;

	ArrayList* array_list_new(size_t init_capacity);
	void array_list_add_to_end(ArrayList *list, char *string);
#endif

